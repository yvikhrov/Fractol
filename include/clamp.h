/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:50 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:38:03 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAMP_H
# define CLAMP_H

# include "color.h"

int			clamp_int(int v, int min, int max);
float		clamp_float(float v, float min, float max);
t_rgb		clamp_rgb(t_rgb rgb, float min, float max);
double		clamp_double(double v, double min, double max);

#endif
