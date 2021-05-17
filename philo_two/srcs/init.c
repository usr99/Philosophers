/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:42:37 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/17 02:38:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_two.h"

t_info	*init_philo_info(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	if (get_arg_info(info, argc, argv) == -1)
		return (NULL);
	info->exec_tm = get_timestamp(0);
	info->is_alive = TRUE;
	pthread_mutex_init(&info->output_mutex, NULL);
	return (info);
}

t_philo_meals	*init_philos_meals(int size)
{
	t_philo_meals	*meals;
	int				i;

	meals = (t_philo_meals *)malloc(sizeof(t_philo_meals) * size);
	if (!meals)
		return (NULL);
	i = 0;
	while (i < size)
	{
		meals[i].last_meal = 0;
		meals[i].nb_meals = 0;
		meals[i].need_forks = FALSE;
		i++;
	}
	return (meals);
}

pthread_t	*init_philos_threads(t_info *info)
{
	pthread_t	*th_philos;
	t_philo		*curr;
	int			i;

	th_philos = (pthread_t *)malloc(sizeof(pthread_t) * info->nb_philo);
	info->philos = (t_philo **)malloc(sizeof(t_philo *) * info->nb_philo);
	if (!th_philos || !info->philos)
		return (NULL);
	i = 0;
	while (i < info->nb_philo)
	{
		curr = init_philo(info, i);
		if (!curr)
			return (NULL);
		pthread_create(th_philos + i, NULL, &philo_routine, curr);
		info->philos[i] = curr;
		i++;
	}
	return (th_philos);
}

t_philo	*init_philo(t_info *info, int i)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->nb_philo = i + 1;
	new->time_to_eat = info->time_to_eat;
	new->time_to_sleep = info->time_to_sleep;
	new->output_mutex = &info->output_mutex;
	new->exec_tm = info->exec_tm;
	new->is_alive = &info->is_alive;
	new->meals.need_forks = FALSE;
	new->meals.last_meal = 0;
	new->meals.nb_meals = 0;
	pthread_mutex_init(&new->death_mutex, NULL);
	return (new);
}
