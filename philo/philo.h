#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
typedef struct s_data s_data;


#define SIZE_MTX_US 3
#define EAT 0
#define	PRINT 1
#define DEATH 2

typedef struct s_philo
{
	int	id;
	int	fork_l;
	int	fork_r;
	pthread_mutex_t	print;
	size_t	last_meal;
	struct s_data	*data;	
}	t_philo;



typedef struct s_data
{
	int	number_of_philo;
	size_t	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	size_t start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t *used__mtx;
	t_philo *philos;
	int	flag_death;

}	t_data;




int		ft_strlen(char *str);
int		ft_isdigit(int c);
long	ft_atoi(const char *str);
long	ft_atoi_err(const char *str, int *err);
void	creat_threads(t_data *data);
size_t	get_time();
void	ft_printstatus(t_philo *philo, char *status);
int		ft_usleep(size_t milliseconds);
bool	check_death(t_data *data);