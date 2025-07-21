#include "philo.h"

void	initialisation_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < SIZE_MTX_US)
	{
		pthread_mutex_init(&data->used__mtx[i], NULL);
		i++;
	}
}

t_data	*initialisation_of_vars(char **av, int ac)
{
	t_data	*data;
	int i;

	i = 0;
	data = malloc(sizeof(t_data));
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6 && ft_atoi(av[5]) != 0)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	data->philos = malloc(sizeof(t_philo) * data->number_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	data->used__mtx = malloc(sizeof(pthread_mutex_t) * SIZE_MTX_US);
	data->flag_death = 0;
	initialisation_mutex(data);
	while (i < data->number_of_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].fork_l = i ;
		data->philos[i].fork_r = (i + 1) % data->number_of_philo ;
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	return (data);
}

bool	check_each_arg(char *av)
{
	int i;
	int err;

	err = 0;
	i = 0;
	if(av[i] == '+')
		i++;
	while(i < ft_strlen(av))
	{
		if (!ft_isdigit(av[i]) )
			return (false);
		i++;
	}
	ft_atoi_err(av, &err);
	if (err == 1)
		return (false);
	return (true);
}

bool	check_args(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!check_each_arg(av[i]))
			return (false);
		i++;
	}
	return (true);	
}


int	main(int ac, char *av[])
{	
	t_data *data;

	if (ac < 5 || ac > 6)
		return (0);
	if (!check_args(ac, av))
		return (0);
	
	data = initialisation_of_vars(av, ac);
	// printf("NUMBER OF MEALS ==> %d\n", data->number_of_times_each_philosopher_must_eat);
	if (data->number_of_philo == 0 )
	{
		printf("INVALID INPUT\n");
		return (0);
	}
	creat_threads(data);
	return (0);
}
