/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:30:54 by shamizi           #+#    #+#             */
/*   Updated: 2022/02/15 13:32:51 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thinking(t_philo *ph)
{
	long long	lli;

	ph->current_time = timestamp();
	lli = timediff(ph->rules->starting_time, ph->current_time);
	pthread_mutex_lock(&ph->rules->writing);
	if (!ph->rules->someonedied)
		printf("[%lli] %d is thinking\n", lli, ph->id + 1);
	pthread_mutex_unlock(&ph->rules->writing);
}

void	ft_sleep(t_philo *ph)
{
	long long	lli;

	ph->current_time = timestamp();
	lli = timediff(ph->rules->starting_time, ph->current_time);
	pthread_mutex_lock(&ph->rules->writing);
	if (!ph->rules->someonedied)
		printf("[%lli] %d is sleeping\n", lli, ph->id + 1);
	pthread_mutex_unlock(&ph->rules->writing);
	usleep(ph->rules->timetosleep * 1000);
	ft_thinking(ph);
}

void	ft_eat(t_philo *ph)
{
	long long	lli;

	pthread_mutex_lock(ph->lfork);
	pthread_mutex_lock(ph->rfork);
	ph->current_time = timestamp();
	ph->last_meal = timestamp();
	lli = timediff(ph->rules->starting_time, ph->current_time);
	if (!ph->rules->someonedied)
	{
		printf("[%lli] %d has taken left fork\n", lli, ph->id + 1);
		printf("[%lli] %d has taken right fork\n", lli, ph->id + 1);
	}
	ph->nbeat += 1;
	pthread_mutex_lock(&ph->rules->writing);
	if (!ph->rules->someonedied)
		printf("[%lli] %d is eating\n", lli, ph->id + 1);
	pthread_mutex_unlock(&ph->rules->writing);
	usleep(ph->rules->timetoeat * 1000);
	pthread_mutex_unlock(ph->lfork);
	pthread_mutex_unlock(ph->rfork);
	ft_sleep(ph);
}

int	meal(t_rules *r)
{
	int	i;

	i = 0;
	while (r->max_meal != -1  && i < r->nbphilo && r->philo[i].nbeat >= r->philo[i].all_eat)
		i++;
	if (i == r->nbphilo)
		return (1);
	return (0);
}
void	*death(t_rules *r)
{
	int		i;
	int		j;

	usleep(r->timetoeat * 1000 - 10);
	while (!r->someonedied)
	{
		j = meal(r);
		if (j)
			break;
		i = -1;
		while (++i < r->nbphilo)
		{
			pthread_mutex_lock(&r->writing);
			if ((timestamp() - r->philo[i].last_meal) > r->timetodie)
			{
				if (!r->someonedied && r->nbphilo != 1)
					printf("[%lli] %d is dead\n", timestamp() - r->starting_time, i + 1);
				r->someonedied++;
			}
			pthread_mutex_unlock(&r->writing);
			usleep(100);
		}
	}
	return (NULL);
}
