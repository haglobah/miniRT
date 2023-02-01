/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:09:19 by mhedtman          #+#    #+#             */
/*   Updated: 2023/02/01 15:09:53 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_cylinder(t_cyl *cyl, t_ray ray, t_hit *hit)
{
	hit_tube(cyl, ray, hit);
	hit_disk(cyl, ray, hit);
}
