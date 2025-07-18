#include "philo.h"

void *test_function(void *args)
{
	t_philo *philos;

	philos = (t_philo *)args;
	printf("philos id ==> %d\n", philos->id);
	return NULL;
}

void	creat_threads(t_data *data)
{
	int i;
	pthread_t arr_threads[data->number_of_philo];

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_create(&arr_threads[i], NULL, &test_function, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_join(arr_threads[i], NULL);
		i++;
	}
}
