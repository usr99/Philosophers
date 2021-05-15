/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 22:01:40 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/15 02:57:06 by mamartin         ###   ########.fr       */
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

			last_meal = get_timestamp(info->exec_tm) - info->meals[i].last_meal;
			if (last_meal >= info->time_to_die)
			{
				print_log("%d died\n", info->philos[i]);
				info->is_alive = FALSE;
				return (NULL);
			}
			if (least_times_eaten > info->meals[i].nb_meals)
				least_times_eaten = info->meals[i].nb_meals;
			i++;
		}
		if (info->nb_must_eat != -1 && least_times_eaten >= info->nb_must_eat)
		{
			info->is_alive = FALSE;
			return (NULL);
		}
		ft_msleep(1);
	}
}

void	check_forks(t_info *info, int philo)
{
	long	last_meal;
	int		forks_available[2];
	int		i;
	
	// is left fork taken ?
	i = philo - 1;
	if (philo == 0)
		i = info->nb_philo - 1;
	last_meal = get_timestamp(info->exec_tm) - info->meals[i].last_meal;
	if (last_meal >= info->time_to_eat || info->meals[i].last_meal == 0)
		forks_available[0] = TRUE;
	else
		forks_available[0] = FALSE;

	// is right fork taken ?
	i = philo + 1;
	if (philo == info->nb_philo - 1)
		i = 0;
	last_meal = get_timestamp(info->exec_tm) - info->meals[i].last_meal;
	if (last_meal >= info->time_to_eat || info->meals[i].last_meal == 0)
		forks_available[1] = TRUE;
	else
		forks_available[1] = FALSE;

	// if forks available, philo can take them
	if (forks_available[0] == TRUE && forks_available[1] == TRUE)
		info->philos[philo]->meals->need_forks = FALSE;
}
