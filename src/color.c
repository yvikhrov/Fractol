#include "fdf.h"

t_rgb			init_rgb(float r, float g, float b)
{
	t_rgb rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

t_rgb			hsv2rgb(t_rgb hsv)
{
	t_rgb		res;
	t_rgbtorgb	norm;
	float		fract;

	(hsv.r == 360.0f) ? (hsv.r = 0.0f) : (hsv.r /= 60.0f);
	fract = hsv.r - floor(hsv.r);
	norm.p = hsv.b * (1.0f - hsv.g);
	norm.q = hsv.b * (1.0f - hsv.g * fract);
	norm.t = hsv.b * (1.0f - hsv.g * (1.0f - fract));
	if (0.0f <= hsv.r && hsv.r < 1.0f)
		res = init_rgb(hsv.b, norm.t, norm.p);
	else if (1.0f <= hsv.r && hsv.r < 2.0f)
		res = init_rgb(norm.q, hsv.b, norm.p);
	else if (2.0f <= hsv.r && hsv.r < 3.0f)
		res = init_rgb(norm.p, hsv.b, norm.t);
	else if (3.0f <= hsv.r && hsv.r < 4.0f)
		res = init_rgb(norm.p, norm.q, hsv.b);
	else if (4.0f <= hsv.r && hsv.r < 5.0f)
		res = init_rgb(norm.t, norm.p, hsv.b);
	else if (5.0f <= hsv.r && hsv.r < 6.0f)
		res = init_rgb(hsv.b, norm.p, norm.q);
	else
		res = init_rgb(0.0f, 0.0f, 0.0f);
	return (res);
}

int				rgb_to_int(t_rgb color)
{
	int result;

	result = 0;
	result += color.b * 255.0f;
	result += ((int)(color.g * 255.0f)) << 8;
	result += ((int)(color.r * 255.0f)) << 16;
	return (result);
}

t_rgb			int_to_rgb(int int_rgb)
{
	t_rgb color;

	color.b = (float)(int_rgb & 255) / 255.0f;
	color.g = (float)((int_rgb >> 8) & 255) / 255.0f;
	color.r = (float)((int_rgb >> 16) & 255) / 255.0f;
	return (color);
}

