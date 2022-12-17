/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:50:29 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/17 12:29:33 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# include <math.h>
# include <fcntl.h> 
# include <stdio.h>
# include <stdbool.h>

# define WIDTH 400
# define HEIGHT 225

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
double	len_squared(t_3d v);
double	len(t_3d v);
t_3d	*mk_unit(t_3d v);
void	print3d(char *s, t_3d v);

typedef struct s_ray
{
	t_3d	pos;
	t_3d	dir;

}	t_ray;

t_3d	*at(t_ray ray, double t);
t_ray	*mk_ray(t_3d pos, t_3d dir);
void	del_ray(t_ray *r);
int		color_ray(t_ray r);
void	printray(char *s, t_ray v);

typedef struct s_color
{
	u_int8_t r;
	u_int8_t g;
	u_int8_t b;

}	t_clr;

//color.c
int			color(t_clr s, t_clr e, double percent);
uint32_t	dcolor(double r, double g, double b);
uint32_t	colora(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);
uint32_t	rgb(u_int8_t r, u_int8_t g, u_int8_t b);
void		printclr(t_clr clr);

typedef	struct s_alight
{
	t_d		range;
	t_clr	color;
} t_ambient;

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
	t_3d	pos;
	t_d		diameter;
	t_clr	color;
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
	t_ambient	*amb;
	t_light		*l;
	t_cam		*cam;
	t_sphere	*sp;
	t_plane		*pl;
	t_cyl		*cyl;	
}	t_mrt;

//minirt.c
char	***lex(int argc,char **argv);
t_mrt	*parse(char ***sens);
void	raytrace(mlx_image_t *img, t_mrt *p);

// bool		hit_sphere(t_3d center, double radius, t_ray r, double t_min, double t_max, t_hrecord *rec);
uint32_t	cons_sphere_clr(t_3d unit);

//utils.c
int		s_isneq(char *s1, char *s2, int n);
int		s_iseq(char *s1, char *s2);
void	ft_free(void *ptr);
void	free_all(t_mrt *m);
int		strslen(char **strs);
int		free_strs(char **sp);
void	printns(char **slist);
void	prints(char **slist);
void	printsens(char ***sentence_list);

#endif