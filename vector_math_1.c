/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:14:03 by mhedtman          #+#    #+#             */
/*   Updated: 2023/02/01 10:05:17 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_3d	*mk_3d(t_lst *lst, double x, double y, double z)
{
	t_3d	*new;

	new = ft_calloc(1, sizeof(t_3d));
	if (new == NULL)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	add_to_list(&lst, new, NULL);
	return (new);
}

t_3d	sum_3d(t_3d v, t_3d w)
{
	t_3d	new;

	new = (t_3d){v.x + w.x, v.y + w.y, v.z + w.z};
	return (new);
}

t_3d	sum4_3d(t_3d v, t_3d w, t_3d u, t_3d z)
{
	t_3d	new;

	new = (t_3d){v.x + w.x + u.x + z.x,
		v.y + w.y + u.y + z.y,
		v.z + w.z + u.z + z.z};
	return (new);
}

t_3d	mul(double k, t_3d v)
{
	t_3d	new;

	new = (t_3d){k * v.x, k * v.y, k * v.z};
	return (new);
}
