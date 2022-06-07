/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:41:23 by galpers           #+#    #+#             */
/*   Updated: 2022/06/06 11:36:43 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "semaphore.h"

# include <signal.h>

typedef struct s_philo
{
	int				num_philos;
	int				num_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	int				num_eat_count;
	int				stop;
	int				died;
	int				*pid;
	sem_t			*block_printf;
	sem_t			*block_fork;
	long long int	t_start;
	int				index;
	long long int	t_meal;
	pthread_t		check_monitor;
}t_philo;

//init
t_philo		*init_philo(int argc, char **argv);

//unity
int			ft_error(char *str);
long long	find_time(void);
void		upgrade_sleep(long long time, t_philo *philo);
void		philo_print(t_philo *philo, char *str);
#endif