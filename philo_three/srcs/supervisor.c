/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:59:05 by user42            #+#    #+#             */
/*   Updated: 2021/05/30 16:27:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_three.h"

void	*monitoring(void *ptr)
{
	t_philo	*philo;
	t_bool	is_sated;
	long	last_meal;

	is_sated = FALSE;
	philo = (t_philo *)ptr;
	while (philo->is_alive)
	{
		sem_wait(philo->death_sem);
		last_meal = get_timestamp(philo->exec_tm) - philo->meals.last_meal;
		if (last_meal >= philo->time_to_die)
			return (kill_philos(philo));
		sem_post(philo->death_sem);
		if (!is_sated && philo->meals.nb_meals >= philo->nb_must_eat)
		{
			sem_post(philo->meals_count_sem);
			is_sated = TRUE;
		}
		usleep(60);
	}
	return (NULL);
}

void	*check_deaths(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	sem_wait(philo->alive_sem);
	philo->is_alive = FALSE;
	sem_post(philo->alive_sem);
	return (NULL);
}

void	*kill_philos(t_philo *philo)
{
	print_log("%d died\n", philo);
	sem_wait(philo->output_sem);
	sem_post(philo->alive_sem);
	sem_post(philo->death_sem);
	ft_msleep(100);
	sem_post(philo->output_sem);
	return (NULL);
}
