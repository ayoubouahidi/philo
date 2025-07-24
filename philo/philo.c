#include "philo.h"


void	*routine(void *args)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)args;
	void (*ptr[])(t_philo *) = {eating, sleeping, thinking};
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

void	end_sim(t_data *data)
{
	pthread_mutex_lock(&(data->used__mtx[SIM]));
	data->sim = 1;
	pthread_mutex_unlock(&(data->used__mtx[SIM]));
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

void	monitoring(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			if (all_philos_eating(data))
			{
				end_sim(data);
				return ;
			}
			pthread_mutex_lock(&(data->used__mtx[MEAL]));
			if (get_time(data) - data->philos[i].last_meal > data->time_to_die)
			{
				monitoring_death(data, i);
				pthread_mutex_unlock(&(data->used__mtx[MEAL]));
				return ;
			}
			pthread_mutex_unlock(&data->used__mtx[MEAL]);
			i++;
		}
	}
}

void	creat_threads(t_data *data)
{
	int			i;
	pthread_t	arr_threads[data->number_of_philo];

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_create(&arr_threads[i], NULL, routine, &data->philos[i]);
		i++;
	}
	monitoring(data);
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_join(arr_threads[i], NULL);
		i++;
	}
	free_data(data);
}
