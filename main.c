/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:14:29 by shamizi           #+#    #+#             */
/*   Updated: 2021/12/16 14:20:52 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo
{
	/*left fork, right fork, last meal seconde ? is eating ? is dead ? */
	int	lfork;
	int rfork;
	pthread_t id;
	int nbeat;
	int last_meal;
	int isdead;
}t_philo;

typedef struct s_rules
{
	int nbphilo;
	int timetodie;
	int timetoeat;
	int timetosleep;
	int max_meal;
	pthread_mutex_t fork[250];
	t_philo philo[250];
}t_rules;
/////////////////////////////////////////////////////////////////////////////////////

void	*test(void *arg)
{
	int i = 1;

	printf("creation philo %d\n", i);
	return 0;
}

int	init_rules(char **argv, t_rules *rules)
{
	rules->nbphilo = atoi(argv[1]);
	rules->timetodie = atoi(argv[2]);
	rules->timetoeat = atoi(argv[3]);
	rules->timetosleep = atoi(argv[4]);
	if (rules->nbphilo < 1 || rules->timetodie < 0 || rules->nbphilo > 250
			|| rules->timetoeat < 0 || rules timetosleep < 0)
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
		rules->philo[i].id = i;
		rules->philo[i].lfork = i;
		rules->philo[i].rfork = (i + 1) % rules->nbphilo;
		rules->philo[i].nbeat = 0;
		rules->philo[i].last_meal = 0;
		rules->philo[i].isdead = 0;
	}
}

int		start(t_rules *rules, t_philo *philo)
{
	int i;

	i = 0;

}
int		main(int argc, char **argv)
{
	t_rules rules;
	t_philo philo;

	if (argc != 5 && argc != 6)
		return (0);
	if (!ft_is_num(argv))
		return (0);
	if(!init_rules(argv, &rules))
		return (0);
	init_philo(&rules, &philo);
	start(&rules, &philo);
	//printf("%d : %d : %d : %d : %d : ",rules.nbphilo, rules.timetodie, rules.timetoeat, rules.timetosleep, rules.max_meal);
	return (0);
}
