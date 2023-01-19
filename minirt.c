//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/19 14:09:03 by mhedtman         ###   ########.fr       */
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
	// printf("h: %f\n", h);
	viewport_height = 2.0 * h;
	viewport_width = viewport_height * w->aspect_ratio;
	
	// print_mrt(m);
	c->pos = m->cam->pos;
	c->dir = m->cam->dir;
	t_3d save = mul(m->save_lst, -1, *c->dir);
	c->w = mk_unit(m->save_lst, save);
	// print3d("SAVE: ", save);
	print3d("w before cross", c->w);
	print3d("w before cross", c->w);
	// CAUTION vup & dir should not be the same.
	printf("TEST");
	t_3d save_two = cross(m->save_lst, *vup, c->w); // -> Here changes the value of c->w for some odd reason
	print3d("w after cross", c->w);
	print3d("SAVE TWO: ", save_two);
	c->u = mk_unit(m->save_lst, save_two);
	c->v = cross(m->save_lst, c->w, c->u);
	c->horizontal = /* focus_dist */ mul(m->save_lst, viewport_width, c->u);
	c->vertical = /* focus_dist */  mul(m->save_lst, viewport_height, c->v);
	c->llc = sub4_3d(m->save_lst, 
					 *c->pos,
					 mul(m->save_lst, 0.5, c->horizontal),
					 mul(m->save_lst, 0.5, c->vertical),
					 c->w);
	print3d("pos", *c->pos);
	print3d("dir", *c->dir);
	print3d("vup", *vup);
	print3d("u", c->u);
	print3d("v", c->v);
	print3d("horizontal", c->horizontal);
	print3d("vertical", c->vertical);
	print3d("llc", *c->llc);
	focal_length = 1.0;
	printf("TEST2\n");
	return (c);
}

uint32_t	compute_pxl_clr(t_mrt *m, t_camera *c, double x, double y)
{
	static t_3d	direction;
	t_3d	*wo_unit_dir;
	t_ray	*r;
	u_int32_t	pxl_clr;
	t_3d	hvec;
	t_3d	vvec;
	static t_3d	*old_dir;

	static	int times_called;

	hvec = mul(m->save_lst, x, c->horizontal);
	vvec = mul(m->save_lst, y, c->vertical);
	wo_unit_dir = sum4_3d(m->save_lst, *c->llc, 
		hvec,
		vvec,
		mul(m->save_lst, -1, *m->cam->pos));
	old_dir = &direction;
	direction = mk_unit(m->save_lst, *wo_unit_dir);
	if (times_called > 0 && !v_iseq(old_dir, &direction))
	{
		// printf("times_called: %i\n", times_called);
		// print3d("llc", *c->llc);
		// print3d("horizontal", *c->horizontal);
		// printf("x: %f\n", x);
		// print3d("hvec", hvec);
		// print3d("vertical", *c->vertical);
		// printf("y: %f\n", y);
		// print3d("vvec", vvec);
		// print3d("campos", *m->cam->pos);
		// print3d("ray_dir", *direction);
	}
	r = mk_ray(m->save_lst, *m->cam->pos, direction);
	// printray("our_ray", *r);
	pxl_clr = trace_ray(r, m);
	// printf("%p\n", pxl_clr);
	
	times_called += 1;
	return (pxl_clr);
}

void	fill_window(t_window *w, double width, double height)
{
	w->aspect_ratio =  width / height;
	w->width = width;
	w->height = height;
}

void	draw_scene(mlx_image_t *img, t_mrt *m)
{
	int			j;
	int			i;
	t_camera	*c;
	t_window	w;
	t_3d		*vup;
	uint32_t	clr;

	fill_window(&w, WIDTH, HEIGHT);
	vup = mk_3d(m->save_lst, 0, 1, 0);
	// t_clr *test = mk_clr(m->save_lst, 1, 2, 3);
	c = mk_camera(m, &w, vup);
	j = HEIGHT - 1;
	while (--j >= 0)
	{
		i = -1;
		while (++i < WIDTH)
		{
			double x = i / w.width;
			double y = j / w.height;
			// printf("x: %f\n", x);
			// printf("y: %f\n", y);
			clr = compute_pxl_clr(m, c, x, y);
			put_pxl(img, i, j, clr);
		}
	}
	free_all(m);
	free(c);
	// free_from_list(m->save_lst);
	// print_list(m->save_lst);
	return ;
}