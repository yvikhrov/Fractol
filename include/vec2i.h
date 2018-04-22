/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvikhrov <yvikhrov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:18:50 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/04/22 17:38:42 by yvikhrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2I_H
# define VEC2I_H

typedef struct		s_vec2i
{
	int				x;
	int				y;
}					t_vec2i;

int					manhattan_dist_vec2(t_vec2i start, t_vec2i end);
t_vec2i				init_vec2i(int x, int y);

#endif
