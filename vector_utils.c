/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:24:11 by mhedtman          #+#    #+#             */
/*   Updated: 2023/01/25 16:42:33 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print3d(char *s, t_3d v)
{
	printf("%s: (%f %f %f)\n", s, v.x, v.y, v.z);
}

void	printray(char *s, t_ray v)
{
	printf("%s DIR: (%f %f %f)\n", s, v.dir.x, v.dir.y, v.dir.z);
	printf("%s POS: (%f %f %f)\n", s, v.pos.x, v.pos.y, v.pos.z);
}
