/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:17 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:36:21 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_app *app, int x, int y, int color)
{
	if (x >= 0 && x < app->frame.width && y >= 0 && y < app->frame.height)
		app->frame.data[y * app->frame.width + x] = color;
}

void	init_wiki_preset2(t_color *w)
{
	w->base_colors[13] = init_rgb(0.800000f, 0.501961f, 0.000000f);
	w->base_colors[14] = init_rgb(0.600000f, 0.341176f, 0.000000f);
	w->base_colors[15] = init_rgb(0.415686f, 0.203922f, 0.011765f);
	w->base_colors[16] = init_rgb(0.949020f, 0.000000f, 0.078431f);
	w->base_colors[17] = init_rgb(0.976471f, 0.027451f, 0.101961f);
	w->base_colors[18] = init_rgb(0.976471f, 0.011765f, 1.000000f);
	w->base_colors[19] = init_rgb(0.956863f, 0.015686f, 0.286275f);
	w->base_colors[20] = init_rgb(1.000000f, 0.003922f, 0.392157f);
	w->base_colors[21] = init_rgb(1.000000f, 0.172549f, 0.541176f);
	w->base_colors[22] = init_rgb(0.972549f, 0.133333f, 0.694118f);
	w->base_colors[23] = init_rgb(0.976471f, 0.490196f, 0.819608f);
	w->base_colors[24] = init_rgb(0.525490f, 0.709804f, 0.898039f);
	w->base_colors[25] = init_rgb(0.874510f, 0.925490f, 0.972549f);
	w->base_colors[26] = init_rgb(0.945098f, 0.913725f, 0.749020f);
	w->base_colors[27] = init_rgb(0.972549f, 0.788235f, 0.372549f);
	w->base_colors[28] = init_rgb(0.980392f, 0.666667f, 0.000000f);
	w->base_colors[29] = init_rgb(0.674510f, 0.501961f, 0.000000f);
	w->base_colors[30] = init_rgb(0.600000f, 0.325490f, 0.003922f);
	w->base_colors[31] = init_rgb(0.854902f, 0.078431f, 0.137255f);
}

void	init_wiki_preset(t_app *app)
{
	t_color *w;

	w = &app->color[WIKI];
	w->shift = 0;
	w->color_num = 32;
	w->base_colors = malloc(sizeof(t_rgb) * w->color_num);
	w->colors = malloc(sizeof(cl_float4) * w->color_num);
	w->base_colors[0] = init_rgb(0.098039f, 0.027451f, 0.101961f);
	w->base_colors[1] = init_rgb(0.258824f, 0.117647f, 0.058824f);
	w->base_colors[2] = init_rgb(0.035294f, 0.003922f, 0.184314f);
	w->base_colors[3] = init_rgb(0.015686f, 0.015686f, 0.286275f);
	w->base_colors[4] = init_rgb(0.000000f, 0.027451f, 0.392157f);
	w->base_colors[5] = init_rgb(0.047059f, 0.172549f, 0.541176f);
	w->base_colors[6] = init_rgb(0.094118f, 0.321569f, 0.694118f);
	w->base_colors[7] = init_rgb(0.223529f, 0.490196f, 0.819608f);
	w->base_colors[8] = init_rgb(0.525490f, 0.709804f, 0.898039f);
	w->base_colors[9] = init_rgb(0.827451f, 0.925490f, 0.972549f);
	w->base_colors[10] = init_rgb(0.945098f, 0.913725f, 0.749020f);
	w->base_colors[11] = init_rgb(0.972549f, 0.788235f, 0.372549f);
	w->base_colors[12] = init_rgb(1.000000f, 0.666667f, 0.000000f);
	init_wiki_preset2(w);
}

void	init_psychedelic(t_color *p)
{
	p->shift = 0;
	p->color_num = 6;
	p->base_colors = malloc(sizeof(t_rgb) * p->color_num);
	p->colors = malloc(sizeof(cl_float4) * p->color_num);
	p->base_colors[0] = init_rgb(38.0f / 255, 197.0f / 255, 95.0f / 255);
	p->base_colors[1] = init_rgb(239.0f / 255, 38.0f / 255, 71.0f / 255);
	p->base_colors[2] = init_rgb(232.0f / 255, 164.0f / 255, 39.0f / 255);
	p->base_colors[3] = init_rgb(19.0f / 255, 96.0f / 255, 147.0f / 255);
	p->base_colors[4] = init_rgb(108.0f / 255, 15.0f / 255, 113.0f / 255);
	p->base_colors[5] = init_rgb(230.0f / 255, 182.0f / 255, 108.0f / 255);
}
