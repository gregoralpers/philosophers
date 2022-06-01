/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <galpers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:00:55 by cdarrell          #+#    #+#             */
/*   Updated: 2022/06/01 13:16:34 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_printf);
	if (stop_check(philo) == 0)
		printf("%lld %d %s\n", \
			find_time() - philo->data->t_start, philo->index, str);
	pthread_mutex_unlock(&philo->data->mutex_printf);
}

void	*start(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (stop_check(philo) == 0)
	{
		philo_print(philo, "is thinking");
		pthread_mutex_lock(philo->lf);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->rf);
		philo_print(philo, "has taken a fork");
		philo_print(philo, "is eating");
		check_time(philo->data->t_eat, philo);
		if (stop_check(philo) == 0)
			update_meal_count(philo);
		update_meal_time(philo);
		philo_print(philo, "is sleeping");
		pthread_mutex_unlock(philo->rf);
		pthread_mutex_unlock(philo->lf);
		check_time(philo->data->t_sleep, philo);
	}
	return (0);
}

void	*check_monitor(void *args)
{
	t_philo	*philos;
	int		i;
	int		flag_all_eat;

	philos = (t_philo *)args;
	while (stop_check(philos) == 0)
	{
		i = -1;
		flag_all_eat = 0;
		while (++i < philos->data->num_philos)
		{
			if (check_meal_time(philos, i))
			{
				philo_print_death(philos + i, "died", philos);
				break ;
			}
			if (check_meal_count(philos, i))
				flag_all_eat++;
		}
		if (flag_all_eat == philos->data->num_philos)
		{
			number_of_meals_reached(philos);
		}
	}
	return (0);
}

void	philo_start(t_philo *philos)
{
	int	i;

	i = -1;
	philos->data->t_start = find_time();
	while (++i < philos->data->num_philos)
	{	
		(philos + i)->t_meal = find_time();
		if (pthread_create(&(philos + i)->p_thread, NULL, &start, philos + i))
			ft_error("Error: Failed to create the thread");
		pthread_detach((philos + i)->p_thread);
		usleep(5);
	}
	if (pthread_create(&philos->data->check_monitor, \
						NULL, &check_monitor, philos))
		ft_error("Error: Failed to create the thread");
	if (pthread_join(philos->data->check_monitor, NULL))
		ft_error("Error: Failed to join the thread");
	i = -1;
	while (++i < philos->data->num_forks)
		pthread_mutex_destroy(&philos->data->mutex_fork[i]);
	pthread_mutex_destroy(&philos->data->mutex_printf);
	pthread_mutex_destroy(&philos->data->mutex_stop);
	pthread_mutex_destroy(&philos->data->mutex_meal_time);
	pthread_mutex_destroy(&philos->data->mutex_meal_count);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		return (ft_error("Error: Wrong number of arguments"));
	if (init_philos(&philos, argc, argv) == -1)
		return (-1);
	philo_start(philos);
	return (0);
}
