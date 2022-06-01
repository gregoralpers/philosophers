/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <galpers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:07:33 by galpers           #+#    #+#             */
/*   Updated: 2022/06/01 16:40:27 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_meal_time(t_philo *philos)
{
	sem_wait(philos->block_t_meal);
	if (find_time() - philos->t_meal > philos->t_die)
	{
		sem_post(philos->block_t_meal);
		return (1);
	}
	sem_post(philos->block_t_meal);
	return (0);
}

void	update_meal_time(t_philo *philo)
{
	sem_wait(philo->block_t_meal);
	philo->t_meal = find_time();
	sem_post(philo->block_t_meal);
}

void	check_meal_count(t_philo *philos)
{
	sem_wait(philos->block_meal_count);
	if (philos->num_eat != -1 && \
				philos->num_eat_count >= philos->num_eat)
	{
		sem_post(philos->block_meal_count);
		sem_wait(philos->block_stop);
		philos->stop = 1;
		sem_post(philos->block_stop);
	}
	else
		sem_post(philos->block_meal_count);
}

void	update_meal_count(t_philo *philo)
{
	sem_wait(philo->block_meal_count);
	philo->num_eat_count += 1;
	sem_post(philo->block_meal_count);
}
