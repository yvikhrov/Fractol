//
//  clamp.h
//  fdf
//
//  Created by Yelyzaveta on 01.04.2018.
//

#ifndef CLAMP_H
# define CLAMP_H

# include "color.h"

int			clamp_int(int v, int min, int max);
float		clamp_float(float v, float min, float max);
t_rgb		clamp_rgb(t_rgb rgb, float min, float max);
double		clamp_double(double v, double min, double max);


#endif
