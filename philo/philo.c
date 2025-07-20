#include "philo.h"

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

void eating(t_philo *philo)
{
	take_fork(philo);
	ft_printstatus(philo, "is eating");
	philo->last_meal = get_time();	
	put_forks(philo);
}

void sleeping(t_philo *philo)
{
	ft_printstatus(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void thinking(t_philo *philo) 
{
	ft_printstatus(philo, "is thinking");
}

void	*routine(void *args)
{
	t_philo *philo;
	int i = 0;

	philo = (t_philo *)args;
	void (*ptr[])(t_philo*) = {eating, sleeping, thinking};
	while (1)
	{
		if (check_death(philo->data))
			break ;
		i %= 3;
		ptr[i](philo);
		i++;
	}
	return (NULL);
}

void	*monitoring(void *args)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = (t_philo *)args;
	while (1)
	{
		if (check_death(philo->data))
			break ;
		if (get_time() - philo->data->philos[i].last_meal > philo->data->time_to_die)
		{
			pthread_mutex_lock(&(philo->data->used__mtx[DEATH]));
			philo->data->flag_death = 1;
			pthread_mutex_lock(&(philo->data->used__mtx[DEATH]));
			ft_printstatus(philo, "died");
			return (NULL);
		}
		i++;
	}
	// usleep(1000);
	return (NULL);
}

void	creat_threads(t_data *data)
{
	int i;
	pthread_t	arr_threads[data->number_of_philo];
	pthread_t	monitoring_thread;

	data->start_time = get_time();
	i = 0;
	pthread_create(&monitoring_thread, NULL, monitoring, data);
	while (i < data->number_of_philo)
	{
		pthread_create(&arr_threads[i], NULL, routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_join(arr_threads[i], NULL);
		i++;
	}
	pthread_join(monitoring_thread, NULL);
}
