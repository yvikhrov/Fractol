#include "fdf.h"
#include "handle_input.h"

static t_app	*get_app()
{
	static t_app *app = NULL;

	if (app == NULL)
	{
		app = (t_app*)malloc(sizeof(t_app));
		ft_memset(app, 0, sizeof(t_app));
	}
	return app;
}

int				quit(t_app *app)
{
	mlx_destroy_image(app->mlx.ptr, app->mlx.img_ptr);
	mlx_destroy_window(app->mlx.ptr, app->mlx.win);
	free(app);
	exit(0);
}

static void		print_usage(void)
{
	ft_putendl("Usage: ./fractol 'fractal name' ['fractal name']");
	ft_putendl("List of available fractals:");
	ft_putendl("Mandelbrot");
	ft_putendl("Julia");
	ft_putendl("Newton");
	ft_putendl("");
	exit(EXIT_FAILURE);
}

void check_fractol(char *c, t_app *app)
{
	int i;
	char *fractal_name;

	i = -1;
	fractal_name = ft_strdup(c);
	while (fractal_name[++i])
		fractal_name[i] = ft_tolower(fractal_name[i]);
	if (!ft_strcmp(fractal_name, "julia"))
		app->current_fractal = JULIA;
	else if (!ft_strcmp(fractal_name, "newton"))
		app->current_fractal = NEWTON;
	else if (!ft_strcmp(fractal_name, "mandelbrot"))
		app->current_fractal = MANDELBROT;
	else
		print_usage();
	free(fractal_name);
}

int		main(int ac, char **av)
{
	t_app	*app;
	pid_t	id;
	char	*s;

	s = NULL;
	app = get_app();
	if (ac == 2)
		s = av[1];
	else if (ac == 3)
	{
		id = fork();
		s = (id == 0) ? av[2] : av[1];
	}
	else
		print_usage();
	check_fractol(s, app);
	if (!init(app))
		return (0);
	mlx_mouse_hook(app->mlx.win, mouse_hook, app);
	mlx_hook(app->mlx.win, 17, 0, quit, app);
	mlx_hook(app->mlx.win, 2, 0, key_press, app);
	mlx_hook(app->mlx.win, 6, 0, mouse_position_hook, app);
	mlx_hook(app->mlx.win, 3, 0, key_release, app);
	mlx_loop(app->mlx.ptr);
	return (0);
}
