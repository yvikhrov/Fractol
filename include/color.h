#ifndef COLOR_H
# define COLOR_H

typedef struct	s_rgb
{
	float		r;
	float		g;
	float		b;
}				t_rgb;

typedef struct	s_hsvtorgb
{
	float		p;
	float		q;
	float		t;
	t_rgb		rgb;
}				t_rgbtorgb;

int				rgb_to_int(t_rgb color);
t_rgb			mix_color(t_rgb x, t_rgb y, float coeff);
t_rgb			clamp_color(t_rgb color, float edge0, float edge1);
t_rgb			int_to_rgb(int int_rgb);
t_rgb			init_rgb(float red, float green, float blue);
t_rgb			hsv2rgb(t_rgb hsv);

#endif
