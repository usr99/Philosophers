/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:36:12 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/12 01:59:07 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	*philo_routine(void *info)
{
	t_philo			*philo;

	philo = (t_philo*)info;
	usleep(philo->time_to_eat * 1000 * (philo->nb_philo % 2) / 2);
	while (1) // routine loop
	{
		// eat
		eat(philo);
		// sleep
		sleeping(philo);
		// think
		think(philo);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	// lock fork 0
	pthread_mutex_lock(philo->forks[0]);
	print_log("%d has taken a fork\n", philo);

	// lock fork 1
	pthread_mutex_lock(philo->forks[1]);
	print_log("%d has taken a fork\n", philo);

	// lock le mutex du die
	//pthread_mutex_lock(philo->death_mutex);

	// update meal structure
	gettimeofday(&philo->meals->last_meal, NULL);
	philo->meals->nb_meals++;

	// unlock mutex du die
	//pthread_mutex_unlock(philo->death_mutex);

	// eat
	print_log("%d is eating\n", philo);
	usleep(philo->time_to_eat * 1000);

	// unlock forks
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
}

void	sleeping(t_philo *philo)
{
	print_log("%d is sleeping\n", philo);
	usleep(philo->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_log("%d is thinking\n", philo);
}
