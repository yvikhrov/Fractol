/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Admin <Admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 21:51:29 by yvikhrov          #+#    #+#             */
/*   Updated: 2018/02/09 23:50:00 by Admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	res.z = vec1.z + vec2.z;
	return (res);
}

t_vec3	vec3_sub(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	res;

	res.x = vec1.x - vec2.x;
	res.y = vec1.y - vec2.y;
	res.z = vec1.z - vec2.z;
	return (res);
}

t_vec3	vec3_mult_scalar(t_vec3 vec, float scalar)
{
	t_vec3	res;

	res.x = vec.x * scalar;
	res.y = vec.y * scalar;
	res.z = vec.z * scalar;
	return (res);
}

t_vec3	vec3_mult_vec3(t_vec3 vec1, t_vec3 vec2)
{
		t_vec3	res;

	res.x = vec1.x * vec2.x;
	res.y = vec1.y * vec2.y;
	res.z = vec1.z * vec2.z;
	return (res);	
}
