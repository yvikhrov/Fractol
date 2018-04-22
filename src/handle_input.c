/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:17 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:22:27 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_input.h"
#include "keys.h"
#include "clamp.h"

int			key_press(int keycode, void *param)
{
	t_app	*app;

	app = (t_app*)param;
	if (keycode == KEY_ESCAPE)
		quit(app);
	else if (keycode == KEY_R)
		init_transform(app);
	else if (keycode == KEY_OPEN_BRACKET || keycode == KEY_CLOSE_BRACKET)
		app->current_fractal = (app->current_fractal + (keycode ==
			KEY_OPEN_BRACKET ? -1 : 1) + FRACTAL_NUM) % FRACTAL_NUM;
	else if (keycode == KEY_U)
		app->update_mouse = !app->update_mouse;
	else if (keycode == KEY_H)
		app->show_help = !app->show_help;
	else if (keycode == KEY_K || keycode == KEY_L)
		app->current_preset = (app->current_preset + (keycode ==
			KEY_K ? -1 : 1) + COLOR_PRESET_TOTAL) % COLOR_PRESET_TOTAL;
	app->key_mask[keycode] = 1;
	return (1);
}

int			mouse_hook(int keycode, int x, int y, void *param)
{
	t_app *app;

	app = (t_app*)param;
	if (x >= 0 && y >= 0 && x < app->frame.width && y < app->frame.height)
	{
		if (keycode == 5)
			app->key_mask[MOUSE_ZOOM_OUT] = 1;
		if (keycode == 4)
			app->key_mask[MOUSE_ZOOM_IN] = 1;
	}
	return (1);
}

int			mouse_position_hook(int x, int y, void *param)
{
	t_app *app;

	app = (t_app*)param;
	if (app->update_mouse)
	{
		app->mouse_x = x;
		app->mouse_y = y;
	}
	app->zoom_mouse_x = x;
	app->zoom_mouse_y = y;
	return (1);
}

void		mouse_input(t_app *app, double dt)
{
	float delta_zoom;
	float ndc_x;
	float ndc_y;

	ndc_x = 2.0 * app->zoom_mouse_x / app->frame.width - 1.0;
	ndc_y = 2.0 * app->zoom_mouse_y / app->frame.height - 1.0;
	delta_zoom = clamp_double(app->transform.zoom * dt * 10.0, 1e-16,
								app->transform.zoom * 0.8);
	if (app->key_mask[MOUSE_ZOOM_IN])
	{
		if (app->transform.zoom > 1e30)
			return ;
		app->transform.zoom += delta_zoom;
		app->transform.x_shift += ndc_x / app->transform.zoom * dt * 10.0;
		app->transform.y_shift += ndc_y / app->transform.zoom * dt * 10.0;
	}
	else if (app->key_mask[MOUSE_ZOOM_OUT])
	{
		if (app->transform.zoom < -1e30)
			return ;
		app->transform.zoom -= delta_zoom;
		app->transform.x_shift -= ndc_x / app->transform.zoom * dt * 10.0;
		app->transform.y_shift -= ndc_y / app->transform.zoom * dt * 10.0;
	}
}

void		handle_input(t_app *app, double dt)
{
	if (app->key_mask[KEY_LEFT])
		app->transform.x_shift -= 0.5 * dt / app->transform.zoom;
	else if (app->key_mask[KEY_RIGHT])
		app->transform.x_shift += 0.5 * dt / app->transform.zoom;
	else if (app->key_mask[KEY_UP])
		app->transform.y_shift -= 0.5 * dt / app->transform.zoom;
	else if (app->key_mask[KEY_DOWN])
		app->transform.y_shift += 0.5 * dt / app->transform.zoom;
	else if (app->key_mask[KEY_EQUAL] || app->key_mask[KEY_MINUS])
		app->max_iteration += (app->key_mask[KEY_EQUAL] ? 15 : -15);
	else if (app->key_mask[KEY_N] || app->key_mask[KEY_M])
		app->color[app->current_preset].shift +=
						dt * 2.0f * (app->key_mask[KEY_M] ? 1 : -1);
	else
		mouse_input(app, dt);
	app->max_iteration = MAX(app->max_iteration, 10);
}
