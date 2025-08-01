/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:34:59 by ayouahid          #+#    #+#             */
/*   Updated: 2025/07/24 15:35:00 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo		*philo;
	int			i;
	static void	(*ptr[])(t_philo *) = {eating, sleeping, thinking};

	i = 0;
	philo = (t_philo *)args;
	if (philo->id % 2 != 0)
		usleep(500);
	check_if_number_one(philo);
	while (1)
	{
		if (all_philos_eating(philo->data) || check_death(philo->data)
			|| check_end(philo->data))
			return (NULL);
		i %= 3;
		ptr[i](philo);
		i++;
	}
}

void	monitoring_death(t_data *data, int i)
{
	pthread_mutex_lock(&(data->used__mtx[DEATH]));
	data->flag_death = 1;
	pthread_mutex_lock(&(data->used__mtx[PRINT]));
	printf("%lld %d %s \n", get_time(data), data->philos[i].id, "died");
	pthread_mutex_unlock(&(data->used__mtx[PRINT]));
	pthread_mutex_unlock(&(data->used__mtx[DEATH]));
	end_sim(data);
}

int	check_philos_death(t_data *data)
{
	int		i;
	size_t	time_since_meal;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_lock(&(data->used__mtx[MEAL]));
		time_since_meal = get_time(data) - data->philos[i].last_meal;
		pthread_mutex_unlock(&(data->used__mtx[MEAL]));
		if (time_since_meal > data->time_to_die)
		{
			monitoring_death(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (1)
	{
		usleep(1000);
		if (check_end(data))
			return (NULL);
		if (all_philos_eating(data))
		{
			end_sim(data);
			return (NULL);
		}
		if (check_philos_death(data))
			return (NULL);
	}
	return (NULL);
}

void	creat_threads(t_data *data)
{
	int			i;
	pthread_t	*arr_threads;
	pthread_t	monitoring_thread;

	arr_threads = malloc(sizeof(pthread_t) * data->number_of_philo);
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_create(&arr_threads[i], NULL, routine, &data->philos[i]);
		i++;
	}
	pthread_create(&monitoring_thread, NULL, monitoring, data);
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_join(arr_threads[i], NULL);
		i++;
	}
	pthread_join(monitoring_thread, NULL);
	free(arr_threads);
	free_data(data);
}
