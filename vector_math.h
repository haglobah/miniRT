/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:12:44 by mhedtman          #+#    #+#             */
/*   Updated: 2023/01/25 16:41:30 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "objects.h"

// VECTOR FILE ONE
t_3d	*mk_3d(t_lst *lst, double x, double y, double z);
t_3d	sum_3d(t_3d v, t_3d w);
t_3d	sum4_3d(t_3d v, t_3d w, t_3d u, t_3d z);
t_3d	mul(double k, t_3d v);

// VECTOR FILE TWO
t_3d	sub_3d(t_3d v, t_3d w);
t_3d	sub4_3d(t_3d v, t_3d w, t_3d u, t_3d z);
double	dot(t_3d v, t_3d w);
t_3d	cross(t_3d v, t_3d w);
double	len_squared(t_3d v);

// VECTOR FILE THREE
double	sq(double a);
double	dist(t_3d v, t_3d w);
bool	v_iseq(t_3d *v, t_3d *w);
t_3d	at(t_ray ray, double t);
t_3d	mk_unit(t_3d v);

// VECTOR UTILS
void	printray(char *s, t_ray v);
void	print3d(char *s, t_3d v);

#endif