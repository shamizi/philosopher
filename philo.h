/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:51:42 by shamizi           #+#    #+#             */
/*   Updated: 2022/01/11 13:40:49 by shamizi          ###   ########.fr       */
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
	long long starting_time;
	int isdead;
	pthread_t th;
	pthread_mutex_t *lfork;
	pthread_mutex_t *rfork;
	struct s_rules *rules;
}t_philo;

typedef struct s_rules
{
	int nbphilo;
	int timetodie;
	int timetoeat;
	int timetosleep;
	int	someonedied;
	int max_meal;
	t_philo philo[250];
}t_rules;

long long timestamp(void);
long long timediff(long long past, long long present);
#endif
