/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/02/01 15:31:59 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_window(t_window *w, double width, double height)
{
	w->aspect_ratio = width / height;
	w->width = width;
	w->height = height;
}

void	put_pxl(mlx_image_t *img, int pxl_x, int pxl_y, int color)
{
	if (pxl_x >= WIDTH || pxl_x < 0 || pxl_y >= HEIGHT || pxl_y < 0)
		return ;
	mlx_put_pixel(img, pxl_x, pxl_y, color);
}

t_camera	*mk_camera(t_mrt *m, t_window *w, t_3d *vup)
{
	double		theta;
	double		viewport_width;
	double		viewport_height;
	t_camera	*c;

	c = (t_camera *)ft_calloc(1, sizeof(t_camera));
	theta = degrees_to_radians(m->cam->fov);
	viewport_height = 2.0 * (tan(theta / 2));
	viewport_width = viewport_height * w->aspect_ratio;
	c->pos = m->cam->pos;
	c->dir = m->cam->dir;
	c->vup = vup;
	c->w = unit(mul(-1, *c->dir));
	c->u = cross(*vup, c->w);
	c->v = cross(c->w, c->u);
	c->horizontal = mul(viewport_width, c->u);
	c->vertical = mul(viewport_height, c->v);
	c->llc = sub4_3d(
			*c->pos,
			mul(0.5, c->horizontal),
			mul(0.5, c->vertical),
			c->w);
	return (c);
}

uint32_t	compute_pxl_clr(t_mrt *m, t_camera *c, double x, double y)
{
	t_3d		direction;
	t_ray		r;
	t_hit		h;
	u_int32_t	pxl_clr;

	direction = unit(
			sum4_3d(c->llc,
				mul(x, c->horizontal),
				mul(y, c->vertical),
				mul(-1, *c->pos)));
	r = mk_ray(*m->cam->pos, direction);
	trace_ray(m, r, &h);
	pxl_clr = compute_hitpoint_clr(m, &h);
	return (pxl_clr);
}

void	draw_scene(t_options *o, mlx_image_t *img, t_mrt *m)
{
	int			counter[2];
	double		x_y[2];
	t_window	w;
	t_3d		vup;
	uint32_t	clr;

	fill_window(&w, WIDTH, HEIGHT);
	vup = (t_3d){0, -1, 0.1};
	o->camera = mk_camera(m, &w, &vup);
	counter[0] = HEIGHT - 1;
	while (--counter[0] >= 0)
	{
		counter[1] = -1;
		while (++counter[1] < WIDTH)
		{
			x_y[0] = counter[1] / w.width;
			x_y[1] = counter[0] / w.height;
			clr = compute_pxl_clr(m, o->camera, x_y[0], x_y[1]);
			put_pxl(img, counter[1], counter[0], clr);
		}
	}
	return ;
}
