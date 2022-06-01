/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <galpers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:43:55 by galpers           #+#    #+#             */
/*   Updated: 2022/06/01 15:12:19 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	exit(-1);
}

long long	find_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	check_sleep(long long time, t_philo *philo)
{
	long long	t;

	t = find_time();
	while (stop_check(philo) == 0)
	{
		if (find_time() - t >= time)
			break ;
		usleep(500);
	}
}

void	philo_print(t_philo *philo, char *str)
{
	sem_wait(philo->block_printf);
	if (stop_check(philo) == 0)
		printf("%lld %d %s\n", find_time() - philo->t_start, philo->index, str);
	sem_post(philo->block_printf);
}

int	stop_check(t_philo *philo)
{
	sem_wait(philo->block_stop);
	if (philo->stop == 0)
	{
		sem_post(philo->block_stop);
		return (0);
	}
	sem_post(philo->block_stop);
	return (1);
}
