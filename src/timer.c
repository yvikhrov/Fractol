/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liza <liza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:24:23 by liza              #+#    #+#             */
/*   Updated: 2018/04/14 14:35:38 by liza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"
#include <mach/mach_time.h>

void		init_timer(t_timer *timer)
{
	mach_timebase_info_data_t coeff;

	mach_timebase_info(&coeff);
	timer->numer = coeff.numer;
	timer->denom = coeff.denom;
	timer->current_time = 0;
	timer->start = mach_absolute_time();
	timer->current = timer->start;
	timer->time = 0.0;
	timer->old_time = 0.0;
}

double		get_delta_time(t_timer *timer)
{
	double delta_time;

	timer->current = mach_absolute_time() - timer->start;
	timer->current_time = timer->current * timer->numer / timer->denom;
	timer->time = (double)(timer->current_time / 1000) / 1000000.0;
	delta_time = timer->time - timer->old_time;
	timer->old_time = timer->time;
	return (delta_time);
}
