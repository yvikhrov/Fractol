#include "fdf.h"
#include <fcntl.h>
#include "timer.h"

static int	init_window(t_app *app, t_image *frame)
{
	int dummy;

	frame->width = 800;
	frame->height = 800;
	if (!(app->mlx.ptr = mlx_init()))
		return (0);
	app->mlx.win = mlx_new_window(app->mlx.ptr,
									frame->width, frame->height, "FDF");
	if (!app->mlx.win)
		return (0);
	app->mlx.img_ptr = mlx_new_image(app->mlx.ptr, frame->width, frame->height);
	if (!app->mlx.img_ptr)
		return (0);
	frame->data = (int*)mlx_get_data_addr(app->mlx.img_ptr, &dummy, &dummy, &dummy);
	mlx_loop_hook(app->mlx.ptr, main_loop, app);
	return (1);
}

void		init_transform(t_app *app)
{
	app->update_mouse = 1;
	app->kMaxIteration = 300;
	app->mouse_x = 0;
	app->mouse_y = 0;
	app->transform.x_shift = 0.0f;
	app->transform.y_shift = 0.0f;
	app->transform.zoom = 1.0f;
}

void		init_wiki_preset(t_app *app)
{
	t_color *w;

	w = &app->color[WIKI];
	w->shift = 0;
	w->color_num = 32;
	w->base_colors = malloc(sizeof(t_rgb) * w->color_num);
	w->colors = malloc(sizeof(cl_float4) * w->color_num);
	w->base_colors[0] = init_rgb(0.098039f, 0.027451f, 0.101961f);
	w->base_colors[1] = init_rgb(0.258824f, 0.117647f, 0.058824f);
	w->base_colors[2] = init_rgb(0.035294f, 0.003922f, 0.184314f);
	w->base_colors[3] = init_rgb(0.015686f, 0.015686f, 0.286275f);
	w->base_colors[4] = init_rgb(0.000000f, 0.027451f, 0.392157f);
	w->base_colors[5] = init_rgb(0.047059f, 0.172549f, 0.541176f);
	w->base_colors[6] = init_rgb(0.094118f, 0.321569f, 0.694118f);
	w->base_colors[7] = init_rgb(0.223529f, 0.490196f, 0.819608f);
	w->base_colors[8] = init_rgb(0.525490f, 0.709804f, 0.898039f);
	w->base_colors[9] = init_rgb(0.827451f, 0.925490f, 0.972549f);
	w->base_colors[10] = init_rgb(0.945098f, 0.913725f, 0.749020f);
	w->base_colors[11] = init_rgb(0.972549f, 0.788235f, 0.372549f);
	w->base_colors[12] = init_rgb(1.000000f, 0.666667f, 0.000000f);
	w->base_colors[13] = init_rgb(0.800000f, 0.501961f, 0.000000f);
	w->base_colors[14] = init_rgb(0.600000f, 0.341176f, 0.000000f);
	w->base_colors[15] = init_rgb(0.415686f, 0.203922f, 0.011765f);
	w->base_colors[16] = init_rgb(0.949020f, 0.000000f, 0.078431f);
	w->base_colors[17] = init_rgb(0.976471f, 0.027451f, 0.101961f);
	w->base_colors[18] = init_rgb(0.976471f, 0.011765f, 1.000000f);
	w->base_colors[19] = init_rgb(0.956863f, 0.015686f, 0.286275f);
	w->base_colors[20] = init_rgb(1.000000f, 0.003922f, 0.392157f);
	w->base_colors[21] = init_rgb(1.000000f, 0.172549f, 0.541176f);
	w->base_colors[22] = init_rgb(0.972549f, 0.133333f, 0.694118f);
	w->base_colors[23] = init_rgb(0.976471f, 0.490196f, 0.819608f);
	w->base_colors[24] = init_rgb(0.525490f, 0.709804f, 0.898039f);
	w->base_colors[25] = init_rgb(0.874510f, 0.925490f, 0.972549f);
	w->base_colors[26] = init_rgb(0.945098f, 0.913725f, 0.749020f);
	w->base_colors[27] = init_rgb(0.972549f, 0.788235f, 0.372549f);
	w->base_colors[28] = init_rgb(0.980392f, 0.666667f, 0.000000f);
	w->base_colors[29] = init_rgb(0.674510f, 0.501961f, 0.000000f);
	w->base_colors[30] = init_rgb(0.600000f, 0.325490f, 0.003922f);
	w->base_colors[31] = init_rgb(0.854902f, 0.078431f, 0.137255f);
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
	t->base_colors[1] = init_rgb(0.933333f, 136.0f, 51.0f);
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
	app->current_preset = WIKI;
	init_wiki_preset(app);
	init_temperature_preset(app);
	init_transform(app);
	if (!init_window(app, &app->frame) || init_cl(app))
		return (0);
	init_timer(&app->timer);
	return (1);
}
