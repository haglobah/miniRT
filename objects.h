/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:23:00 by mhedtman          #+#    #+#             */
/*   Updated: 2023/02/01 14:59:37 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <stdio.h>

typedef struct s_3d_vector
{
	double	x;
	double	y;
	double	z;

}	t_3d;

typedef struct s_color
{
	u_int8_t	r;
	u_int8_t	g;
	u_int8_t	b;
	u_int8_t	a;

}	t_clr;

typedef struct s_ray
{
	t_3d	pos;
	t_3d	dir;

}	t_ray;

typedef struct s_free_list
{
	t_3d				*vec;
	t_clr				*clr;
	struct s_free_list	*next;
}	t_lst;

typedef struct s_hit
{
	t_3d		pos;
	t_3d		normal;
	bool		from_plane;
	double		t;
	t_clr		clr;

}	t_hit;

typedef struct s_ambient_light
{
	double		ratio;
	t_clr		color;
}	t_ambient;

typedef struct s_cam
{
	t_3d		*pos;
	t_3d		*dir;
	double		fov;
}	t_cam;

typedef struct s_light
{
	t_3d	*pos;
	double	brightness;
	t_clr	color;
}	t_light;

typedef struct s_sphere
{
	t_3d		*pos;
	double		diameter;
	t_clr		color;
}	t_sphere;

typedef struct s_plane
{
	t_3d	*pos;
	t_3d	*normal;
	t_clr	color;
}	t_plane;

typedef struct s_coor_plane
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_coor_plane;

typedef struct s_cyl
{
	t_3d		*pos;
	t_3d		*axis;
	double		diameter;
	double		height;
	t_clr		color;
}	t_cyl;

typedef struct s_window
{
	double	aspect_ratio;
	double	height;
	double	width;
}	t_window;

typedef struct s_camera
{
	t_3d	*pos;
	t_3d	*dir;
	t_3d	*vup;
	t_3d	w;
	t_3d	u;
	t_3d	v;
	t_3d	horizontal;
	t_3d	vertical;
	t_3d	llc;
	double	vfov;
}	t_camera;

typedef struct s_tube_calculation
{
	t_3d	a;
	double	r;
	double	h;
	t_3d	n;
	t_3d	b;
	t_3d	f;
	t_3d	nxa;
	double	d[2];
	double	t[2];
}	t_tube;

typedef struct s_tube_hit
{
	double	t;
	double	h;
	double	d;
	t_3d	a;
	t_3d	b;
	t_cyl	*cyl;
	t_ray	ray;
	t_hit	*hit;
}	t_tube_hit;

typedef struct s_cyl_ray_hit
{
	t_hit	*hit;
	t_cyl	*cyl;
	t_ray	ray;
}	t_crh;

typedef struct s_update_hit
{
	t_3d	pos;
	double	t;
	t_3d	normal;
	bool	from_plane;
	t_clr	clr;
}	t_uhit;

#endif