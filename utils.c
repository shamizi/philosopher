/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:56:37 by shamizi           #+#    #+#             */
/*   Updated: 2022/01/07 16:30:30 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval t;
	if (gettimeofday(&t, NULL) == -1)
		return -1;
	return (t.tv_sec * 1000 + t.tv_usec/1000);
}

long long	timediff(long long past, long long present)
{
	return (present - past);
}
