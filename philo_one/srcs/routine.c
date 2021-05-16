/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:36:12 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/17 01:27:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	*philo_routine(void *info)
{
	t_philo			*philo;

	philo = (t_philo *)info;
	ft_msleep(philo->time_to_eat * (philo->nb_philo % 2) / 2);
	while (*philo->is_alive)
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	fork_request(philo);
	pthread_mutex_lock(&philo->death_mutex);
	philo->meals->last_meal = get_timestamp(philo->exec_tm);
	philo->meals->nb_meals++;
	pthread_mutex_unlock(&philo->death_mutex);
	print_log("%d is eating\n", philo);
	ft_msleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
	*philo->forks_available[0] = TRUE;
	*philo->forks_available[1] = TRUE;
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

void	fork_request(t_philo *philo)
{
	philo->meals->need_forks = TRUE;
	while (philo->meals->need_forks && *philo->is_alive)
		usleep(500);
	if (*philo->is_alive == FALSE)
		return ;
	pthread_mutex_lock(philo->forks[0]);
	print_log("%d has taken a fork\n", philo);
	pthread_mutex_lock(philo->forks[1]);
	print_log("%d has taken a fork\n", philo);
}
