/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:36:12 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/21 17:40:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_two.h"

void	*philo_routine(void *info)
{
	t_philo			*philo;

	philo = (t_philo *)info;
	ft_msleep(philo->time_to_eat * (philo->nb_philo % 2) / 2);
	sem_wait(philo->alive_mutex);
	while (*philo->is_alive)
	{
		sem_post(philo->alive_mutex);
		eat(philo);
		sleeping(philo);
		think(philo);
		sem_wait(philo->alive_mutex);
	}
	sem_post(philo->alive_mutex);
	return (NULL);
}

void	eat(t_philo *philo)
{
	fork_request(philo);
	sem_wait(philo->death_mutex);
	philo->meals.last_meal = get_timestamp(philo->exec_tm);
	philo->meals.nb_meals++;
	sem_post(philo->death_mutex);
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
	while (philo->meals.need_forks && *philo->is_alive)
		usleep(60);
	if (*philo->is_alive == FALSE)
		return ;
	sem_wait(philo->forks);
	print_log("%d has taken a fork\n", philo);
	sem_wait(philo->forks);
	print_log("%d has taken a fork\n", philo);
}
