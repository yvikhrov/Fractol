/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:17 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 18:29:52 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "handle_input.h"

static t_app	*get_app(void)
{
	static t_app *app = NULL;

	if (app == NULL)
	{
		app = (t_app*)malloc(sizeof(t_app));
		ft_memset(app, 0, sizeof(t_app));
	}
	return (app);
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
	ft_putendl("Usage: ./fractol 'fractal name'");
	ft_putendl("List of available fractals:");
	ft_putendl("- Mandelbrot");
	ft_putendl("- Julia");
	ft_putendl("- Newton");
	ft_putendl("- Heart");
	ft_putendl("- Goose");
	ft_putendl("- Ship");
	ft_putendl("- Tricorn");
	ft_putendl("- Celtic");
	ft_putendl("- Perpendicular Mandelbrot");
	ft_putendl("- Perpendicular Celtic");
	exit(EXIT_FAILURE);
}

void			check_fractol(char *c, t_app *app)
{
	int		i;
	char	*fractal_name;

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

int				main(int ac, char **av)
{
	t_app	*app;

	app = get_app();
	if (ac == 2)
		check_fractol(av[1], app);
	else
		print_usage();
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
