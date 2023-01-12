/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/12 09:44:45 by mhedtman         ###   ########.fr       */
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

void	raytrace(mlx_image_t *img, t_mrt *m)
{
	double	aspect_ratio = (double) WIDTH / (double) HEIGHT;

	int j = HEIGHT - 1;
	while (--j >= 0)
	{
		int i = -1;
		while (++i < WIDTH)
		{
			double	u = (i / (double) WIDTH) - 0.5;
			double	v = (j / (double) HEIGHT) - 0.5;
			u = u * aspect_ratio;
			t_3d	*direction = mk_unit(*sum_3d(*mul(m->cam->fov, (t_3d){v, u, 0}), *mul(-1, *m->cam->pos)));
			t_ray	*r = mk_ray(*m->cam->pos, *direction);
			put_pxl(img, i, j, color_ray(*r, m));
		}
	}
	return ;
}