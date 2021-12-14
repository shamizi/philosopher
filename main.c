/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:14:29 by shamizi           #+#    #+#             */
/*   Updated: 2021/12/14 16:45:40 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philo
{
	/*left fork, right fork, last meal seconde ? is eating ? is dead ? */
	int	lfork;
	int rfork;
	pthread_t philo[250];
	pthread_mutex_t fork[250];
}t_philo;

typedef struct s_rules
{
	int nbphilo;
	int timetodie;
	int timetoeat;
	int timetosleep;
	int max_meal;
}t_rules;
/////////////////////////////////////////////////////////////////////////////////////

void	*test(void *arg)
{
	int i = 1;

	printf("creation philo %d\n", i);
	return 0;
}

void	init_rules(char **argv, t_rules *rules)
{
	rules->nbphilo = atoi(argv[1]);
	rules->timetodie = atoi(argv[2]);
	rules->timetoeat = atoi(argv[3]);
	rules->timetosleep = atoi(argv[4]);
	if (argv[5])
		rules->max_meal = atoi(argv[5]);
	else
		rules->max_meal = -1;
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
		pthread_create(&philo->philo[i], NULL, test, (void *)0);
		//pthread_mutex_init(&philo.fork[i], NULL)
		usleep(20);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_rules rules;
	t_philo philo;

	if (argc != 5 && argc != 6)
		return (0);
	if (!ft_is_num(argv))
		return (0);
	init_rules(argv, &rules);
	init_philo(&rules, &philo);
	//printf("%d : %d : %d : %d : %d : ",rules.nbphilo, rules.timetodie, rules.timetoeat, rules.timetosleep, rules.max_meal);
	return (0);
}
