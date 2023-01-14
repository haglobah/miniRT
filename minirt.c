/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/14 18:12:49 by bhagenlo         ###   ########.fr       */
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
	
	c = (t_camera *)ft_calloc(1, sizeof(t_camera));
	theta = degrees_to_radians(m->cam->fov);
	h = tan(theta / 2);
	printf("h: %f\n", h);
	viewport_height = 2.0 * h;
	viewport_width = viewport_height * w->aspect_ratio;
	
	// print_mrt(m);
	c->pos = m->cam->pos;
	printf("here\n");
	c->dir = m->cam->dir;
	c->w = mk_unit(*mul(-1, *c->dir));
	// CAUTION vup & dir should not be the same.
	c->u = mk_unit(*cross(*vup, *c->w));
	c->v = cross(*c->w, *c->u);
	c->horizontal = /* focus_dist */ mul(viewport_width, *c->u);
	c->vertical = /* focus_dist */  mul(viewport_height, *c->v);
	c->llc = sub4_3d(*c->pos,
					 *mul(0.5, *c->horizontal),
					 *mul(0.5, *c->vertical),
					 *c->w);
	print3d("pos", *c->pos);
	print3d("dir", *c->dir);
	print3d("vup", *vup);
	print3d("u", *c->u);
	print3d("v", *c->v);
	print3d("w", *c->w);
	print3d("horizontal", *c->horizontal);
	print3d("vertical", *c->vertical);
	print3d("llc", *c->llc);
	focal_length = 1.0;
	return (c);
}

void	draw_pxl(mlx_image_t *img, t_mrt *m, t_camera *c, int x, int y)
{
	t_3d	*direction;
	t_3d	*wo_unit_dir;
	t_ray	*r;
	u_int32_t	pxl_clr;
	t_3d	hvec;
	t_3d	vvec;

	hvec = *mul(x, *c->horizontal);
	vvec = *mul(y, *c->vertical);
	// print3d("llc", *c->llc);
	// print3d("hvec", hvec);
	// print3d("vvec", vvec);
	// print3d("campos", *m->cam->pos);
	wo_unit_dir = sum4_3d(*c->llc, 
		hvec,
		vvec,
		*mul(-1, *m->cam->pos));
	direction = mk_unit(*wo_unit_dir);
	// print3d("ray_dir", *wo_unit_dir);
	r = mk_ray(*m->cam->pos, *direction);
	printray("our_ray", *r);
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
	t_3d		*vup;

	fill_window(&w, WIDTH, HEIGHT);
	vup = mk_3d(0, 1, 0);
	print3d("vup", *vup);
	c = mk_camera(m, &w, vup);
	j = HEIGHT - 1;
	while (--j >= 0)
	{
		i = -1;
		while (++i < WIDTH)
		{
			double x = i / w.width;
			double y = j / w.height;
			draw_pxl(img, m, c, x, y);
		}
	}
	return ;
}