/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 10:38:35 by galpers           #+#    #+#             */
/*   Updated: 2022/06/10 19:00:30 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	return (-1);
}

long long	find_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	check_time(long long time, t_philo *philo)
{
	long long	t;

	t = find_time();
	while (!stop_check(philo))
	{
		if (find_time() - t >= time)
			break ;
		usleep(500);
	}
}

int	stop_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_stop);
	if (philo->data->stop == 0)
	{
		pthread_mutex_unlock(&philo->data->mutex_stop);
		return (0);
	}
	return (1);
}

void	philo_print_death(t_philo *philo, char *str, t_philo *philos)
{
	printf("%lld %d %s\n", \
			find_time() - philo->data->t_start, philo->index, str);
	pthread_mutex_lock(&philo->data->mutex_stop);
	philos->data->stop = 1;
	pthread_mutex_unlock(&philo->data->mutex_stop);
}
