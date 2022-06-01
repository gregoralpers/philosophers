/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <galpers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:58:02 by galpers           #+#    #+#             */
/*   Updated: 2022/06/01 16:32:13 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_atoi(const char *str)
{
	long int	n;
	int			max_int;

	max_int = 2147483647;
	while (*str == ' ' || *str == '\f' || *str == '\n' || \
			*str == '\r' || *str == '\t' || *str == '\v')
		str++;
	n = 0;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		if (n > max_int)
			return (-1);
		str++;
	}
	if (*str != '\0' || n == 0)
		return (-1);
	return ((int)n);
}

static t_philo	*init_data(int argc, char **argv)
{
	t_philo	*tmp;

	tmp = (t_philo *)malloc(sizeof(t_philo));
	if (!tmp)
		ft_error("Error: Failed to malloc philo");
	tmp->num_philos = ft_atoi(argv[1]);
	tmp->num_forks = tmp->num_philos;
	tmp->t_die = ft_atoi(argv[2]);
	tmp->t_eat = ft_atoi(argv[3]);
	tmp->t_sleep = ft_atoi(argv[4]);
	if (tmp->num_philos < 1 || tmp->num_philos > 250 || tmp->t_die == -1 || \
		tmp->t_eat == -1 || tmp->t_sleep == -1)
		ft_error("Error: Wrong arguments");
	tmp->num_eat = -1;
	if (argc == 6)
	{
		tmp->num_eat = ft_atoi(argv[5]);
		if (tmp->num_eat == -1)
			ft_error("Error: Wrong arguments");
	}
	tmp->num_eat_count = 0;
	tmp->stop = 0;
	tmp->died = 0;
	return (tmp);
}

t_philo	*init_philo(int argc, char **argv)
{
	t_philo	*tmp;

	if (argc < 5 || argc > 6)
		ft_error("Error: Wrong number of arguments");
	tmp = init_data(argc, argv);
	tmp->pid = (int *)malloc(sizeof(int) * tmp->num_forks);
	if (!tmp->pid)
		ft_error("Error: malloc error (init pid)");
	sem_unlink("/block_print");
	sem_unlink("/block_forks");
	sem_unlink("/block_stop");
	sem_unlink("/block_t_meal");
	sem_unlink("/block_meal_count");
	tmp->block_printf = sem_open("/block_print", O_CREAT, 0644, 1);
	tmp->block_fork = sem_open("/block_forks", O_CREAT, \
								0644, tmp->num_forks);
	tmp->block_stop = sem_open("/block_stop", O_CREAT, 0644, 1);
	tmp->block_t_meal = sem_open("/block_t_meal", O_CREAT, 0644, 1);
	tmp->block_meal_count = sem_open("/block_meal_count", O_CREAT, 0644, 1);
	if (tmp->block_printf == SEM_FAILED || tmp->block_fork == SEM_FAILED || \
		tmp->block_stop == SEM_FAILED || tmp->block_t_meal == SEM_FAILED || \
		tmp->block_meal_count == SEM_FAILED)
		ft_error("Error: semaphore open error");
	return (tmp);
}
