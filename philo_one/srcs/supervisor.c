/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 22:01:40 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/16 19:42:42 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

void	*check_meals(void *ptr_info)
{
	t_info			*info;
	long			last_meal;
	int				least_times_eaten;
	int				i;

	info = (t_info*)ptr_info;
	while (1)
	{
		i = 0;
		least_times_eaten = info->meals[i].nb_meals;
		while (i < info->nb_philo)
		{
			if (info->philos[i]->meals->need_forks)
				check_forks(info, i);

			pthread_mutex_lock(&info->philos[i]->death_mutex);
			last_meal = get_timestamp(info->exec_tm) - info->meals[i].last_meal;
			if (last_meal >= info->time_to_die)
			{
				print_log("%d died\n", info->philos[i]);
				info->is_alive = FALSE;
				pthread_mutex_unlock(&info->philos[i]->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&info->philos[i]->death_mutex);
			
			if (least_times_eaten > info->meals[i].nb_meals)
				least_times_eaten = info->meals[i].nb_meals;
			i++;
		}
		if (info->nb_must_eat != -1 && least_times_eaten >= info->nb_must_eat)
		{
			info->is_alive = FALSE;
			return (NULL);
		}
		usleep(500);
	}
}

void	check_forks(t_info *info, int philo)
{
	int		i;
	
	i = philo + 1;
	if (philo == info->nb_philo - 1)
		i = 0;

	// are forks taken ?
	if (info->forks_available[philo] && info->forks_available[i])
	{
		info->philos[philo]->meals->need_forks = FALSE;
		info->forks_available[philo] = FALSE;
		info->forks_available[i] = FALSE;
	}
}
