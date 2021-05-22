/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:36:24 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/22 20:28:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_three.h"

// 5 800 200 200, 5 800 200 200 7, 4 310 200 100, 4 410 200 200

int	main(int argc, char **argv)
{
	/*t_info		*philo_info;
	pid_t		*childs;
	pthread_t	supervisor;
	int			i;

	if (argc < 5 || argc > 6)
		return (-1);
	philo_info = init_philo_info(argc, argv);
	if (!philo_info)
		return (-1);
	childs = init_philos_processes(philo_info);
	if (!childs)
		return (-1);
	pthread_create(&supervisor, NULL, &supervisor_func, philo_info);
	i = 0;
	pthread_join(supervisor, NULL);
	while (i < philo_info->nb_philo)
	{
		kill(childs[i], SIGTERM);
		i++;
	}
	free_all(philo_info, childs);*/

	int		a = 5;
	int		*b = &a;

	(void)argc;
	(void)argv;

	pid_t	pid = fork();
	if (pid == 0)
	{
		*b = 52;
	}
	else
	{
		waitpid(pid, NULL, 0);
		printf("%d\n", *b);
	}



	return (0);
}
