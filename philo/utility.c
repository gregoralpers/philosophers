/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 10:38:35 by galpers           #+#    #+#             */
/*   Updated: 2022/05/31 16:59:18 by galpers          ###   ########.fr       */
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

void	check_sleep(long long time, t_data *data)
{
	long long	t;

	t = find_time();
	while (!data->stop)
	{
		if (find_time() - t >= time)
			break ;
		usleep(50);
	}
}

void	check_eat(long long time, t_data *data)
{
	long long	t;

	t = find_time();
	while (!data->stop)
	{
		if (find_time() - t >= time)
			break ;
		usleep(50);
	}
}


void	philo_print_death(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_printf);
	if (!philo->data->stop)
		printf("%lld %d %s\n", \
			find_time() - philo->data->t_start, philo->index, str);
}