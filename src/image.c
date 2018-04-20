#include "fdf.h"

void	put_pixel(t_app *app, int x, int y, int color)
{
	if (x >= 0 && x < app->frame.width && y >= 0 && y < app->frame.height)
		app->frame.data[y * app->frame.width + x] = color;
}
