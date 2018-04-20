#include "fdf.h"

void				ft_error(char *err_msg)
{
	if (err_msg)
		ft_putendl_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}
