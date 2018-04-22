/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:17 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:26:34 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_error(char *err_msg)
{
	if (err_msg)
		ft_putendl_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

cl_float4	init_float4(t_rgb rgb)
{
	cl_float4 res;

	res.x = rgb.r;
	res.y = rgb.g;
	res.z = rgb.b;
	res.w = 1.0f;
	return (res);
}

int			key_release(int keycode, void *ctx)
{
	t_app *app;

	app = (t_app*)ctx;
	app->key_mask[keycode] = 0;
	return (1);
}
