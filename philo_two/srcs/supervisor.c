/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 22:01:40 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/29 01:34:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_two.h"

void	*supervisor_func(void *ptr_info)
{
	t_info			*info;
	int				least_times_eaten;
	int				i;

	info = (t_info *)ptr_info;
	while (1)
	{
		i = 0;
		least_times_eaten = info->philos[i]->meals.nb_meals;
		while (i < info->nb_philo)
		{
			check_forks(info, info->philos[i]);
			if (check_deaths(info, i) != 0)
				return (NULL);
			if (least_times_eaten > info->philos[i]->meals.nb_meals)
				least_times_eaten = info->philos[i]->meals.nb_meals;
			i++;
		}
		if (check_meals(info, least_times_eaten) == 0)
			return (NULL);
		usleep(100);
	}
}

int	check_deaths(t_info *info, int n)
{
	long	last_meal;

	sem_wait(info->philos[n]->death_mutex);
	last_meal = get_timestamp(info->exec_tm) - info->philos[n]->meals.last_meal;
	if (last_meal >= info->time_to_die)
	{
		print_log("%d died\n", info->philos[n]);
		sem_wait(info->alive_mutex);
		info->is_alive = FALSE;
		sem_post(info->alive_mutex);
		sem_post(info->philos[n]->death_mutex);
		return (-1);
	}
	sem_post(info->philos[n]->death_mutex);
	return (0);
}

int	check_meals(t_info *info, int least)
{
	if (info->nb_must_eat != -1 && least >= info->nb_must_eat)
	{
		sem_wait(info->alive_mutex);
		info->is_alive = FALSE;
		sem_post(info->alive_mutex);
		return (0);
	}
	return (-1);
}

void	check_forks(t_info *info, t_philo *philo)
{
	int		priority;
	int		i;

	if (philo->meals.need_forks)
	{
		i = 0;
		priority = 0;
		while (i < info->nb_philo)
		{
			if (philo->meals.last_meal < info->philos[i]->meals.last_meal)
				priority++;
			i++;
		}
		if (info->forks_available > 0
			&& info->nb_philo - priority >= info->forks_available / 2)
		{
			philo->meals.need_forks = FALSE;
			info->forks_available -= 2;
		}
	}
}
