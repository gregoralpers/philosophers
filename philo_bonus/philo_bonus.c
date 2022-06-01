/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <galpers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:41:40 by galpers           #+#    #+#             */
/*   Updated: 2022/06/01 16:41:21 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!stop_check(philo))
	{
		if (check_meal_time(philo) == 1)
		{
			philo->died = 1;
			sem_wait(philo->block_printf);
			printf("%lld %d %s\n", \
					find_time() - philo->t_start, philo->index, "died");
			sem_wait(philo->block_stop);
			philo->stop = 1;
			sem_post(philo->block_stop);
			break ;
		}
		check_meal_count(philo);
	}	
	if (philo->died)
		exit (1);
	else
		exit (0);
}	

void	philo_start(t_philo *philo)
{
	if (pthread_create(&philo->check_monitor, \
			NULL, &check_monitor, philo))
		ft_error("Error: Failed to create the thread");
	if (philo->index % 2 == 0)
		usleep(5);
	while (!stop_check(philo))
	{
		philo_print(philo, "is thinking");
		sem_wait(philo->block_fork);
		philo_print(philo, "has taken a fork");
		sem_wait(philo->block_fork);
		philo_print(philo, "has taken a fork");
		philo_print(philo, "is eating");
		check_sleep(philo->t_eat, philo);
		update_meal_time(philo);
		sem_post(philo->block_fork);
		sem_post(philo->block_fork);
		update_meal_count(philo);
		philo_print(philo, "is sleeping");
		check_sleep(philo->t_sleep, philo);
	}
	if (pthread_join(philo->check_monitor, NULL))
		ft_error("Error: Failed to join the thread");
}

void	exit_philo(t_philo **philo)
{
	t_philo	*tmp;
	int		i;
	int		status;

	tmp = *philo;
	i = 0;
	while (i < tmp->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < tmp->num_philos)
				kill(tmp->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(tmp->block_printf);
	sem_close(tmp->block_fork);
	sem_close(tmp->block_stop);
	sem_close(tmp->block_t_meal);
	sem_close(tmp->block_meal_count);
	sem_unlink("/block_print");
	sem_unlink("/block_forks");
	sem_unlink("/block_stop");
	sem_unlink("/block_t_meal");
	sem_unlink("/block_meal_count");
	free(tmp->pid);
	free(tmp);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;

	philo = init_philo(argc, argv);
	i = -1;
	philo->t_start = find_time();
	while (++i < philo->num_philos)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			ft_error("Error: fork mistake");
		if (philo->pid[i] == 0)
		{
			philo->index = i + 1;
			update_meal_time(philo);
			philo_start(philo);
		}
	}
	exit_philo(&philo);
	return (0);
}
