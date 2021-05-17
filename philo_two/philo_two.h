/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:16:27 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/17 02:39:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>

# define FALSE	0
# define TRUE	1

typedef int	t_bool;

/*
**	STATS ABOUT PHILOSOPHERS MEALS
*/

typedef struct s_philo_meals
{
	long			last_meal;
	int				nb_meals;
	t_bool			need_forks;
}	t_philo_meals;

/*
**	PARAMETER FOR EACH PHILOSOPHER'S THREAD
*/

typedef struct s_philo
{
	int				nb_philo;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	pthread_mutex_t	*output_mutex;
	pthread_mutex_t	death_mutex;
	t_philo_meals	meals;
	t_bool			*is_alive;
	long			exec_tm;
}	t_philo;

/*
**	MAIN STRUCTURE TO STORE ARGUMENTS
*/

typedef struct s_info
{
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nb_must_eat;
	int				nb_philo;
	long			exec_tm;
	t_philo			**philos;
	pthread_mutex_t	output_mutex;
	t_bool			is_alive;
}	t_info;

/*
**	INIT FUNCTIONS
*/

t_info			*init_philo_info(int argc, char **argv);
pthread_t		*init_philos_threads(t_info *info);
t_philo			*init_philo(t_info *info, int i);
t_philo_meals	*init_philos_meals(int size);

int				get_arg_info(t_info *info, int argc, char **argv);

/*
**	SUPERVISOR FUNCTIONS
*/

void			*supervisor_func(void *ptr_info);
int				check_deaths(t_info *info, int n);
int				check_meals(t_info *info, int n);

/*
**	PHILOSOPHER ROUTINE
*/

void			*philo_routine(void *info);
void			eat(t_philo *philo);
void			sleeping(t_philo *philo);
void			think(t_philo *philo);

/*
**	SOME USEFUL FUNCTIONS
*/

int				ft_atoi(const char *nptr);
void			print_log(char *output, t_philo *philo);
long			get_timestamp(long exec_tm);
void			ft_msleep(int time);
void			free_all(t_info *info, pthread_t *th);

#endif
