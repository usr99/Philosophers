/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:36:12 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/22 19:30:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_three.h"

void	*philo_routine(void *info)
{
	t_philo			*philo;

	philo = (t_philo *)info;
	ft_msleep(philo->time_to_eat * (philo->nb_philo % 2) / 2);
	while (TRUE)
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
	sem_wait(philo->death_sem);
	philo->meals.last_meal = get_timestamp(philo->exec_tm);
	philo->meals.nb_meals++;
	sem_post(philo->death_sem);
	print_log("%d is eating\n", philo);
	ft_msleep(philo->time_to_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
	*philo->forks_available += 2;
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
	philo->meals.need_forks = TRUE;
	while (philo->meals.need_forks)
		usleep(60);
	sem_wait(philo->forks);
	print_log("%d has taken a fork\n", philo);
	sem_wait(philo->forks);
	print_log("%d has taken a fork\n", philo);
}
