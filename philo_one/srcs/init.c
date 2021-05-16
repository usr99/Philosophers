/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:42:37 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/16 20:08:14 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

t_info			*init_philo_info(int argc, char **argv)
{
	t_info	*info;
	int		i;
	
	info = (t_info*)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->exec_tm = get_timestamp(0);
	info->nb_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->nb_philo < 1 || info->time_to_die < 1 || info->time_to_eat < 1
		|| info->time_to_sleep < 1)
	{
		printf("Arguments must be non-zero positive integers\n");
		free(info);
		return (NULL);
	}
	if (argc == 6)
		info->nb_must_eat = ft_atoi(argv[5]);
	else
		info->nb_must_eat = -1;
	info->forks = init_forks_mutexes(info->nb_philo);
	if (!info->forks)
		return (NULL);
	if (pthread_mutex_init(&info->output_mutex, NULL) != 0)
		return (NULL);
	info->meals = init_philos_meals(info->nb_philo);
	if (!info->meals)
		return (NULL);
	info->is_alive = TRUE;
	info->forks_available = (bool*)malloc(sizeof(bool) * info->nb_philo);
	if (!info->forks_available)
		return (NULL);
	i = 0;
	while (i < info->nb_philo)
	{
		info->forks_available[i] = TRUE;
		i++;
	}
	return (info);
}

pthread_mutex_t	*init_forks_mutexes(int size)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * size);
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

t_philo_meals	*init_philos_meals(int size)
{
	t_philo_meals	*meals;
	int				i;

	meals = (t_philo_meals*)malloc(sizeof(t_philo_meals) * size);
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

pthread_t		*init_philos_threads(t_info *info)
{
	pthread_t	*th_philos;
	t_philo		*curr;
	int			i;
	
	th_philos = (pthread_t*)malloc(sizeof(pthread_t) * info->nb_philo);
	info->philos = (t_philo**)malloc(sizeof(t_philo*) * info->nb_philo);
	if (!th_philos || !info->philos)
		return (NULL);
	i = 0;
	while (i < info->nb_philo)
	{
		curr = init_philo(info, i);
		if (!curr)
			return (NULL);
		if (pthread_create(th_philos + i, NULL, &philo_routine, curr) != 0)
			return (NULL);
		info->philos[i] = curr;
		i++;
	}
	return (th_philos);
}

t_philo			*init_philo(t_info *info, int i)
{
	t_philo	*new;

	new = (t_philo*)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->nb_philo = i + 1;
	new->time_to_eat = info->time_to_eat;
	new->time_to_sleep = info->time_to_sleep;
	new->forks[0] = &info->forks[i];
	new->forks_available[0] = &info->forks_available[i];
	if (i != info->nb_philo - 1)
	{
		new->forks[1] = &info->forks[i + 1];
		new->forks_available[1] = &info->forks_available[i + 1];
	}
	else
	{
		new->forks[1] = &info->forks[0];
		new->forks_available[1] = &info->forks_available[0];
	}
	new->output_mutex = &info->output_mutex;
	new->meals = &info->meals[i];
	new->exec_tm = info->exec_tm;
	new->is_alive = &info->is_alive;
	new->meals->need_forks = FALSE;
	if (pthread_mutex_init(&new->death_mutex, NULL) != 0)
		return (NULL);
	return (new);
}
