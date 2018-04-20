#include "mix.h"

t_rgb			mix_color(t_rgb x, t_rgb y, float coeff)
{
	t_rgb mixedColor;

	mixedColor.r = mix_float(x.r, y.r, coeff);
	mixedColor.g = mix_float(x.g, y.g, coeff);
	mixedColor.b = mix_float(x.b, y.b, coeff);
	return (mixedColor);
}

float			mix_float(float x, float y, float coeff)
{
	return (x * (1.0f - coeff) + y * coeff);
}
