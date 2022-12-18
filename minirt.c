/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/18 14:43:52 by mhedtman         ###   ########.fr       */
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
	cam->pos = (t_3d){0, 0, 0};
	cam->dir = (t_3d){0, 0, -1};
	cam->fov = 1.0;

	sphere->pos = (t_3d){0, 0, -0.67};
	sphere->diameter = 0.54;

	
	double	aspect_ratio = (double) WIDTH / (double) HEIGHT;
	
	double	viewport_height = 2.0;
	double	viewport_width = viewport_height * aspect_ratio;

	double	focal_length = 0.5;

	t_3d	origin = (t_3d){0, 0, 0};
	t_3d	horizontal = (t_3d){viewport_width, 0, 0};
	t_3d	vertical = (t_3d){0, viewport_height, 0};
	t_3d	lower_left_corner = (t_3d){-(viewport_width / 2), 
									   -(viewport_height / 2),
									   -focal_length};

	int j = HEIGHT - 1;
	while (--j >= 0)
	{
		int i = -1;
		while (++i < WIDTH)
		{
			t_d h = (t_d)i / (double) (WIDTH - 1);
			t_d v = (t_d)j / (double) (HEIGHT - 1);
			t_ray *r = mk_ray(origin,
				*sum4_3d(lower_left_corner,
						*mul(h, horizontal),
						*mul(v, vertical), 
						*mul(-1, origin)));
			put_pxl(img, i, j, color_ray(*r, sphere));
		}
	}
	return ;
}