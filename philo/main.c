#include "philo.h"

t_data	*initialisation_of_vars(char **av)
{
	t_data	*data;
	int i;

	i = 0;
	data = malloc(sizeof(t_data));
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	data->philos = malloc(sizeof(t_philo) * data->number_of_philo);
	while (i < data->number_of_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].fork_l = i + 1;
		data->philos[i].fork_r = i + 2;
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


int	main(int ac, char **av)
{	
	t_data *data;

	if (ac < 5 || ac > 6)
		return (0);
	if (!check_args(ac, av))
		return (0);
	// printf("done !\n");
	data = initialisation_of_vars(av);
	creat_threads(data);
	printf("number of philos is => %d\n", data->number_of_philo);
	return (0);
}
