/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:29:34 by ayouahid          #+#    #+#             */
/*   Updated: 2025/07/24 15:29:36 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_meal_status(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->used__mtx[MEAL_COUNT]));
	philo->meal_count++;
	if (philo->data->number_of_times_each_philosopher_must_eat != -1
		&& philo->meal_count \
		== philo->data->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_unlock(&(philo->data->used__mtx[MEAL_COUNT]));
		pthread_mutex_lock(&(philo->data->used__mtx[FINISH]));
		if (!philo->finish_eating)
		{
			philo->finish_eating = 1;
			pthread_mutex_unlock(&(philo->data->used__mtx[FINISH]));
			pthread_mutex_lock(&(philo->data->used__mtx[GLB_FINISH]));
			philo->data->philos_finished_eating++;
			pthread_mutex_unlock(&(philo->data->used__mtx[GLB_FINISH]));
		}
		else
			pthread_mutex_unlock(&(philo->data->used__mtx[FINISH]));
	}
	else
		pthread_mutex_unlock(&(philo->data->used__mtx[MEAL_COUNT]));
	put_forks(philo);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->used__mtx[FINISH]));
	if (philo->finish_eating)
	{
		pthread_mutex_unlock(&(philo->data->used__mtx[FINISH]));
		return ;
	}
	pthread_mutex_unlock(&(philo->data->used__mtx[FINISH]));
	eating_print(philo);
	pthread_mutex_lock(&(philo->data->used__mtx[MEAL]));
	philo->last_meal = get_time(philo->data);
	pthread_mutex_unlock(&(philo->data->used__mtx[MEAL]));
	ft_usleep(philo->data->time_to_eat, philo->data);
	update_meal_status(philo);
}

void	sleeping(t_philo *philo)
{
	ft_printstatus(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	thinking(t_philo *philo)
{
	ft_printstatus(philo, "is thinking");
	if (philo->data->time_to_eat > philo->data->time_to_sleep)
		ft_usleep(philo->data->time_to_eat - philo->data->time_to_sleep, philo->data);
	if (philo->data->number_of_philo % 2 == 1)
		ft_usleep(15, philo->data);
}

int	all_philos_eating(t_data *data)
{
	int	result;

	result = 0;
	if (data->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	pthread_mutex_lock(&(data->used__mtx[GLB_FINISH]));
	if (data->philos_finished_eating >= data->number_of_philo)
		result = 1;
	pthread_mutex_unlock(&(data->used__mtx[GLB_FINISH]));
	return (result);
}
