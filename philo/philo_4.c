#include "philo.h"

int	check_end(t_data *data)
{
	pthread_mutex_lock(&(data->used__mtx[SIM]));
	if (data->sim == 1)
	{
		pthread_mutex_unlock(&(data->used__mtx[SIM]));
		return (1);
	}
	pthread_mutex_unlock(&(data->used__mtx[SIM]));
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}