/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 01:10:01 by mamartin          #+#    #+#             */
/*   Updated: 2021/05/22 17:09:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_three.h"

int	ft_atoi(const char *nptr)
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
	sem_wait(philo->output_sem);
	printf("[%ld] ", get_timestamp(philo->exec_tm));
	printf(output, philo->nb_philo);
	sem_post(philo->output_sem);
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
		usleep(50);
		current_tm = get_timestamp(0);
	}
}

void	free_all(t_info *info, pid_t *childs)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		sem_close(info->philos[i]->death_sem);
		sem_unlink(info->philos[i]->death_name);
		free(info->philos[i]->death_name);
		free(info->philos[i]);
		i++;
	}
	sem_close(info->forks);
	sem_unlink(SEM_FORKS_NAME);
	sem_close(info->output_sem);
	sem_unlink(SEM_OUTPUT_NAME);
	free(info->philos);
	free(info);
	free(childs);
}
