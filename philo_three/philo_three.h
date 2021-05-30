/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:16:27 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/30 16:24:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>
# include <wait.h>

# define FALSE				0
# define TRUE				1
# define SEM_FORKS_NAME		"SEM_forks"
# define SEM_OUTPUT_NAME	"SEM_output"
# define SEM_ALIVE_NAME		"SEM_alive"
# define SEM_MEALS_NAME		"SEM_meals"

typedef int	t_bool;

/*
**	STATS ABOUT PHILOSOPHERS MEALS
*/

typedef struct s_philo_meals
{
	long			last_meal;
	int				nb_meals;
}	t_philo_meals;

/*
**	PARAMETER FOR EACH PHILOSOPHER'S THREAD
*/

typedef struct s_philo
{
	int				nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nb_must_eat;
	sem_t			*forks;
	sem_t			*output_sem;
	sem_t			*death_sem;
	sem_t			*meals_count_sem;
	sem_t			*alive_sem;
	char			*death_name;
	t_philo_meals	meals;
	t_bool			is_alive;
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
	sem_t			*forks;
	sem_t			*output_sem;
	sem_t			*meals_count_sem;
	sem_t			*alive_sem;
}	t_info;

/*
**	INIT FUNCTIONS
*/

t_info			*init_philo_info(int argc, char **argv);
pid_t			*init_philos_processes(t_info *info);
t_philo			*init_philo(t_info *info, int i);

int				get_arg_info(t_info *info, int argc, char **argv);
char			*ft_itoa(int n);

/*
**	PHILOSOPHER ROUTINE
*/

void			*philo_routine(void *info);
void			eat(t_philo *philo);
void			sleeping(t_philo *philo);
void			think(t_philo *philo);
void			destroy_philo(t_philo *philo);

/*
**	SUPERVISOR
*/

int				wait_meals(t_info *info);
void			wait_processes(t_info *info, pid_t *childs, int pid_meals);

void			*monitoring(void *ptr);
void			*check_deaths(void *ptr);
void			*kill_philos(t_philo *philo);

/*
**	SOME USEFUL FUNCTIONS
*/

int				ft_atoi(const char *nptr);
void			print_log(char *output, t_philo *philo);
long			get_timestamp(long exec_tm);
void			ft_msleep(int time);
void			free_all(t_info *info, pid_t *childs);

#endif
