/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:17 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 18:13:44 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <fcntl.h>
#include "timer.h"

static int	init_window(t_app *app, t_image *frame)
{
	int d;

	frame->width = 800;
	frame->height = 800;
	if (!(app->mlx.ptr = mlx_init()))
		return (0);
	app->mlx.win = mlx_new_window(app->mlx.ptr,
									frame->width, frame->height, "Fractol");
	if (!app->mlx.win)
		return (0);
	app->mlx.img_ptr = mlx_new_image(app->mlx.ptr, frame->width, frame->height);
	if (!app->mlx.img_ptr)
		return (0);
	frame->data = (int*)mlx_get_data_addr(app->mlx.img_ptr, &d, &d, &d);
	mlx_loop_hook(app->mlx.ptr, main_loop, app);
	return (1);
}

void		init_transform(t_app *app)
{
	app->update_mouse = 1;
	app->max_iteration = 300;
	app->mouse_x = 0;
	app->mouse_y = 0;
	app->transform.x_shift = 0.0f;
	app->transform.y_shift = 0.0f;
	app->transform.zoom = 1.0f;
}

void		init_temperature_preset(t_app *app)
{
	t_color *t;

	t = &app->color[TEMPERATURE];
	t->shift = 0;
	t->color_num = 14;
	t->base_colors = malloc(sizeof(t_rgb) * t->color_num);
	t->colors = malloc(sizeof(cl_float4) * t->color_num);
	t->base_colors[0] = init_rgb(0.917647f, 0.498039f, 0.192156f);
	t->base_colors[1] = init_rgb(0.933333f, 136.0f / 255, 51.0f / 255);
	t->base_colors[2] = init_rgb(240.0f / 255, 160.0f / 255, 81.0f / 255);
	t->base_colors[3] = init_rgb(241.0f / 255, 165.0f / 255, 91.0f / 255);
	t->base_colors[4] = init_rgb(242.0f / 255, 172.0f / 255, 99.0f / 255);
	t->base_colors[5] = init_rgb(243.0f / 255, 171.0f / 255, 117.0f / 255);
	t->base_colors[6] = init_rgb(244.0f / 255, 188.0f / 255, 127.0f / 255);
	t->base_colors[7] = init_rgb(244.0f / 255, 193.0f / 255, 135.0f / 255);
	t->base_colors[8] = init_rgb(250.0f / 255, 229.0f / 255, 206.0f / 255);
	t->base_colors[9] = init_rgb(253.0f / 255, 241.0f / 255, 233.0f / 255);
	t->base_colors[10] = init_rgb(253.0f / 255, 246.0f / 255, 246.0f / 255);
	t->base_colors[11] = init_rgb(254.0f / 255, 249.0f / 255, 255.0f / 255);
	t->base_colors[12] = init_rgb(224.0f / 255, 230.0f / 255, 252.0f / 255);
	t->base_colors[13] = init_rgb(167.0f / 255, 190.0f / 255, 250.0f / 255);
}

int			init(t_app *app)
{
	app->show_help = 0;
	app->current_preset = WIKI;
	init_wiki_preset(app);
	init_temperature_preset(app);
	init_psychedelic(&app->color[PSYCHEDELIC]);
	init_transform(app);
	if (!init_window(app, &app->frame) || init_cl(app))
		return (0);
	init_timer(&app->timer);
	return (1);
}
