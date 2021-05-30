/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:36:12 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/30 16:26:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_three.h"

void	*philo_routine(void *info)
{
	t_philo			*philo;
	pthread_t		monitor;
	pthread_t		death_supervisor;

	philo = (t_philo *)info;
	philo->is_alive = TRUE;
	pthread_create(&monitor, NULL, &monitoring, info);
	pthread_create(&death_supervisor, NULL, &check_deaths, info);
	ft_msleep(philo->time_to_eat * (philo->nb_philo % 2) / 2);
	while (philo->is_alive)
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	pthread_join(monitor, NULL);
	pthread_join(death_supervisor, NULL);
	destroy_philo(philo);
	return (NULL);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->forks);
	print_log("%d has taken a fork\n", philo);
	sem_wait(philo->forks);
	print_log("%d has taken a fork\n", philo);
	sem_wait(philo->death_sem);
	philo->meals.last_meal = get_timestamp(philo->exec_tm);
	philo->meals.nb_meals++;
	sem_post(philo->death_sem);
	print_log("%d is eating\n", philo);
	ft_msleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	sleeping(t_philo *philo)
{
	print_log("%d is sleeping\n", philo);
	ft_msleep(philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_log("%d is thinking\n", philo);
}

void	destroy_philo(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->output_sem);
	sem_close(philo->alive_sem);
	sem_close(philo->death_sem);
	sem_close(philo->meals_count_sem);
	sem_unlink(philo->death_name);
	free(philo->death_name);
	free(philo);
}
