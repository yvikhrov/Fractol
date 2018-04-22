/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:52:44 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 18:15:03 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		init_fractal_kernel(t_cl *cl)
{
	int			err;
	t_fractal	fractal;

	fractal = MANDELBROT;
	cl->kernel_names[MANDELBROT] = ft_strdup("mandelbrot");
	cl->kernel_names[JULIA] = ft_strdup("julia");
	cl->kernel_names[NEWTON] = ft_strdup("newton");
	cl->kernel_names[HEART] = ft_strdup("heart");
	cl->kernel_names[GOOSE] = ft_strdup("goose");
	cl->kernel_names[SHIP] = ft_strdup("ship");
	cl->kernel_names[TRICORN] = ft_strdup("tricorn");
	cl->kernel_names[CELTIC] = ft_strdup("celtic");
	cl->kernel_names[PERP1] = ft_strdup("perp1");
	cl->kernel_names[PERP2] = ft_strdup("perp2");
	while (fractal < FRACTAL_NUM)
	{
		cl->kernel[fractal] = clCreateKernel(cl->program,
						cl->kernel_names[fractal], &err);
		if (!cl->kernel[fractal] || err != CL_SUCCESS)
			return (-1);
		++fractal;
	}
	return (0);
}

int		build_program(t_app *app)
{
	int		err;
	char	*source;
	size_t	len;
	char	buffer[2048];

	len = get_file(app, "kernel.cl", &source);
	if (source == NULL)
		return (-1);
	app->cl.program = clCreateProgramWithSource(app->cl.context,
							1, (const char **)&source, &len, &err);
	if (!app->cl.program)
		return (-1);
	err = clBuildProgram(app->cl.program, 1, &(app->cl.device_id),
								"-cl-fast-relaxed-math", NULL, NULL);
	free(source);
	if (err != CL_SUCCESS)
	{
		ft_putstr("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(app->cl.program, app->cl.device_id,
				CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		ft_putstr(buffer);
		return (-1);
	}
	return (init_fractal_kernel(&app->cl));
}

void	opencl_error(const char *errinfo, const void *p, size_t cb, void *u)
{
	(void)p;
	(void)cb;
	(void)u;
	ft_putendl(errinfo);
}

int		init_cl_context(t_cl *cl)
{
	int err;

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &cl->device_id, NULL);
	if (err != CL_SUCCESS)
		return (-1);
	cl->context = clCreateContext(0, 1, &cl->device_id, opencl_error,
																NULL, &err);
	if (!cl->context)
		return (-1);
	cl->queue = clCreateCommandQueue(cl->context, cl->device_id, 0, &err);
	if (!cl->queue)
		return (-1);
	return (0);
}

int		init_cl(t_app *app)
{
	int err;
	int max_color_num;

	err = -1;
	max_color_num = 1;
	while (++err < COLOR_PRESET_TOTAL)
		max_color_num = MAX(max_color_num, app->color[err].color_num);
	app->cl.global_work_size[0] = app->frame.width;
	app->cl.global_work_size[1] = app->frame.height;
	app->cl.local_work_size[0] = 16;
	app->cl.local_work_size[1] = 16;
	if (init_cl_context(&app->cl) || build_program(app))
		return (-1);
	app->cl.image_buffer = clCreateBuffer(app->cl.context, CL_MEM_READ_WRITE,
						app->frame.width * app->frame.height * 4, NULL, &err);
	if (err != CL_SUCCESS)
		return (-1);
	app->cl.color_buffer = clCreateBuffer(app->cl.context, CL_MEM_READ_WRITE,
								sizeof(cl_float4) * max_color_num, NULL, &err);
	if (err != CL_SUCCESS)
		return (-1);
	return (0);
}
