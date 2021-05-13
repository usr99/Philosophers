/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:36:24 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/12 02:00:30 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

int		main(int argc, char **argv)
{
	t_info			*philo_info;
	pthread_t		*th_philos;

	if (argc < 5 || argc > 6)
		return (-1);
	philo_info = init_philo_info(argc, argv);
	if (!philo_info)
		return (-1);
	th_philos = init_philos_threads(philo_info);
	if (!th_philos)
		return (-1);

	while (check_meals(philo_info) == 0)
		usleep(500);

	return (0);
}

int		check_meals(t_info *info)
{
	struct timeval	tm;
	unsigned long	last_meal;
	int				least_times_eaten;
	int				i;

	i = 0;
	least_times_eaten = info->meals[i].nb_meals;
	while (i < info->nb_philo)
	{
		//pthread_mutex_lock(&info->death_mutex[i]);
		gettimeofday(&tm, NULL);
		last_meal = (tm.tv_sec - info->meals[i].last_meal.tv_sec) * 1000000;
		last_meal += (tm.tv_usec - info->meals[i].last_meal.tv_usec);
		last_meal /= 1000;
		if (last_meal > info->time_to_die)
		{
			print_log("%d died\n", info->philos[i]);
			return (-1);
		}
		//pthread_mutex_unlock(&info->death_mutex[i]);
		if (least_times_eaten > info->meals[i].nb_meals)
			least_times_eaten = info->meals[i].nb_meals;
		i++;
	}
	if (info->nb_must_eat != -1 && least_times_eaten >= info->nb_must_eat)
		return (-1);
	return (0);
}
