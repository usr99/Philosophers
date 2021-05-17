/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:36:24 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/17 02:36:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_two.h"

// 5 800 200 200, 5 800 200 200 7, 4 310 200 100, 4 410 200 200

int	main(int argc, char **argv)
{
	t_info		*philo_info;
	pthread_t	*th_philos;
	pthread_t	supervisor;
	int			i;

	if (argc < 5 || argc > 6)
		return (-1);
	philo_info = init_philo_info(argc, argv);
	if (!philo_info)
		return (-1);
	th_philos = init_philos_threads(philo_info);
	if (!th_philos)
		return (-1);
	pthread_create(&supervisor, NULL, &supervisor_func, philo_info);
	i = 0;
	pthread_join(supervisor, NULL);
	while (i < philo_info->nb_philo)
	{
		pthread_join(th_philos[i], NULL);
		i++;
	}
	free_all(philo_info, th_philos);
	return (0);
}
