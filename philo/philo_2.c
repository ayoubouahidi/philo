#include "philo.h"

void	free_data(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->used__mtx)
	{
		i = 0;
		while (i < SIZE_MTX_US)
		{
			pthread_mutex_destroy(&data->used__mtx[i]);
			i++;
		}
		free(data->used__mtx);
	}
	if (data->philos)
		free(data->philos);
	free(data);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->data->forks[philo->fork_l]));
		ft_printstatus(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->data->forks[philo->fork_r]));
		ft_printstatus(philo, "has taken a fork");
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(&(philo->data->forks[philo->fork_r]));
		ft_printstatus(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->data->forks[philo->fork_l]));
		ft_printstatus(philo, "has taken a fork");
	}
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_l]));
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_r]));
}

void	check_if_number_one(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
	{
		pthread_mutex_lock(&(philo->data->forks[0]));
		ft_printstatus(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->data->used__mtx[DEATH]));
		philo->data->flag_death = 1;
		pthread_mutex_unlock(&(philo->data->used__mtx[DEATH]));
		pthread_mutex_unlock(&(philo->data->forks[0]));
	}
}

void	eating_meals(t_philo *philo, int finished_eating)
{
	if (finished_eating)
	{
		pthread_mutex_lock(&(philo->data->used__mtx[GLB_FINISH]));
		philo->data->philos_finished_eating++;
		pthread_mutex_unlock(&(philo->data->used__mtx[GLB_FINISH]));
		pthread_mutex_lock(&(philo->data->used__mtx[FINISH]));
		philo->finish_eating = 1;
		pthread_mutex_unlock(&(philo->data->used__mtx[FINISH]));
	}
}	