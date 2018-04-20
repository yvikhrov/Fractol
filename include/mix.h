#ifndef MIX_H
# define MIX_H

# include "color.h"

t_rgb			mix_color(t_rgb x, t_rgb y, float coeff);
float			mix_float(float x, float y, float coeff);

#endif
