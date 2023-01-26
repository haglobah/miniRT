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
	viewport_height = 2.0 * h;
	viewport_width = viewport_height * w->aspect_ratio;

	c->pos = m->cam->pos;
	c->dir = m->cam->dir;
	c->w = unit(mul(-1, *c->dir));
	c->u = unit(cross(*vup, c->w));
	c->v = cross(c->w, c->u);
	c->horizontal = mul(viewport_width, c->u);
	c->vertical = mul(viewport_height, c->v);
	c->llc = sub4_3d(
				*c->pos,
				mul(0.5, c->horizontal),
				mul(0.5, c->vertical),
				c->w);
	// print3d("pos", *c->pos);
	// print3d("dir", *c->dir);
	// print3d("vup", *vup);
	// print3d("u", c->u);
	// print3d("v", c->v);
	// print3d("horizontal", c->horizontal);
	// print3d("vertical", c->vertical);
	// print3d("llc", c->llc);
	focal_length = 1.0;
	return (c);
}

uint32_t	compute_pxl_clr(t_mrt *m, t_camera *c, double x, double y)
{
	static t_3d	direction;
	t_3d	wo_unit_dir;
	t_ray	r;
	u_int32_t	pxl_clr;
	t_3d	hvec;
	t_3d	vvec;
	static t_3d	*old_dir;

	static	int times_called;

	hvec = mul(x, c->horizontal);
	vvec = mul(y, c->vertical);
	wo_unit_dir = sum4_3d(c->llc, 
		hvec,
		vvec,
		mul(-1, *m->cam->pos));
	old_dir = &direction;
	direction = unit(wo_unit_dir);
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
	r = mk_ray(*m->cam->pos, direction);
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

// void	move(mlx_key_data_t key, void *param)
// {
// 	t_mrt	*m;
// 	t_3d	pos;

// 	m = (t_mrt *)param;
// 	printf("ADRESS OF M: %p\n", m);
// 	print_mrt(m);
// 	if (key.key == MLX_KEY_DOWN)
// 	{
// 		printf("TEST\n");
// 		pos = sum_3d(*m->cam->pos, (t_3d){1, 1, 1});
// 		free(m->cam->pos);
// 		m->cam->pos = mk_3d(NULL, pos.x, pos.y, pos.z);
// 	}
// }

void	draw_scene(t_options *o, mlx_t *mlx, mlx_image_t *img, t_mrt *m)
{
	int			j;
	int			i;
	t_camera	*c;
	t_window	w;
	t_3d		*vup;
	uint32_t	clr;

	fill_window(&w, WIDTH, HEIGHT);
	//hooks für change in m
	// print3d("CAM POS: ", *m->cam->pos);
	// mlx_loop_hook(mlx, &move, m);
	vup = mk_3d(m->save_lst, 0, 1, 0);
	o->camera = mk_camera(m, &w, vup);
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
			clr = compute_pxl_clr(m, o->camera, x, y);
			put_pxl(img, i, j, clr);
		}
	}
	// free(c);
	return ;
}