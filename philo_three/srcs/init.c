/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:42:37 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/22 23:31:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_three.h"
#include "errno.h"
#include "string.h"

t_info	*init_philo_info(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	if (get_arg_info(info, argc, argv) == -1)
		return (NULL);
	info->exec_tm = get_timestamp(0);
	sem_unlink(SEM_FORKS_NAME);
	info->forks = sem_open(SEM_FORKS_NAME, O_CREAT | O_EXCL,
			0600, info->nb_philo);
	sem_unlink(SEM_OUTPUT_NAME);
	info->output_sem = sem_open(SEM_OUTPUT_NAME, O_CREAT | O_EXCL,
			0600, 1);
	if (!info->forks || !info->output_sem)
		return (NULL);
	info->forks_available = info->nb_philo;
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

pid_t	*init_philos_processes(t_info *info)
{
	pid_t		*childs;
	t_philo		*curr;
	int			i;

	childs = (pid_t *)malloc(sizeof(pid_t) * info->nb_philo);
	memset(childs, 0, sizeof(pid_t) * info->nb_philo);
	info->philos = (t_philo **)malloc(sizeof(t_philo *) * info->nb_philo);
	if (!childs || !info->philos)
		return (NULL);
	i = 0;
	while (i < info->nb_philo)
	{
		childs[i] = fork();
		if (childs[i] == -1)
			return (childs);
		else if (childs[i] == 0)
		{
			curr = init_philo(info, i);
			if (!curr)
				return (NULL);	
			philo_routine(curr);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	return (childs);
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
	new->output_sem = info->output_sem;
	new->exec_tm = info->exec_tm;
	new->meals.need_forks = FALSE;
	new->meals.last_meal = 0;
	new->meals.nb_meals = 0;
	new->death_name = ft_itoa(i);
	sem_unlink(new->death_name);
	new->death_sem = sem_open(new->death_name, O_CREAT | O_EXCL,
			0600, 1);
	if (!new->death_sem)
		return (NULL);
	new->forks = info->forks;
	new->forks_available = &info->forks_available;
	return (new);
}
