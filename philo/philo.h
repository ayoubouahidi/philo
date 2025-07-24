/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:51:22 by ayouahid          #+#    #+#             */
/*   Updated: 2025/07/24 15:51:23 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define SIZE_MTX_US 9
#define EAT 0
#define PRINT 1
#define DEATH 2
#define MEAL 3
#define FINISH 4
#define MEAL_COUNT 5
#define GLB_FINISH 6
#define SIM 7
#define TIME_MUTEX 8

typedef struct s_data	t_data;
typedef struct s_philo
{
	int					id;
	int					fork_l;
	int					fork_r;
	int					meal_count;
	size_t				last_meal;
	struct s_data		*data;
	int					finish_eating;
}						t_philo;

typedef struct s_data
{
	int					number_of_philo;
	size_t				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*used__mtx;

	t_philo				*philos;
	int					flag_death;
	int					sim;
	int					philos_finished_eating;
	long long			start_time;
}						t_data;

int						ft_strlen(char *str);
int						ft_isdigit(int c);
long					ft_atoi(const char *str);
long					ft_atoi_err(const char *str, int *err);
void					creat_threads(t_data *data);
long long				get_time(t_data *data);
void					ft_printstatus(t_philo *philo, char *status);
bool					check_death(t_data *data);
int						ft_usleep(long long milliseconds, t_data *data);
void					free_data(t_data *data);
bool					check_args(int ac, char **av);
void					eating_meals(t_philo *philo, int finished_eating);
void					check_if_number_one(t_philo *philo);
void					put_forks(t_philo *philo);
void					take_fork(t_philo *philo);
void					free_data(t_data *data);
int						all_philos_eating(t_data *data);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					eating(t_philo *philo);
void					eating_print(t_philo *philo);
int						check_end(t_data *data);
int						ft_strlen(char *str);
bool					check_each_arg(char *av);
void					eating_print(t_philo *philo);
void					end_sim(t_data *data);
