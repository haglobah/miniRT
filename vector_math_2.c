/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:20:19 by mhedtman          #+#    #+#             */
/*   Updated: 2023/01/26 10:27:30 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_3d	sub_3d(t_3d v, t_3d w)
{
	t_3d	new;

	new = sum_3d(v, mul(-1, w));
	return (new);
}

t_3d	sub4_3d(t_3d v, t_3d w, t_3d u, t_3d z)
{
	t_3d	new;

	new = (t_3d){v.x - w.x - u.x - z.x,
		v.y - w.y - u.y - z.y,
		v.z - w.z - u.z - z.z};
	return (new);
}

double	dot(t_3d v, t_3d w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

t_3d	cross(t_3d v, t_3d w)
{
	t_3d	new;

	new = (t_3d){v.y * w.z - w.y * v.z,
		v.z * w.x - w.z * v.x,
		v.x * w.y - w.x * v.y};
	return (new);
}

double	len_squared(t_3d v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
