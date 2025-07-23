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

void	eating(t_philo *philo)
{
	int	finished_eating;

	finished_eating = 0;
	pthread_mutex_lock(&(philo->data->used__mtx[FINISH]));
	if (philo->finish_eating)
	{
		pthread_mutex_unlock(&(philo->data->used__mtx[FINISH]));
		return ;
	}
	pthread_mutex_unlock(&(philo->data->used__mtx[FINISH]));
	take_fork(philo);
	ft_printstatus(philo, "is eating");
	pthread_mutex_lock(&(philo->data->used__mtx[MEAL_COUNT]));
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->data->used__mtx[MEAL_COUNT]));
	pthread_mutex_lock(&(philo->data->used__mtx[MEAL]));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->data->used__mtx[MEAL]));
	ft_usleep(philo->data->time_to_eat, philo->data);
	// printf("DEBUG :philo id : %d meal_count is %d\n", philo->id, philo->meal_count);
	pthread_mutex_lock(&(philo->data->used__mtx[MEAL_COUNT]));
	if (philo->data->number_of_times_each_philosopher_must_eat != -1 && philo->meal_count == philo->data->number_of_times_each_philosopher_must_eat)
		finished_eating = 1;
	pthread_mutex_unlock(&(philo->data->used__mtx[MEAL_COUNT]));
	if (finished_eating)
	{
		// printf("im here philo id %d\n", philo->id);
		pthread_mutex_lock(&(philo->data->used__mtx[GLB_FINISH]));
		philo->data->philos_finished_eating++;
		pthread_mutex_unlock(&(philo->data->used__mtx[GLB_FINISH]));
		pthread_mutex_lock(&(philo->data->used__mtx[FINISH]));
		philo->finish_eating = 1;
		pthread_mutex_unlock(&(philo->data->used__mtx[FINISH]));
	}
	put_forks(philo);
}

void	sleeping(t_philo *philo)
{
	ft_printstatus(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	thinking(t_philo *philo)
{
	ft_printstatus(philo, "is thinking");
	if (philo->data->number_of_philo % 2 == 1)
		ft_usleep(15, philo->data);
}

int	all_philos_eating(t_data *data)
{
	int result;

	result = 0;
	if (data->number_of_times_each_philosopher_must_eat == -1)
		return 0;
	pthread_mutex_lock(&(data->used__mtx[GLB_FINISH]));
	if (data->philos_finished_eating >= data->number_of_philo)
		result = 1;
	pthread_mutex_unlock(&(data->used__mtx[GLB_FINISH]));
	return (result);
}

void	*routine(void *args)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo *)args;
	void (*ptr[])(t_philo *) = {eating, sleeping, thinking};
	if (philo->id % 2 != 0)
		usleep(500);
	check_if_number_one(philo);
	while (1)
	{
		if (all_philos_eating(philo->data) || check_death(philo->data))
			return (NULL);
		i %= 3;
		ptr[i](philo);
		i++;
	}
}

void	monitoring(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->number_of_philo )
		{
			if (all_philos_eating(data))
			{
				printf("all philos have eaten\n");
				exit(0) ;
				return ;
			}
			pthread_mutex_lock(&(data->used__mtx[MEAL]));
			if (get_time() - data->philos[i].last_meal > data->time_to_die)
			{
				pthread_mutex_unlock(&data->used__mtx[MEAL]);
				pthread_mutex_lock(&(data->used__mtx[PRINT]));
				pthread_mutex_lock(&(data->used__mtx[DEATH]));
				data->flag_death = 1;
				printf("%lld %d %s \n", get_time(), data->philos[i].id, "died");
				pthread_mutex_unlock(&(data->used__mtx[DEATH]));
				pthread_mutex_unlock(&(data->used__mtx[PRINT]));
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
}
