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

cl_float4 init_float4(float r, float g, float b, float a)
{
	cl_float4 res;

	res.x = r;
	res.y = g;
	res.z = b;
	res.w = a;
	return (res);
}

int			init(t_app *app, int ac, char **av)
{
	if (ac != 2)
		return (0);
//
//
//	app->color_num = 4;
//	app->colors = malloc(sizeof(cl_float4) * app->color_num);
//	app->colors[0] = init_float4(0.89f, 0.15f, 0.82f, 1.0f);
//	app->colors[1] = init_float4(0.15f, 0.82f, 0.89f, 1.0f);
//	app->colors[2] = init_float4(0.65f, 0.22f, 0.89f, 1.0f);
//	app->colors[3] = init_float4(0.25f, 0.92f, 0.29f, 1.0f);
//

	app->color_num = 32;
	app->colors = malloc(sizeof(cl_float4) * app->color_num);
	app->colors[0] = init_float4(0.098039f, 0.027451f, 0.101961f, 1.0f);
	app->colors[1] = init_float4(0.258824f, 0.117647f, 0.058824f, 1.0f);
	app->colors[2] = init_float4(0.035294f, 0.003922f, 0.184314f, 1.0f);
	app->colors[3] = init_float4(0.015686f, 0.015686f, 0.286275f, 1.0f);
	app->colors[4] = init_float4(0.000000f, 0.027451f, 0.392157f, 1.0f);
	app->colors[5] = init_float4(0.047059f, 0.172549f, 0.541176f, 1.0f);
	app->colors[6] = init_float4(0.094118f, 0.321569f, 0.694118f, 1.0f);
	app->colors[7] = init_float4(0.223529f, 0.490196f, 0.819608f, 1.0f);
	app->colors[8] = init_float4(0.525490f, 0.709804f, 0.898039f, 1.0f);
	app->colors[9] = init_float4(0.827451f, 0.925490f, 0.972549f, 1.0f);
	app->colors[10] = init_float4(0.945098f, 0.913725f, 0.749020f, 1.0f);
	app->colors[11] = init_float4(0.972549f, 0.788235f, 0.372549f, 1.0f);
	app->colors[12] = init_float4(1.000000f, 0.666667f, 0.000000f, 1.0f);
	app->colors[13] = init_float4(0.800000f, 0.501961f, 0.000000f, 1.0f);
	app->colors[14] = init_float4(0.600000f, 0.341176f, 0.000000f, 1.0f);
	app->colors[15] = init_float4(0.415686f, 0.203922f, 0.011765f, 1.0f);
	app->colors[16] = init_float4(0.949020f, 0.000000f, 0.078431f, 1.0f);
	app->colors[17] = init_float4(0.976471f, 0.027451f, 0.101961f, 1.0f);
	app->colors[18] = init_float4(0.976471f, 0.011765f, 1.000000f, 1.0f);
	app->colors[19] = init_float4(0.956863f, 0.015686f, 0.286275f, 1.0f);
	app->colors[20] = init_float4(1.000000f, 0.003922f, 0.392157f, 1.0f);
	app->colors[21] = init_float4(1.000000f, 0.172549f, 0.541176f, 1.0f);
	app->colors[22] = init_float4(0.972549f, 0.133333f, 0.694118f, 1.0f);
	app->colors[23] = init_float4(0.976471f, 0.490196f, 0.819608f, 1.0f);
	app->colors[24] = init_float4(0.525490f, 0.709804f, 0.898039f, 1.0f);
	app->colors[25] = init_float4(0.874510f, 0.925490f, 0.972549f, 1.0f);
	app->colors[26] = init_float4(0.945098f, 0.913725f, 0.749020f, 1.0f);
	app->colors[27] = init_float4(0.972549f, 0.788235f, 0.372549f, 1.0f);
	app->colors[28] = init_float4(0.980392f, 0.666667f, 0.000000f, 1.0f);
	app->colors[29] = init_float4(0.674510f, 0.501961f, 0.000000f, 1.0f);
	app->colors[30] = init_float4(0.600000f, 0.325490f, 0.003922f, 1.0f);
	app->colors[31] = init_float4(0.854902f, 0.078431f, 0.137255f, 1.0f);


	app->current_fractal = JULIA;
	app->update_mouse = 1;
	app->kMaxIteration = 300;
	app->mouse_x = 0;
	app->mouse_y = 0;
	app->transform.x_shift = 0.0f;
	app->transform.y_shift = 0.0f;
	app->transform.zoom = 1.0f;
	app->white_color = init_rgb(1.0f, 1.0f, 1.0f);
	if (!init_window(app, &app->frame) || init_cl(app))
		return (0);
	init_timer(&app->timer);
	return (1);
}
