/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:36:24 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/30 16:08:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_three.h"

int	main(int argc, char **argv)
{
	t_info		*philo_info;
	pid_t		*childs;
	int			ret;

	if (argc < 5 || argc > 6)
		return (-1);
	philo_info = init_philo_info(argc, argv);
	if (!philo_info)
		return (-1);
	childs = init_philos_processes(philo_info);
	if (!childs)
		return (-1);
	ret = wait_meals(philo_info);
	if (ret == -1)
		return (-1);
	wait_processes(philo_info, childs, ret);
	free_all(philo_info, childs);
	return (0);
}

int	wait_meals(t_info *info)
{
	pid_t	checkmeals_process;
	int		i;

	if (info->nb_must_eat == -1)
		return (0);
	checkmeals_process = fork();
	if (checkmeals_process == -1)
		return (-1);
	else if (checkmeals_process == 0)
	{
		i = 0;
		while (i < info->nb_philo)
		{
			sem_wait(info->meals_count_sem);
			i++;
		}
		sem_post(info->alive_sem);
		exit(EXIT_SUCCESS);
	}
	return (checkmeals_process);
}

void	wait_processes(t_info *info, pid_t *childs, int pid_meals)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		waitpid(childs[i], NULL, 0);
		i++;
	}
	if (info->nb_must_eat != -1)
		kill(pid_meals, SIGTERM);
}
