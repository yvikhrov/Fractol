/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:50 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 18:15:21 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "color.h"
# include "clamp.h"
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "vec2i.h"
# include <math.h>
# include "timer.h"
# include <OpenCL/opencl.h>

# define MAX(a, b) ((a > b) ? a : b)

typedef enum			e_fractal
{
	MANDELBROT = 0,
	JULIA,
	NEWTON,
	HEART,
	GOOSE,
	SHIP,
	TRICORN,
	CELTIC,
	PERP1,
	PERP2,
	FRACTAL_NUM
}						t_fractal;

typedef struct			s_vec4
{
	float				x;
	float				y;
	float				z;
	float				w;
}						t_vec4;

typedef struct			s_mlx
{
	void				*ptr;
	void				*win;
	void				*img_ptr;
}						t_mlx;

typedef struct			s_image
{
	int					*data;
	int					width;
	int					height;
}						t_image;

typedef struct			s_transform
{
	double				x_shift;
	double				y_shift;
	double				zoom;
}						t_transform;

typedef struct			s_cl
{
	char				*kernel_names[FRACTAL_NUM];
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel[FRACTAL_NUM];
	cl_mem				image_buffer;
	cl_mem				color_buffer;
	size_t				global_work_size[2];
	size_t				local_work_size[2];
}						t_cl;

typedef enum			e_color_preset
{
	WIKI = 0,
	TEMPERATURE,
	PSYCHEDELIC,
	COLOR_PRESET_TOTAL

}						t_color_preset;

typedef struct			s_color
{
	int					color_num;
	float				shift;
	t_rgb				*base_colors;
	cl_float4			*colors;
}						t_color;

typedef struct			s_app
{
	t_mlx				mlx;
	t_image				frame;
	t_transform			transform;
	char				key_mask[282];
	t_timer				timer;
	int					mouse_x;
	int					mouse_y;
	int					zoom_mouse_x;
	int					zoom_mouse_y;
	int					max_iteration;
	t_cl				cl;
	t_fractal			current_fractal;
	int					update_mouse;
	t_color				color[COLOR_PRESET_TOTAL];
	t_color_preset		current_preset;
	int					show_help;
	size_t				array_size;
	size_t				kernel_size;
}						t_app;

int						init(t_app *app);
int						parse_map(int fd, t_app *app);
int						main_loop(void *param);

void					put_pixel(t_app *app, int x, int y, int color);
void					init_psychedelic(t_color *p);
void					init_wiki_preset(t_app *app);

int						quit(t_app *app);
void					ft_error(char *err_msg);
void					init_transform(t_app *app);

int						init_cl(t_app *app);
size_t					get_file(t_app *app, const char *path, char **file);

cl_float4				init_float4(t_rgb rgb);
int						key_release(int keycode, void *ctx);

#endif
