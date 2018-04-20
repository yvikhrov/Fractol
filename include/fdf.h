#ifndef FDF_H
# define FDF_H

# include "color.h"
# include "clamp.h"
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "vec2i.h"
# include <math.h>
# include "timer.h"
# include "cl.h"
# include <OpenCL/opencl.h>

typedef enum		e_fractal
{
	MANDELBROT = 0,
	JULIA,
	NEWTON,
	FRACTAL_NUM
}					t_fractal;


typedef struct		s_vec4
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec4;


typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img_ptr;
}					t_mlx;


typedef struct		s_image
{
	int				*data;
	int				width;
	int				height;
}					t_image;

typedef struct 		s_transform
{
	float			x_shift;
	float			y_shift;
	float			zoom;
}					t_transform;



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
}						t_cl;

typedef struct		s_app
{
	t_mlx			mlx;
	t_image			frame;
	t_transform		transform;
    int             gradient_coloring;
    t_rgb         color_max;
    t_rgb         color_min;
    float           hue_min;
    float           hue_max;
    int             perception_speed;
    char            key_mask[282];
	int				array_size;
	t_rgb			white_color;
	t_timer 		timer;
	int				mouse_x;
	int				mouse_y;
	int				zoom_mouse_x;
	int				zoom_mouse_y;
	t_cl			cl;
	t_fractal		current_fractal;
	int				update_mouse;
	int				color_num;
	cl_float4		*colors;
}					t_app;


int                 init(t_app *app, int ac, char **av);
int                 parse_map(int fd, t_app *app);
int	    	        main_loop(void *param);

void				put_pixel(t_app *app, int x, int y, int color);

int					quit(t_app *app);
void				ft_error(char *err_msg);

t_rgb				mandelbrot_color(t_app *app, int x, int y);

int					init_cl(t_app *app);


#endif
