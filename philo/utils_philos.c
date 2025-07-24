#include "philo.h"

long long	get_time(t_data *data)
{
	struct timeval	tv;
	long long		m_sec;
	long long		result;

	gettimeofday(&tv, NULL);
	m_sec = tv.tv_sec * 1000;
	m_sec += (tv.tv_usec / 1000);
	pthread_mutex_lock(&data->used__mtx[TIME_MUTEX]);
	if (!data->start_time)
		data->start_time = m_sec;
	result = m_sec - data->start_time;
	pthread_mutex_unlock(&data->used__mtx[TIME_MUTEX]);
	return (result);
}

void	ft_printstatus(t_philo *philo, char *status)
{
	pthread_mutex_lock(&(philo->data->used__mtx[PRINT]));
	if (philo->data->flag_death == 0)
		printf("%lld %d %s \n", get_time(philo->data), philo->id, status);
	pthread_mutex_unlock(&(philo->data->used__mtx[PRINT]));
}

int	ft_usleep(long long milliseconds, t_data *data)
{
	long long	start;

	start = get_time(data);
	while ((get_time(data) - start) < milliseconds)
	{
		if (check_death(data))
			return (0);
		usleep(500);
	}
	return (0);
}

bool	check_death(t_data *data)
{
	pthread_mutex_lock(&(data->used__mtx[DEATH]));
	if (data->flag_death)
	{
		pthread_mutex_unlock(&(data->used__mtx[DEATH]));
		return (true);
	}
	pthread_mutex_unlock(&(data->used__mtx[DEATH]));
	return (false);
}

bool	check_each_arg(char *av)
{
	int	i;
	int	err;

	err = 0;
	i = 0;
	if (av[i] == '+')
		i++;
	while (i < ft_strlen(av))
	{
		if (!ft_isdigit(av[i]))
			return (false);
		i++;
	}
	ft_atoi_err(av, &err);
	if (err == 1)
		return (false);
	return (true);
}

