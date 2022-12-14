/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:59:43 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/14 18:14:14 by bhagenlo         ###   ########.fr       */
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

void	raytrace(mlx_image_t *img, t_parse *p)
{

	(void)p;
	double	aspect_ratio = WIDTH / HEIGHT;
	
	double	viewport_height = 2.0;
	double	viewport_width = viewport_height * aspect_ratio;

	double	focal_length = 1.0;

	t_3d	origin = (t_3d){0, 0, 0};
	t_3d	vw = (t_3d){viewport_width, 0, 0};
	t_3d	vh = (t_3d){0, viewport_height, 0};
	t_3d	lower_left_corner = (t_3d){-(viewport_width / 2), 
									   -(viewport_height / 2),
									   -focal_length};

	int i = -1;
	while (++i < WIDTH)
	{
		int j = -1;
		while (++j < HEIGHT)
		{
			t_d h = (t_d)i / (WIDTH);
			t_d v = (t_d)j / (HEIGHT);
			t_ray *r = mk_ray(origin,
				*sum4_3d(lower_left_corner,
						*mul(h, vw),
						*mul(v, vh), 
						*mul(-1, origin)));
			put_pxl(img, i, j, color_ray(*r));
		}
	}
	return ;
}