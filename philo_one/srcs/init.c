/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:42:37 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/30 15:52:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

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
	pthread_mutex_init(&info->alive_mutex, NULL);
	if (create_forks(info) == -1)
		return (NULL);
	return (info);
}

pthread_mutex_t	*init_forks_mutexes(int size)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(forks + i, NULL) != 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
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
	new->forks[0] = &info->forks[i];
	new->forks_available[0] = &info->forks_available[i];
	if (i != info->nb_philo - 1)
		i = i + 1;
	else
		i = 0;
	new->forks[1] = &info->forks[i];
	new->forks_available[1] = &info->forks_available[i];
	new->output_mutex = &info->output_mutex;
	new->alive_mutex = &info->alive_mutex;
	new->exec_tm = info->exec_tm;
	new->is_alive = &info->is_alive;
	new->meals.need_forks = FALSE;
	new->meals.last_meal = 0;
	new->meals.nb_meals = 0;
	pthread_mutex_init(&new->death_mutex, NULL);
	return (new);
}
