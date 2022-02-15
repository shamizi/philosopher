/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:51:42 by shamizi           #+#    #+#             */
/*   Updated: 2022/02/15 12:59:30 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_philo
{
	int id;
	int nbeat;
	int all_eat;
	long long last_meal;
	long long current_time;
	int isdead;
	pthread_t th;
	pthread_mutex_t *lfork;
	pthread_mutex_t *rfork;
	struct s_rules *rules;
}t_philo;

typedef struct s_rules
{

	long long starting_time;
	int nbphilo;
	int timetodie;
	int timetoeat;
	int timetosleep;
	int someonedied;
	int max_meal;
	pthread_mutex_t writing;
	t_philo philo[250];
}t_rules;

void	ft_thinking(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_eat(t_philo *philo);
void	*death(t_rules *r);
void	init_philo(t_rules *rules);
int	init_rules(char **argv, t_rules *rules);
int	init_mutex(t_rules *rules);
int	ft_is_num(char **argv);
long long timestamp(void);
long long timediff(long long past, long long present);
#endif
