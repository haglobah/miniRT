/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:50:29 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/27 16:42:19 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

# include "parser.h"
# include "vector_math.h"
# include "objects.h"

# define WIDTH 1200
# define HEIGHT 675
# define EPSILON 0.001

typedef double t_d;

typedef struct s_options
{
	mlx_t		*mlx;
	mlx_image_t *g_img;
	t_mrt		*m;
	t_camera	*camera;
}	t_options;

//ray.c
t_3d		at(t_ray ray, double t);
t_ray		mk_ray(t_3d pos, t_3d dir);
uint32_t	compute_hitpoint_clr(t_mrt *m, t_hit *h);

//color.c
int			color(t_clr s, t_clr e, double percent);
uint32_t	dcolor(double r, double g, double b);
uint32_t	colora(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);
uint32_t	rgb(u_int8_t r, u_int8_t g, u_int8_t b);
void		print_clr(t_clr clr);
void		del_clr(t_clr *v);
t_clr		sum_clr(t_clr v, t_clr w);
t_clr		mul_clr(double k, t_clr v);

//data.c 
t_ambient	*mk_amb(t_d ratio, t_clr *clr);
t_cam		*mk_cam(t_3d *pos, t_3d *dir, t_d fov);
t_light		*mk_l(t_3d *pos, t_clr *clr, t_d brightness);
void		fill_sp(t_3d *pos, t_d diameter, t_clr *clr, t_sphere *sphere);
void		fill_pl(t_3d *pos, t_3d *normal, t_clr *clr, t_plane *plane);
void		fill_cyl(t_tmp_cyl tmp_cyl, t_cyl *cyl);

//memory.c
void		add_to_list(t_lst **lst, t_3d *v, t_clr *clr, t_ray *ray);
void		print_list(t_lst *list);
t_lst		*mk_node(t_3d *v, t_clr *clr, t_ray *ray);
void		free_from_list(t_lst *lst);
void		free_mrt(t_mrt *m);
void		free_opt(t_options *o);

//scene.c 
void		fill_window(t_window *w, double width, double height);
t_camera	*mk_camera(t_mrt *m, t_window *w, t_3d *vup);

//minirt.c
void		trace_ray(t_mrt *m, t_ray r, t_hit *h);
char		***lex(int argc,char **argv);
void		draw_scene(t_options *o, mlx_t *mlx, mlx_image_t *img, t_mrt *p);

// bool		hit_sphere(t_3d center, double radius, t_ray r, double t_min, double t_max, t_hrecord *rec);
uint32_t	cons_sphere_clr(t_clr color, double coeff);

//hit.c
double		hitpoint_sphere(t_3d center, double radius, t_ray r, double *root);
void		update_hit(t_hit *h, t_3d pos, double t, t_3d *normal, bool from_plane, t_clr clr);
bool		did_hit(t_hit *h);
void		hit_sphere(t_sphere *sp, t_ray r, t_hit *h);
void		hit_plane(t_plane *pl, t_ray r, t_hit *h);
void		hit_cylinder(t_cyl *cyl, t_ray r, t_hit *h);

// math.c
double		d_max(double a, double b);
double		degrees_to_radians(double deg);

//print.c
void		print_mrt(t_mrt *m);
void		print_camera(t_camera *c);
void		print_ray(char *s, t_ray v);
void		print_hit(t_hit h);
void		print_3d(char *s, t_3d v);

//utils.c
int			s_isneq(char *s1, char *s2, int n);
int			s_iseq(char *s1, char *s2);
void		ft_free(void *ptr);
void		free_all(t_mrt *m);
int			strslen(char **strs);
int			free_strs(char **sp);
void		printnstrs(char **slist);
void		printstrs(char **slist);
void		printstrs_n(char **slist);
void		printsens(char ***sentence_list);

// parser.c
t_mrt		*parse(char ***sens);

#endif