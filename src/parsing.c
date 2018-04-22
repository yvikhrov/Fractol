/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:17 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 18:19:48 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"
#include <limits.h>

void				free_array_of_strings(char **strings)
{
	char **tmp;

	tmp = strings;
	while (*strings)
	{
		free(*strings);
		strings++;
	}
	free(tmp);
}

char				**realloc_lines(char **lines, t_app *app)
{
	register size_t	i;
	char			**new_lines;

	new_lines = (char**)malloc(sizeof(char*) * app->array_size * 2);
	i = 0;
	while (i < app->array_size)
	{
		new_lines[i] = lines[i];
		i++;
	}
	free(lines);
	app->array_size *= 2;
	return (new_lines);
}

size_t				write_file(char **file, t_app *app,
								int line_num, char **lines)
{
	int		i;
	size_t	offset;

	*file = (char*)malloc(sizeof(char) * (app->kernel_size + 1 + line_num));
	i = -1;
	offset = 0;
	while (++i < line_num)
	{
		ft_memcpy(*file + offset, lines[i], ft_strlen(lines[i]));
		offset += ft_strlen(lines[i]);
		(*file)[offset++] = '\n';
	}
	(*file)[offset] = '\0';
	free_array_of_strings(lines);
	return (app->kernel_size + line_num);
}

size_t				get_file(t_app *app, const char *path, char **file)
{
	char	*line;
	char	**lines;
	int		fd;
	size_t	line_num;

	app->array_size = 512;
	app->kernel_size = 0;
	*file = NULL;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		ft_putstr("Missing file: ");
		ft_putendl((char*)path);
		return (0);
	}
	lines = (char**)malloc(sizeof(char*) * app->array_size);
	ft_memset(lines, 0, sizeof(char*) * app->array_size);
	line_num = 0;
	while (get_next_line(fd, &line))
	{
		if (line_num >= app->array_size)
			lines = realloc_lines(lines, app);
		lines[line_num++] = line;
		app->kernel_size += ft_strlen(line);
	}
	return (write_file(file, app, line_num, lines));
}
