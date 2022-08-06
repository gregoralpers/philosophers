/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:41:24 by galpers           #+#    #+#             */
/*   Updated: 2022/06/01 19:20:42 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal_time(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos->data->mutex_meal_time);
	if (find_time() - (philos + i)->t_meal >= philos->data->t_die)
	{
		pthread_mutex_unlock(&philos->data->mutex_meal_time);
		return (1);
	}
	pthread_mutex_unlock(&philos->data->mutex_meal_time);
	return (0);
}

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_meal_time);
	philo->t_meal = find_time();
	pthread_mutex_unlock(&philo->data->mutex_meal_time);
}

int	check_meal_count(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos->data->mutex_meal_count);
	if (philos->data->num_eat != -1 && \
				(philos + i)->num_eat_count >= philos->data->num_eat)
	{
		pthread_mutex_unlock(&philos->data->mutex_meal_count);
		return (1);
	}
	pthread_mutex_unlock(&philos->data->mutex_meal_count);
	return (0);
}

void	update_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_meal_count);
	philo->num_eat_count += 1;
	pthread_mutex_unlock(&philo->data->mutex_meal_count);
}

void	number_of_meals_reached(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->mutex_stop);
}
