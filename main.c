/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:14:29 by shamizi           #+#    #+#             */
/*   Updated: 2022/01/11 13:47:34 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


//ok donc la il me faut un mutex pour quand j'écrit ou nom et que je le bloque totalement quand qqn est mort

int	init_rules(char **argv, t_rules *rules)
{
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
	return (1);
}

int		ft_is_num(char **argv)
{
	int i;
	int j;

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

void	init_philo(t_rules *rules, t_philo *philo)
{
	int i;

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
	int i;
	int ret;
	
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
			rules->philo[i].rfork = rules->philo[i +1].lfork;
		i++;
	}
	return (0);
}

void	ft_thinking(t_philo *ph)
{
	long long lli;

	ph->current_time = timestamp();
	lli = timediff(ph->starting_time, ph->current_time);
	if (timediff(ph->last_meal, ph->current_time) > ph->rules->timetodie)
	{
			if(!ph->rules->someonedied)
				printf("[%lli] %d is dead\n", lli ,ph->id + 1);
		ph->rules->someonedied++;
	}
	else
	{
		if(!ph->rules->someonedied)
			printf("[%lli] %d is thinking\n", lli ,ph->id + 1);
	}
}
void	ft_sleep(t_philo *ph)
{
	long long	lli;

	ph->current_time = timestamp();
	lli = timediff(ph->starting_time, ph->current_time);
	if(!ph->rules->someonedied)
		printf("[%lli] %d is sleeping\n", lli ,ph->id + 1);
	usleep(ph->rules->timetosleep * 1000);
	ft_thinking(ph);
}

void	ft_eat(t_philo *ph)
{
	long long	lli;

	pthread_mutex_lock(ph->lfork);
	pthread_mutex_lock(ph->rfork);
	ph->current_time = timestamp();
	lli = timediff(ph->starting_time, ph->current_time);
	ph->last_meal = timestamp();
	if(!ph->rules->someonedied)
	{
		printf("[%lli] %d has taken left fork\n", lli ,ph->id + 1);
		printf("[%lli] %d has taken right fork\n", lli ,ph->id + 1);
	}
	ph->nbeat += 1;
	if(!ph->rules->someonedied)
		printf("[%lli] %d is eating\n", lli, ph->id + 1);
	usleep(ph->rules->timetoeat * 1000);
	pthread_mutex_unlock(ph->lfork);
	pthread_mutex_unlock(ph->rfork);
	ft_sleep(ph);
}


void	*routine(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	p->starting_time = timestamp();
	if (p->id %2)
		usleep(1500);
	while (!p->rules->someonedied)
	{
		if (p->nbeat == p->all_eat)
			break ;
		ft_eat(p);
	}
	return NULL;
}

int		start(t_rules *rules)
{
	int i;

	i = 0;
	while(i < rules->nbphilo)
	{
		pthread_create(&rules->philo[i].th, NULL, routine, &rules->philo[i]);
		i++;
	}
	i = 0;
	while (i < rules->nbphilo)
	{
		pthread_join(rules->philo[i].th, NULL);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_rules rules;
	t_philo philo;

	if (argc != 5 && argc != 6)
		return (0); // nb argument invalide
	if (!ft_is_num(argv))
		return (0); // format d'argument invalide
	if(!init_rules(argv, &rules))
		return (0); // regle incohérente
	init_philo(&rules, &philo);
	if (init_mutex(&rules))
		return (0); //mutex create failed
	start(&rules);
	//printf("%d : %d : %d : %d : %d : ",rules.nbphilo, rules.timetodie, rules.timetoeat, rules.timetosleep, rules.max_meal);
	return (0);
}
