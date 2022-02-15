/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:25:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/02/15 12:31:08 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	p->last_meal = timestamp();
	if (p->id % 2)
		usleep(p->rules->timetoeat * 1000);
	while (!p->rules->someonedied)
	{
		if (p->rules->nbphilo == 1)
		{
			printf("[%d] 1 is dead\n", p->rules->timetodie);
			break ;
		}
		if (p->nbeat == p->all_eat)
			break ;
		ft_eat(p);
	}
	return (NULL);
}

int	start(t_rules *rules)
{
	int			i;
//	pthread_t	thread;

	i = 0;
	rules->starting_time = timestamp();
	while (i < rules->nbphilo)
	{
		pthread_create(&rules->philo[i].th, NULL, routine, &rules->philo[i]);
	//	pthread_create(&thread, NULL, death, rules);
	//	pthread_detach(thread);
		i++;
	}
	death(rules);
	i = 0;
	while (i < rules->nbphilo)
	{
		pthread_join(rules->philo[i].th, NULL);
		pthread_mutex_destroy((rules->philo[i].lfork));
		free(rules->philo[i].lfork);
		i++;
	}
	pthread_mutex_destroy(&rules->writing);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 5 && argc != 6)
	{
		printf("Format d'argument invalide");
		return (0);
	}
	if (!ft_is_num(argv) || !init_rules(argv, &rules))
	{
		printf("Erreur d'arguments");
		return (0);
	}
	init_philo(&rules);
	if (init_mutex(&rules))
	{
		printf("Echec de la création du mutex");
		return (0);
	}
	start(&rules);
	return (0);
}
