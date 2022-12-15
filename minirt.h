/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:50:29 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/14 16:17:41 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# include <math.h>
# include <fcntl.h> 
# include <stdio.h>

# define WIDTH 1280
# define HEIGHT 720

typedef double t_d;

typedef struct s_parse
{
} t_parse;

typedef struct s_3d_vector
{
	double x;
	double y;
	double z;

}	t_3d;

t_3d	*mk_3d(double x, double y, double z);
void	del_3d(t_3d *v);
t_3d	*sum_3d(t_3d v, t_3d w);
t_3d	*scalar(double k, t_3d v);
double	dot(t_3d v, t_3d w);
t_3d	*cross(t_3d v, t_3d w);
double	len(t_3d v);
t_3d	*mk_unit(t_3d v);

typedef struct s_ray
{
	t_3d	pos;
	t_3d	dir;

}	t_ray;

t_ray	*mk_ray(t_3d pos, t_3d dir);
void	del_ray(t_ray *r);
int		color_ray(t_ray r);

typedef struct s_color
{
	u_int8_t r;
	u_int8_t g;
	u_int8_t b;

}	t_clr;

uint32_t	dcolor(double r, double g, double b);
uint32_t	colora(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);
uint32_t	color(u_int8_t r, u_int8_t g, u_int8_t b);

typedef	struct s_alight
{
	t_d		range;
	t_clr	color;
} t_alight;

typedef struct s_light
{
	t_3d	pos;
	t_d		range;
	t_clr	color;
} t_light;

typedef struct	s_cam
{
	t_3d	pos;
	t_3d	dir;
	int		fov;
} t_cam;

typedef struct s_sphere
{
	t_3d	 	pos;
	t_d			diameter;
	t_clr		color;
} t_sphere;

typedef struct s_plane
{
	t_3d	pos;
	t_3d	dir;
	t_clr	color;
} t_plane;

typedef struct s_cyl
{
	t_3d	pos;
	t_3d	dir;
	t_d		diameter;
	t_d		height;
	t_clr	color;
} t_cyl;

typedef struct s_minirt
{
	t_alight	*alight;
	t_light		*light;
	t_cam		*cam;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cyl		*cylinders;	
}	t_mrt;

t_mrt	*parse_file(int argc, char **argv);

void	raytrace(mlx_image_t *img, t_mrt *p);


//utils.c
void	ft_free(void *ptr);
void	free_all(t_mrt *m);

#endif