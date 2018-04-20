/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_cross_prod.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 13:13:58 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/02/10 12:38:57 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

t_vec3	vec3_cross(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 res;

	res.x = vec1.y * vec2.z - vec1.z * vec2.y;
	res.y = vec1.z * vec2.x - vec1.x * vec2.z;
	res.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (res);
}

t_vec3	vec3_normalize(t_vec3 vec)
{
	t_vec3	res;
	float	inv_length;

	inv_length = 1.0f / sqrt(vec3_dot(vec, vec));
	res.x = vec.x * inv_length;
	res.y = vec.y * inv_length;
	res.z = vec.z * inv_length;
	return (res);
}
