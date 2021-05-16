/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 00:34:55 by user42            #+#    #+#             */
/*   Updated: 2021/05/17 00:52:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

int	get_arg_info(t_info *info, int argc, char **argv)
{
	info->nb_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->nb_philo < 1
		|| info->time_to_die < 1
		|| info->time_to_eat < 1
		|| info->time_to_sleep < 1)
	{
		printf("Arguments must be non-zero positive integers\n");
		free(info);
		return (-1);
	}
	if (argc == 6)
		info->nb_must_eat = ft_atoi(argv[5]);
	else
		info->nb_must_eat = -1;
	return (0);
}

int	create_forks(t_info *info)
{
	int	i;

	i = -1;
	info->forks = init_forks_mutexes(info->nb_philo);
	if (!info->forks)
		return (-1);
	info->forks_available = (t_bool *)malloc(sizeof(t_bool) * info->nb_philo);
	if (!info->forks_available)
		return (-1);
	while (++i < info->nb_philo)
		info->forks_available[i] = TRUE;
	return (0);
}
