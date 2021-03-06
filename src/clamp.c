/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:16 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:09:07 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clamp.h"

int				clamp_int(int v, int min, int max)
{
	if (v > min)
		return ((v < max) ? v : max);
	else
		return (min);
}

float			clamp_float(float v, float min, float max)
{
	if (v > min)
		return ((v < max) ? v : max);
	else
		return (min);
}

double			clamp_double(double v, double min, double max)
{
	if (v > min)
		return ((v < max) ? v : max);
	else
		return (min);
}

t_rgb			clamp_rgb(t_rgb color, float edge0, float edge1)
{
	t_rgb result;

	result.r = clamp_float(color.r, edge0, edge1);
	result.g = clamp_float(color.g, edge0, edge1);
	result.b = clamp_float(color.b, edge0, edge1);
	return (result);
}
