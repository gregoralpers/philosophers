/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <galpers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 10:11:02 by galpers           #+#    #+#             */
/*   Updated: 2022/06/01 13:15:57 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philos;
	int				num_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	int				stop;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	mutex_meal_time;
	pthread_mutex_t	mutex_meal_count;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_printf;
	long long int	t_start;
	pthread_t		check_monitor;
}t_data;

typedef struct s_philo
{
	int				index;
	int				num_eat_count;
	long long int	t_meal;
	t_data			*data;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	pthread_t		p_thread;
}t_philo;

//initiation
int			init_philos(t_philo **philos, int argc, char **argv);

//utility
int			ft_error(char *str);
long long	find_time(void);
void		check_time(long long time, t_philo *philo);
void		philo_print_death(t_philo *philo, char *str, t_philo *philos);
int			stop_check(t_philo *philo);
void		update_meal_time(t_philo *philo);
int			check_meal_time(t_philo *philos, int i);
int			check_meal_count(t_philo *philos, int i);
void		update_meal_count(t_philo *philo);
void		number_of_meals_reached(t_philo *philo);

#endif
