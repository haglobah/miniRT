/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/05 11:40:36 by mhedtman         ###   ########.fr       */
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
	t_cam		*cam;
	t_sphere	*sphere;
	(void)m;
	
	cam = ft_calloc(1, sizeof(t_cam));
	sphere = ft_calloc(1, sizeof(t_sphere));
	
	cam->pos = (t_3d){0, 0, 3.5};
	cam->dir = (t_3d){0, 0, -1};
	cam->fov = 1.0;

	sphere->pos = (t_3d){0, 0, 0};
	sphere->diameter = 0.3;
	sphere->color = (t_clr){0.9 * 255, 0.2 * 255, 0.3 * 255};

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
			t_3d	*direction = normalize_vector(sum_3d(*mul(-1, cam->pos), *mk_3d(u, v, cam->fov)));
			t_ray	*r = mk_ray(cam->pos, *direction);
			put_pxl(img, i, j, color_ray(*r, sphere));
		}
	}
	return ;
}