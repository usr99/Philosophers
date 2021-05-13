/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 01:10:01 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/11 23:39:06 by mamartin         ###   ########.fr       */
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
	pthread_mutex_lock(philo->output_mutex);
	print_timestamp(philo->exec_time);
	printf(output, philo->nb_philo);
	pthread_mutex_unlock(philo->output_mutex);
}

void	print_timestamp(struct timeval exec_timestamp)
{
	struct timeval		timestamp;
	unsigned long		offset;

	gettimeofday(&timestamp, NULL);
	offset = timestamp.tv_sec * 1000000 - exec_timestamp.tv_sec * 1000000;
	offset += timestamp.tv_usec - exec_timestamp.tv_usec;
	offset /= 1000;
	printf("[%ld] ", offset);
}
