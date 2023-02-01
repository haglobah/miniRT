/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:02:22 by mhedtman          #+#    #+#             */
/*   Updated: 2023/02/01 15:20:17 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "objects.h"

double		hitpoint_sphere(t_3d center, double radius, t_ray r, double *root);
void		update_hit(t_hit *h, t_uhit uh);
bool		did_hit(t_hit *h);
double		hitpoint_plane(t_3d support, t_3d normal, t_ray r);
void		hit_sphere(t_sphere *sp, t_ray r, t_hit *h);
void		hit_plane(t_plane *pl, t_ray r, t_hit *h);
void		hit_cylinder(t_cyl *cyl, t_ray r, t_hit *h);
void		hit_tube(t_cyl *cyl, t_ray ray, t_hit *hit);
void		hit_disk(t_cyl *cyl, t_ray ray, t_hit *hit);

#endif