/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/12 15:15:57 by bhagenlo         ###   ########.fr       */
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

void	draw_pxl(mlx_image_t *img, t_mrt *m, int x, int y)
{
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
	t_3d	*direction;
	t_ray	*r;
	u_int32_t	pxl_clr;
	
	aspect_ratio = (double) WIDTH / (double) HEIGHT;
	viewport_width = ((x / (double) WIDTH) - 0.5) * aspect_ratio;
	viewport_height = (y / (double) HEIGHT) - 0.5;
	direction = mk_unit(*sum_3d(
		*mul(m->cam->fov, 
			(t_3d){viewport_width, viewport_height, 0}),
		*mul(-1, *m->cam->pos)));
	r = mk_ray(*m->cam->pos, *direction);
	pxl_clr = trace_ray(*r, m);
	put_pxl(img, x, y, pxl_clr);
}

void	draw_scene(mlx_image_t *img, t_mrt *m)
{
	double	aspect_ratio = (double) WIDTH / (double) HEIGHT;

	int j = HEIGHT - 1;
	while (--j >= 0)
	{
		int i = -1;
		while (++i < WIDTH)
		{
			draw_pxl(img, m, i, j);
		}
	}
	return ;
}