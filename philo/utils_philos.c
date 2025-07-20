#include "philo.h"

size_t	get_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "error\n", 6);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_printstatus(t_philo *philo, char *status)
{
	pthread_mutex_lock(&(philo->data->used__mtx[PRINT]));
	printf("%lu %d %s \n", get_time() - philo->data->start_time, philo->id, status);
	pthread_mutex_unlock(&(philo->data->used__mtx[PRINT]));
}

int ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

bool check_death(t_data *data)
{
	pthread_mutex_lock(&(data->used__mtx[DEATH]));
	if (data->flag_death)
	{
		printf("=======================DEBUUUUUG : FLAG IS 1 =======================");
		pthread_mutex_unlock(&(data->used__mtx[DEATH]));
		return (true);
	}
	pthread_mutex_unlock(&(data->used__mtx[DEATH]));
	return (false);
}
