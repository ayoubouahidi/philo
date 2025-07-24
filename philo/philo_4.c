/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:34:32 by ayouahid          #+#    #+#             */
/*   Updated: 2025/07/24 15:34:33 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	eating_print(t_philo *philo)
{
	take_fork(philo);
	ft_printstatus(philo, "is eating");
}

void	end_sim(t_data *data)
{
	pthread_mutex_lock(&(data->used__mtx[SIM]));
	data->sim = 1;
	pthread_mutex_unlock(&(data->used__mtx[SIM]));
}
