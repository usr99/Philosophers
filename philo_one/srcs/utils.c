/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 01:10:01 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/15 02:20:52 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

int		ft_atoi(const char *nptr)
{
	int		i;
	int		is_negative;
	long	nbr;

	i = 0;
	is_negative = 0;
	nbr = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_negative = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	if (is_negative)
		return (-nbr);
	return (nbr);
}

void	print_log(char *output, t_philo *philo)
{
	if (*philo->is_alive == FALSE)
		return ;
	pthread_mutex_lock(philo->output_mutex);
	printf("[%ld] ", get_timestamp(philo->exec_tm));
	printf(output, philo->nb_philo);
	pthread_mutex_unlock(philo->output_mutex);
}

long	get_timestamp(long reference_tm)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000 - reference_tm);
}

void	ft_msleep(int time_to_sleep)
{
	long	current_tm;
	long	reference_tm;

	reference_tm = get_timestamp(0);
	current_tm = reference_tm;
	while (time_to_sleep > current_tm - reference_tm)
	{
		usleep(100);
		current_tm = get_timestamp(0);
	}
}

void	free_all(t_info *info, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		free(info->philos[i]);
		i++;
	}
	free(info->philos);
	free(info->forks);
	free(info->meals);
	free(info);
	free(th);
}
