/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:42:37 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/12 01:28:27 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

t_info			*init_philo_info(int argc, char **argv)
{
	t_info	*info;
	
	info = (t_info*)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	gettimeofday(&info->exec_time, NULL);
	info->nb_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->nb_must_eat = ft_atoi(argv[5]);
	else
		info->nb_must_eat = -1;
	info->forks = init_forks_mutexes(info->nb_philo);
	if (!info->forks)
		return (NULL);
	/*info->death_mutex = init_forks_mutexes(info->nb_philo);
	if (!info->death_mutex)
		return (NULL);*/
	if (pthread_mutex_init(&info->output_mutex, NULL) != 0)
		return (NULL);
	info->meals = init_philos_meals(info->nb_philo, info->exec_time);
	if (!info->meals)
		return (NULL);
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

t_philo_meals	*init_philos_meals(int size, struct timeval exec_time)
{
	t_philo_meals	*meals;
	int				i;

	meals = (t_philo_meals*)malloc(sizeof(t_philo_meals) * size);
	if (!meals)
		return (NULL);
	i = 0;
	while (i < size)
	{
		meals[i].last_meal = exec_time;
		meals[i].nb_meals = 0;
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
		if (pthread_detach(th_philos[i]) != 0)
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
	if (i != info->nb_philo - 1)
		new->forks[1] = &info->forks[i + 1];
	else
		new->forks[1] = &info->forks[0];
	//new->death_mutex = &info->death_mutex[i];
	new->output_mutex = &info->output_mutex;
	new->meals = &info->meals[i];
	new->exec_time = info->exec_time;
	return (new);
}
