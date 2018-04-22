/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:50 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:37:42 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2i.h"

t_vec2i	init_vec2i(int x, int y)
{
	t_vec2i point;

	point.x = x;
	point.y = y;
	return (point);
}

int		abs_int(int x)
{
	return (x > 0 ? x : -x);
}
