#include "philo.h"

long long	get_time(void)
{
	struct timeval		tv;
	long long			m_sec;
	static long long start_time; 

	gettimeofday(&tv, NULL);
	m_sec = tv.tv_sec * 1000;
	m_sec += (tv.tv_usec / 1000);
	if (!start_time)
		start_time = m_sec;
	return (m_sec - start_time);
}

void	ft_printstatus(t_philo *philo, char *status)
{	
	pthread_mutex_lock(&(philo->data->used__mtx[PRINT]));
	if (philo->data->flag_death == 0)
		printf("%lld %d %s \n", get_time() , philo->id, status);
	pthread_mutex_unlock(&(philo->data->used__mtx[PRINT]));
}

int ft_usleep(long long milliseconds, t_data *data)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		if(check_death(data))
			return 0;
		usleep(500);
	}
	return (0);
}

bool check_death(t_data *data)
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
