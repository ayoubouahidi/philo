#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
typedef struct s_data s_data;

typedef struct s_philo
{
	int	id;
	int	fork_l;
	int	fork_r;
	// pthread_mutex_t	print;
	
	struct s_data	*data;	
}	t_philo;

typedef struct s_data
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	pthread_mutex_t *forks;
	t_philo *philos;
}	t_data;




int		ft_strlen(char *str);
int		ft_isdigit(int c);
long	ft_atoi(const char *str);
long	ft_atoi_err(const char *str, int *err);
void	creat_threads(t_data *data);