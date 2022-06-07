/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:07:33 by galpers           #+#    #+#             */
/*   Updated: 2022/06/06 10:44:59 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	meal_time(t_philo *philo, int i)
{
	if (i == 0 && find_time() - philo->t_meal > philo->t_die)
		sem_post(philo->block_t_meal);
	else if (i == 1)
		philo->t_meal = find_time();
}

void	check_meal_count(t_philo *philo)
{
	if (philo->num_eat != -1 && \
				philo->num_eat_count >= philo->num_eat)
		sem_post(philo->block_stop);
}

void	update_meal_count(t_philo *philos)
{
	philos->num_eat_count += 1;
}
