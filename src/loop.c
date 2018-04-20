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

void		update(t_app *app)
{
	handle_input(app, get_delta_time(&app->timer));
	app->color_max = hsv2rgb(init_rgb(app->hue_max, 0.9, 0.9));
	app->color_min = hsv2rgb(init_rgb(app->hue_min, 0.8, 0.6));
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
	err |= clSetKernelArg(app->cl.kernel[app->current_fractal], 10, sizeof(int), &app->color_num);

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
