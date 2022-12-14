/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:50:29 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/14 17:23:58 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# include <math.h>
# include <stdio.h>

# define WIDTH 1600
# define HEIGHT 900

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
t_3d	*sum4_3d(t_3d v, t_3d w, t_3d u, t_3d z);
t_3d	*mul(double k, t_3d v);
double	dot(t_3d v, t_3d w);
t_3d	*cross(t_3d v, t_3d w);
double	len(t_3d v);
t_3d	*mk_unit(t_3d v);
void	print3d(char *s, t_3d v);

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

int			color(t_clr s, t_clr e, double percent);
uint32_t	dcolor(double r, double g, double b);
uint32_t	colora(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);
uint32_t	rgb(u_int8_t r, u_int8_t g, u_int8_t b);

typedef struct s_minirt
{
	
}	t_mrt;

void	raytrace(mlx_image_t *img, t_parse *p);


//utils.c
void	ft_free(void *ptr);
void	free_all(t_mrt *m);

#endif