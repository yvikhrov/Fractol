#include "fdf.h"

#include <stdio.h>

//int		read_file(char *path, char **file)
//{
//	char	*line;
//	int		fd;
//	int		err;
//
//	fd = open(path, O_RDONLY);
//	if (fd < 0)
//		return (-1);
//	while ((err = get_next_line(fd, &line)) > 0)
//	{
//		if (*file == NULL)
//			*file = line;
//		else
//			*file = ft_strjoin(*file, line);
//		// LEAKS
//	}
//	return (err == -1);
//}

void		init_fractal_name(t_cl *cl)
{
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


}

size_t        get_file(const char *name, char **str)
{
	FILE    *file;
	size_t    len;

	if (!(file = fopen(name, "r")))
		ft_error("get_file(): open failed");
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (!(*str = (char*)malloc(sizeof(char) * (len + 1))))
		ft_error("get_file(): malloc error");
	fread(*str, len, 1, file);
	(*str)[len] = '\0';
	fclose(file);
	return (len);
}

int		build_program(t_app *app)
{
	int		err;
	char	*source;
	size_t	len;
	char	buffer[2048];

	len = get_file("kernel.cl", &source);
	app->cl.program = clCreateProgramWithSource(app->cl.context, 1, (const char **)&source, &len, &err);
	if (!app->cl.program)
		return (-1);
	err = clBuildProgram(app->cl.program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		ft_putstr("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(app->cl.program, app->cl.device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		ft_putstr(buffer);
		return (-1);
	}



	t_fractal fractal = MANDELBROT;
	init_fractal_name(&app->cl);
	while (fractal < FRACTAL_NUM)
	{
		app->cl.kernel[fractal] = clCreateKernel(app->cl.program, app->cl.kernel_names[fractal], &err);
		if (!app->cl.kernel[fractal] || err != CL_SUCCESS)
			return (-1);
		++fractal;
	}



	return (0);
}

void	opencl_error(const char *errinfo, const void *private_info, size_t cb, void *user_data)
{
	(void)private_info;
	(void)cb;
	(void)user_data;
	ft_putendl(errinfo);
}

int		init_cl(t_app *app)
{
	int err;

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &app->cl.device_id, NULL);
	if (err != CL_SUCCESS)
		return (-1);
	app->cl.context = clCreateContext(0, 1, &app->cl.device_id, opencl_error, NULL, &err);
	if (!app->cl.context)
		return (-1);
	app->cl.queue = clCreateCommandQueue(app->cl.context, app->cl.device_id, 0, &err);
	if (!app->cl.queue)
		return (-1);
	if (build_program(app))
		return (-1);
	app->cl.image_buffer = clCreateBuffer(app->cl.context, CL_MEM_READ_WRITE, app->frame.width * app->frame.height * 4, NULL, &err);
	if (err != CL_SUCCESS)
		return (-1);
	app->cl.color_buffer = clCreateBuffer(app->cl.context, CL_MEM_READ_WRITE, sizeof(cl_float4) * app->color[app->current_preset].color_num, NULL, &err);
	if (err != CL_SUCCESS)
		return (-1);
	return (0);
}
