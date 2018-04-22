/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:50 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:38:35 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIX_H
# define MIX_H

# include "color.h"

t_rgb			mix_color(t_rgb x, t_rgb y, float coeff);
float			mix_float(float x, float y, float coeff);

#endif
