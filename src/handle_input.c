#include "handle_input.h"
#include "keys.h"

int			key_press(int keycode, void *param)
{
	t_app *app;

	int diff;

	app = (t_app*)param;
	if (keycode == KEY_ESCAPE)
		quit(app);
	else if (keycode == KEY_G)
		app->gradient_coloring = !app->gradient_coloring;
	else if (keycode == KEY_P)
		app->perception_speed <<= 1;
	else if (keycode == KEY_O)
		app->perception_speed >>= 1;
	else if (keycode == KEY_OPEN_BRACKET || keycode == KEY_CLOSE_BRACKET)
	{
		diff = keycode == KEY_OPEN_BRACKET ? -1 : 1;
		app->current_fractal = (app->current_fractal + diff + FRACTAL_NUM) % FRACTAL_NUM;
	}
	else if (keycode == KEY_U)
		app->update_mouse = !app->update_mouse;
	app->perception_speed = clamp_int(app->perception_speed, 1, 8);
	app->key_mask[keycode] = 1;
	return (1);
}

int		mouse_hook(int keycode, int x, int y, void *param)
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

int			key_release(int keycode, void *ctx)
{
	t_app *app;

	app = (t_app*)ctx;
	app->key_mask[keycode] = 0;
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

void		handle_input(t_app *app, double dt)
{
	if (app->key_mask[KEY_EQUAL])
		app->transform.zoom *= 2.0f * dt;
	else if (app->key_mask[KEY_MINUS])
		app->transform.zoom /= 2.0f * dt;
	else if (app->key_mask[KEY_LEFT])
		app->transform.x_shift -= 0.25f * dt / app->transform.zoom;
	else if (app->key_mask[KEY_RIGHT])
		app->transform.x_shift += 0.25f * dt / app->transform.zoom;
	else if (app->key_mask[KEY_UP])
		app->transform.y_shift -= 0.25f * dt / app->transform.zoom;
	else if (app->key_mask[KEY_DOWN])
		app->transform.y_shift += 0.25f * dt / app->transform.zoom;
	else if (app->key_mask[MOUSE_ZOOM_IN])
	{
		app->transform.zoom += app->transform.zoom * dt * 10.0f;
		app->transform.x_shift += (2.0f * app->zoom_mouse_x / app->frame.width - 1.0f) / app->transform.zoom * dt * 10.0f;
		app->transform.y_shift += (2.0f * app->zoom_mouse_y / app->frame.height - 1.0f) / app->transform.zoom * dt * 10.0f;
	}
	else if (app->key_mask[MOUSE_ZOOM_OUT])
	{
		app->transform.zoom -= app->transform.zoom * dt * 10.0f;
		app->transform.x_shift -= (2.0f * app->zoom_mouse_x / app->frame.width - 1.0f) / app->transform.zoom * dt  * 10.0f;
		app->transform.y_shift -= (2.0f * app->zoom_mouse_y / app->frame.height - 1.0f) / app->transform.zoom * dt * 10.0f;
//		app->transform.zoom -= app->transform.zoom * dt * 10.0f;
	}


	app->hue_min = fmodf(app->hue_min, 360.0f);
	app->hue_max = fmodf(app->hue_max, 360.0f);
}

