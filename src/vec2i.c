#include "vec2i.h"

t_vec2i init_vec2i(int x, int y)
{
	t_vec2i point;

	point.x = x;
	point.y = y;
	return (point);
}

int		abs_int(int x)
{
	return (x > 0 ? x : -x);
}

