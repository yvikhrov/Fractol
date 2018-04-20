#include "libft.h"
#include "fdf.h"
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
