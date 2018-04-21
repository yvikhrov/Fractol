#include "fdf.h"
#include "mix.h"
#include "handle_input.h"
#include "keys.h"
#include "timer.h"

#include <stdio.h>

typedef struct		s_complex
{
	float			im;
	float			re;
}					t_complex;

cl_float4 init_float4(t_rgb rgb)
{
	cl_float4 res;

	res.x = rgb.r;
	res.y = rgb.g;
	res.z = rgb.b;
	res.w = 1.0f;
	return (res);
}

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
	clEnqueueWriteBuffer(app->cl.queue, app->cl.color_buffer, CL_TRUE, 0, sizeof(cl_float4) * preset->color_num, preset->colors, 0, NULL, NULL);
}

void		update(t_app *app)
{
	handle_input(app, get_delta_time(&app->timer));
	app->color_max = hsv2rgb(init_rgb(app->hue_max, 0.9, 0.9));
	app->color_min = hsv2rgb(init_rgb(app->hue_min, 0.8, 0.6));
	update_color_preset(&app->color[app->current_preset], app);
}

void		render(t_app *app)
{
    int err;

	err = clSetKernelArg(app->cl.kernel[app->current_fractal], 0, sizeof(cl_mem), &app->cl.image_buffer);
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 1, sizeof(cl_mem), &app->cl.color_buffer);
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 2, sizeof(double), &app->transform.zoom);
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 3, sizeof(double), &app->transform.x_shift);
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 4, sizeof(double), &app->transform.y_shift);
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 5, sizeof(int), &app->mouse_x);
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 6, sizeof(int), &app->mouse_y);
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 7, sizeof(int), &app->frame.width);
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 8, sizeof(int), &app->frame.height);
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 9, sizeof(int), &app->kMaxIteration);
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 10, sizeof(int), &app->color[app->current_preset].color_num);

	size_t	global_work_size[] = {app->frame.width, app->frame.height};
	size_t	local_work_size[] = {16, 16};

	err = clEnqueueNDRangeKernel(app->cl.queue, app->cl.kernel[app->current_fractal], 2, NULL, global_work_size, local_work_size, 0, NULL, NULL);
	clFinish(app->cl.queue);

	//Smooth image


	err = clEnqueueReadBuffer(app->cl.queue, app->cl.image_buffer, CL_TRUE, 0, app->frame.width * app->frame.height * 4, app->frame.data, 0, NULL, NULL );
}

int			main_loop(void *param)
{
	t_app *app;

	app = (t_app*)param;
	ft_memset(app->frame.data, 0, app->frame.width * app->frame.height * 4);
	update(app);
	render(app);
	mlx_put_image_to_window(app->mlx.ptr, app->mlx.win, app->mlx.img_ptr, 0, 0);
	app->key_mask[MOUSE_ZOOM_OUT] = 0;
	app->key_mask[MOUSE_ZOOM_IN] = 0;
	return (0);
}
