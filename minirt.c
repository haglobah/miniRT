/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/13 14:23:36 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	offset_x(int window_width)
// {
// 	return (window_width / 3);
// }

// int	offset_y(int window_height)
// {
// 	return (window_height / 8);
// }

void	put_pxl(mlx_image_t *img, int pxl_x, int pxl_y, int color)
{
	if (pxl_x >= WIDTH || pxl_x < 0 || pxl_y >= HEIGHT || pxl_y < 0)
		return ;
	mlx_put_pixel(img, pxl_x, pxl_y, color);
}

t_camera	*mk_camera(t_mrt *m, t_window *w, t_3d *vup)
{
	double	theta;
	double	h;
	double	focal_length;
	double	viewport_width;
	double	viewport_height;
	t_camera	*c;
	
	theta = degrees_to_radians(m->cam->fov);
	h = tan(theta / 2);
	viewport_height = 2.0 * h;
	viewport_width = viewport_height * w->aspect_ratio;
	
	c->pos = m->cam->pos;
	c->dir = m->cam->dir;
	c->w = mk_unit(*c->dir);
	c->u = mk_unit(*cross(*vup, *c->w));
	c->v = cross(*c->w, *c->u);
	c->horizontal = /* focus_dist */ mul(viewport_width, *c->u);
	c->vertical = /* focus_dist */  mul(viewport_height, *c->v);
	c->llc = sub4_3d(*c->pos,
					 *mul(0.5, *c->horizontal),
					 *mul(0.5, *c->vertical),
					 /* focus_dist*/*c->w);
	focal_length = 1.0;
	return (c);
}

void	draw_pxl(mlx_image_t *img, t_mrt *m, t_camera *c, int x, int y)
{
	t_3d	*direction;
	t_ray	*r;
	u_int32_t	pxl_clr;


	direction = mk_unit(
	*sub_3d(
		*mul(m->cam->fov, 
			*sum_3d(*c->horizontal, *c->vertical)),
		*m->cam->pos));
	r = mk_ray(*m->cam->pos, *direction);
	pxl_clr = trace_ray(r, m);
	put_pxl(img, x, y, pxl_clr);
}

void	fill_window(t_window *w, double width, double height)
{
	w->aspect_ratio =  width / height;
	w->width = width;
	w->width = height;
}

void	draw_scene(mlx_image_t *img, t_mrt *m)
{
	int			j;
	int			i;
	t_camera	*c;
	t_window	w;

	fill_window(&w, WIDTH, HEIGHT);
	c = mk_camera(m, &w, mk_3d(0, 0, 1));
	j = HEIGHT - 1;
	while (--j >= 0)
	{
		i = -1;
		while (++i < WIDTH)
		{
			draw_pxl(img, m, c, i, j);
		}
	}
	return ;
}