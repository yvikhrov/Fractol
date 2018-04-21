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
	HEART,
	GOOSE,
	SHIP,
	TRICORN,
	CELTIC,
	PERP1,
	PERP2,
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
	double			x_shift;
	double			y_shift;
	double			zoom;
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

typedef enum			e_color_preset
{
	WIKI = 0,
	TEMPERATURE,
	COLOR_PRESET_TOTAL

}						t_color_preset;

typedef struct			s_color
{
	int					color_num;
	float				shift;
	t_rgb				*base_colors;
	cl_float4			*colors;
}						t_color;

typedef struct		s_app
{
	t_mlx			mlx;
	t_image			frame;
	t_transform		transform;
	t_rgb			color_max;
	t_rgb			color_min;
	float			hue_min;
	float			hue_max;
	char			key_mask[282];
	int				array_size;
	t_timer 		timer;
	int				mouse_x;
	int				mouse_y;
	int				zoom_mouse_x;
	int				zoom_mouse_y;
	int				kMaxIteration;
	t_cl			cl;
	t_fractal		current_fractal;
	int				update_mouse;
	t_color			color[COLOR_PRESET_TOTAL];
	t_color_preset	current_preset;
}					t_app;


int                 init(t_app *app);
int                 parse_map(int fd, t_app *app);
int	    	        main_loop(void *param);

void				put_pixel(t_app *app, int x, int y, int color);

int					quit(t_app *app);
void				ft_error(char *err_msg);
void				init_transform(t_app *app);

t_rgb				mandelbrot_color(t_app *app, int x, int y);

int					init_cl(t_app *app);


#endif
