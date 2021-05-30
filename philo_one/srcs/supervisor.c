/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 22:01:40 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/30 15:53:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

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
			if (info->philos[i]->meals.need_forks)
				check_forks(info, i);
			if (check_deaths(info, i) != 0)
				return (NULL);
			if (least_times_eaten > info->philos[i]->meals.nb_meals)
				least_times_eaten = info->philos[i]->meals.nb_meals;
			i++;
		}
		if (check_meals(info, least_times_eaten) == 0)
			return (NULL);
		usleep(60);
	}
}

void	check_forks(t_info *info, int philo)
{
	int		i;

	i = philo + 1;
	if (philo == info->nb_philo - 1)
		i = 0;
	if (info->forks_available[philo] && info->forks_available[i])
	{
		info->philos[philo]->meals.need_forks = FALSE;
		info->forks_available[philo] = FALSE;
		info->forks_available[i] = FALSE;
	}
}

int	check_deaths(t_info *info, int n)
{
	long	last_meal;

	pthread_mutex_lock(&info->philos[n]->death_mutex);
	last_meal = get_timestamp(info->exec_tm) - info->philos[n]->meals.last_meal;
	if (last_meal >= info->time_to_die)
	{
		print_log("%d died\n", info->philos[n]);
		pthread_mutex_lock(&info->alive_mutex);
		info->is_alive = FALSE;
		pthread_mutex_unlock(&info->alive_mutex);
		pthread_mutex_unlock(&info->philos[n]->death_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&info->philos[n]->death_mutex);
	return (0);
}

int	check_meals(t_info *info, int least)
{
	if (info->nb_must_eat != -1 && least >= info->nb_must_eat)
	{
		pthread_mutex_lock(&info->alive_mutex);
		info->is_alive = FALSE;
		pthread_mutex_unlock(&info->alive_mutex);
		return (0);
	}
	return (-1);
}
