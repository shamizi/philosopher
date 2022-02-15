/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:23:58 by shamizi           #+#    #+#             */
/*   Updated: 2022/02/15 12:59:38 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_rules(char **argv, t_rules *rules)
{
	int	ret;

	rules->someonedied = 0;
	rules->nbphilo = atoi(argv[1]);
	rules->timetodie = atoi(argv[2]);
	rules->timetoeat = atoi(argv[3]);
	rules->timetosleep = atoi(argv[4]);
	if (rules->nbphilo < 1 || rules->timetodie < 0 || rules->nbphilo > 250
		|| rules->timetoeat < 0 || rules->timetosleep < 0)
		return (0);
	if (argv[5])
	{
		rules->max_meal = atoi(argv[5]);
		if (rules->max_meal <= 0)
			return (0);
	}
	else
		rules->max_meal = -1;
	ret = pthread_mutex_init(&rules->writing, NULL);
	if (ret)
		return (0);
	return (1);
}

void	init_philo(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nbphilo)
	{
		rules->philo[i].all_eat = rules->max_meal;
		rules->philo[i].id = i;
		rules->philo[i].nbeat = 0;
		rules->philo[i].last_meal = 0;
		rules->philo[i].isdead = 0;
		rules->philo[i].rules = rules;
		i++;
	}
}

int	init_mutex(t_rules *rules)
{
	int	i;
	int	ret;

	i = 0;
	while (i < rules->nbphilo)
	{
		rules->philo[i].lfork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!rules->philo[i].lfork)
			return (1);
		ret = pthread_mutex_init(rules->philo[i].lfork, NULL);
		if (ret)
			return (1);
		i++;
	}
	i = 0;
	while (i < rules->nbphilo)
	{
		if (i == rules->nbphilo - 1)
			rules->philo[i].rfork = rules->philo[0].lfork;
		else
			rules->philo[i].rfork = rules->philo[i + 1].lfork;
		i++;
	}
	return (0);
}

int	ft_is_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] <= '9' && argv[i][j] >= '0')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
