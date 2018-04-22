/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:17 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:08:25 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mix.h"
#include "handle_input.h"
#include "keys.h"
#include "timer.h"

void		update_color_preset(t_color *preset, t_app *app)
{
	t_rgb	fc;
	t_rgb	lc;
	float	coeff;
	int		i;
	int		shifted_i;

	shifted_i = ((int)preset->shift + preset->color_num) % preset->color_num;
	coeff = fabs(fmodf(preset->shift, 1.0f));
	i = -1;
	while (++i < preset->color_num)
	{
		fc = preset->base_colors[shifted_i];
		shifted_i = (shifted_i + 1) % preset->color_num;
		lc = preset->base_colors[shifted_i];
		preset->colors[i] = init_float4(mix_color(fc, lc, coeff));
	}
	clEnqueueWriteBuffer(app->cl.queue, app->cl.color_buffer, CL_TRUE, 0,
		sizeof(cl_float4) * preset->color_num, preset->colors, 0, NULL, NULL);
}

void		update(t_app *app)
{
	handle_input(app, get_delta_time(&app->timer));
	update_color_preset(&app->color[app->current_preset], app);
}

void		render(t_app *app)
{
	int			err;
	cl_kernel	k;

	k = app->cl.kernel[app->current_fractal];
	err = clSetKernelArg(k, 0, sizeof(cl_mem), &app->cl.image_buffer);
	err |= clSetKernelArg(k, 1, sizeof(cl_mem), &app->cl.color_buffer);
	err |= clSetKernelArg(k, 2, sizeof(double), &app->transform.zoom);
	err |= clSetKernelArg(k, 3, sizeof(double), &app->transform.x_shift);
	err |= clSetKernelArg(k, 4, sizeof(double), &app->transform.y_shift);
	err |= clSetKernelArg(k, 5, sizeof(int), &app->mouse_x);
	err |= clSetKernelArg(k, 6, sizeof(int), &app->mouse_y);
	err |= clSetKernelArg(k, 7, sizeof(int), &app->frame.width);
	err |= clSetKernelArg(k, 8, sizeof(int), &app->frame.height);
	err |= clSetKernelArg(k, 9, sizeof(int), &app->max_iteration);
	err |= clSetKernelArg(k, 10, sizeof(int),
							&app->color[app->current_preset].color_num);
	err = clEnqueueNDRangeKernel(app->cl.queue, k, 2, NULL,
		app->cl.global_work_size, app->cl.local_work_size, 0, NULL, NULL);
	clFinish(app->cl.queue);
	err = clEnqueueReadBuffer(app->cl.queue, app->cl.image_buffer, CL_TRUE, 0,
		app->frame.width * app->frame.height * 4, app->frame.data, 0, NULL,
																		NULL);
}

void		render_help(t_app *app)
{
	int shift;
	int c;

	c = 0x4086bb;
	shift = (app->current_fractal == JULIA) ? 20 : 0;
	if (!app->show_help)
		return ;
	mlx_string_put(app->mlx.ptr, app->mlx.win, 10, 10, c,
							app->cl.kernel_names[app->current_fractal]);
	mlx_string_put(app->mlx.ptr, app->mlx.win, 10, 30, c, "Reset - R");
	mlx_string_put(app->mlx.ptr, app->mlx.win, 10, 50, c, "Color shift - N/M");
	mlx_string_put(app->mlx.ptr, app->mlx.win, 10, 70, c,
														"Color preset - K/L");
	mlx_string_put(app->mlx.ptr, app->mlx.win, 10, 90, c,
													"Iteration count - +/-");
	if (app->current_fractal == JULIA)
		mlx_string_put(app->mlx.ptr, app->mlx.win, 10, 110, c,
															"Lock mouse - U");
	mlx_string_put(app->mlx.ptr, app->mlx.win, 10, 110 + shift, c,
													"Change Fractal - [/]");
	mlx_string_put(app->mlx.ptr, app->mlx.win, 10, 130 + shift, c,
														"Show/Hide help - H");
}

int			main_loop(void *param)
{
	t_app *app;

	app = (t_app*)param;
	ft_memset(app->frame.data, 0, app->frame.width * app->frame.height * 4);
	update(app);
	render(app);
	mlx_put_image_to_window(app->mlx.ptr, app->mlx.win,
							app->mlx.img_ptr, 0, 0);
	render_help(app);
	app->key_mask[MOUSE_ZOOM_OUT] = 0;
	app->key_mask[MOUSE_ZOOM_IN] = 0;
	return (0);
}
