/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:42:37 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/30 16:10:51 by user42           ###   ########.fr       */
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
	info->output_sem = sem_open(SEM_OUTPUT_NAME, O_CREAT | O_EXCL, 0600, 1);
	sem_unlink(SEM_ALIVE_NAME);
	info->alive_sem = sem_open(SEM_ALIVE_NAME, O_CREAT | O_EXCL, 0600, 0);
	sem_unlink(SEM_MEALS_NAME);
	info->meals_count_sem = sem_open(SEM_MEALS_NAME, O_CREAT | O_EXCL, 0600,
			0);
	return (info);
}

pid_t	*init_philos_processes(t_info *info)
{
	pid_t		*childs;
	t_philo		*curr;
	int			i;

	childs = (pid_t *)malloc(sizeof(pid_t) * info->nb_philo);
	memset(childs, 0, sizeof(pid_t) * info->nb_philo);
	if (!childs)
		return (NULL);
	i = 0;
	while (i < info->nb_philo)
	{
		childs[i] = fork();
		if (childs[i] == 0)
		{
			curr = init_philo(info, i);
			if (!curr)
				return (NULL);
			philo_routine(curr);
			free(childs);
			free(info);
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
	new->time_to_die = info->time_to_die;
	new->time_to_eat = info->time_to_eat;
	new->time_to_sleep = info->time_to_sleep;
	new->nb_must_eat = info->nb_must_eat;
	new->output_sem = info->output_sem;
	new->alive_sem = info->alive_sem;
	new->forks = info->forks;
	new->meals_count_sem = info->meals_count_sem;
	new->exec_tm = info->exec_tm;
	new->meals.last_meal = 0;
	new->meals.nb_meals = 0;
	new->death_name = ft_itoa(i);
	sem_unlink(new->death_name);
	new->death_sem = sem_open(new->death_name, O_CREAT | O_EXCL, 0777, 1);
	if (!new->death_sem)
		return (NULL);
	return (new);
}
