/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:16:27 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/12 01:18:21 by mamartin         ###   ########.fr       */
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

/*
**	STATS ABOUT PHILOSOPHERS MEALS
*/

typedef struct	s_philo_meals
{
	struct timeval	last_meal;
	int				nb_meals;
}				t_philo_meals;

/*
**	PARAMETER FOR EACH PHILOSOPHER'S THREAD
*/

typedef struct	s_philo
{
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nb_philo;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*output_mutex;
	t_philo_meals	*meals;
	struct timeval	exec_time;
}				t_philo;

/*
**	MAIN STRUCTURE TO STORE ARGUMENTS
*/

typedef struct	s_info
{
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nb_must_eat;
	int				nb_philo;
	struct timeval	exec_time;
	t_philo			**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	output_mutex;
	t_philo_meals	*meals;
}				t_info;

/*
**	INIT FUNCTIONS
*/

t_info			*init_philo_info(int argc, char **argv);
pthread_mutex_t	*init_forks_mutexes(int size);
pthread_t		*init_philos_threads(t_info *info);
t_philo			*init_philo(t_info *info, int i);
t_philo_meals	*init_philos_meals(int size, struct timeval exec_time);

/*
**	SUPERVISOR FUNCTIONS
*/

int				check_meals(t_info *info);

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
void			print_timestamp(struct timeval exec_timestamp);

#endif
