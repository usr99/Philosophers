/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 00:34:55 by user42            #+#    #+#             */
/*   Updated: 2021/05/21 18:09:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_three.h"

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

static int	sz_num(int n)
{
	if (n == 0)
		return (0);
	else
		return (sz_num(n / 10) + 1);
}

char	*ft_itoa(int n)
{
	int		size_n;
	long	nbr;
	char	*str;

	nbr = n;
	size_n = sz_num(nbr);
	if (nbr <= 0)
	{
		nbr *= -1;
		size_n++;
	}
	str = (char *)malloc(size_n + 1);
	if (!str)
		return (NULL);
	str[size_n] = '\0';
	while (size_n--)
	{
		str[size_n] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (str[0] == '0' && n != 0)
		str[0] = '-';
	return (str);
}
