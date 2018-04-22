/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:17 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:26:03 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mix.h"

t_rgb			mix_color(t_rgb x, t_rgb y, float coeff)
{
	t_rgb mixed_color;

	mixed_color.r = mix_float(x.r, y.r, coeff);
	mixed_color.g = mix_float(x.g, y.g, coeff);
	mixed_color.b = mix_float(x.b, y.b, coeff);
	return (mixed_color);
}

float			mix_float(float x, float y, float coeff)
{
	return (x * (1.0f - coeff) + y * coeff);
}
