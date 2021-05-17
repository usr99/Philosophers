/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:36:12 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/17 02:39:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_two.h"

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
	pthread_mutex_lock(&philo->death_mutex);
	philo->meals.last_meal = get_timestamp(philo->exec_tm);
	philo->meals.nb_meals++;
	pthread_mutex_unlock(&philo->death_mutex);
	print_log("%d is eating\n", philo);
	ft_msleep(philo->time_to_eat);
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
