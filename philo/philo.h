#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
typedef struct s_data	s_data;

#define SIZE_MTX_US 4
#define EAT 0
#define PRINT 1
#define DEATH 2
#define MEAL 3


typedef struct s_philo
{
	int					id;
	int					fork_l;
	int					fork_r;
	int					meal_count;
	size_t				last_meal;
	struct s_data		*data;
}						t_philo;

typedef struct s_data
{
	int					number_of_philo;
	size_t				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	size_t				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*used__mtx;
	t_philo				*philos;
	int					flag_death;

}						t_data;

int						ft_strlen(char *str);
int						ft_isdigit(int c);
long					ft_atoi(const char *str);
long					ft_atoi_err(const char *str, int *err);
void					creat_threads(t_data *data);
long long				get_time(void);
void					ft_printstatus(t_philo *philo, char *status);
bool					check_death(t_data *data);
int						ft_usleep(long long milliseconds, t_data *data);