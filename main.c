/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:57:19 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/27 14:08:09 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_hook(void *param)
{
	t_options	*o;

	o = (t_options *)param;
	if (mlx_is_key_down(o->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(o->mlx);
	else if (mlx_is_key_down(o->mlx, MLX_KEY_W))
	{
		*o->camera->pos = sub_3d(*o->camera->pos, (t_3d){0.05, 0, 0});
		draw_scene(o, o->mlx, o->g_img, o->m);
	}
	else if (mlx_is_key_down(o->mlx, MLX_KEY_S))
	{
		*o->camera->pos = sum_3d(*o->camera->pos, (t_3d){0.05, 0, 0});
		draw_scene(o, o->mlx, o->g_img, o->m);
	}
	else if (mlx_is_key_down(o->mlx, MLX_KEY_D))
	{
		*o->camera->pos = sub_3d(*o->camera->pos, (t_3d){0, 0.05, 0});
		draw_scene(o, o->mlx, o->g_img, o->m);
	}
	else if (mlx_is_key_down(o->mlx, MLX_KEY_A))
	{
		*o->camera->pos = sum_3d(*o->camera->pos, (t_3d){0, 0.05, 0});
		draw_scene(o, o->mlx, o->g_img, o->m);
	}
	else if (mlx_is_key_down(o->mlx, MLX_KEY_LEFT_SHIFT))
	{
		*o->camera->pos = sub_3d(*o->camera->pos, (t_3d){0, 0, 0.05});
		draw_scene(o, o->mlx, o->g_img, o->m);
	}
	else if (mlx_is_key_down(o->mlx, MLX_KEY_SPACE))
	{
		*o->camera->pos = sum_3d(*o->camera->pos, (t_3d){0, 0, 0.05});
		draw_scene(o, o->mlx, o->g_img, o->m);
	}
	else if (mlx_is_key_down(o->mlx, MLX_KEY_H))
	{
		*o->camera->dir = sub_3d(*o->m->l->pos, (t_3d){0, 0, 0.05});
		draw_scene(o, o->mlx, o->g_img, o->m);
	}
	else if (mlx_is_key_down(o->mlx, MLX_KEY_J))
	{
		*o->m->l->pos = sum_3d(*o->m->l->pos, (t_3d){0, 0, 0.05});
		draw_scene(o, o->mlx, o->g_img, o->m);
	}
	else if (mlx_is_key_down(o->mlx, MLX_KEY_LEFT))
	{
		*o->camera->dir = sub_3d(*o->camera->dir, (t_3d){0.05, 0., 0});
		draw_scene(o, o->mlx, o->g_img, o->m);
	}
	else if (mlx_is_key_down(o->mlx, MLX_KEY_RIGHT))
	{
		*o->camera->dir = sum_3d(*o->camera->dir, (t_3d){0.05, 0, 0.0});
		draw_scene(o, o->mlx, o->g_img, o->m);
	}
	// print_3d("CAMER POS: ", *o->camera->pos);
}

int	minirt(t_options *o, int argc, char **argv)
{
	char	***sens;

	sens = lex(argc, argv);
	if (!sens)
	{
		ft_printf("Error\nParsing failed. Did you supply a *.rt file?\n");
		return (EXIT_FAILURE);
	}
	o->m = parse(sens);
	// print_mrt(o->m);
	if (!o->m)
		return (EXIT_FAILURE);
	draw_scene(o, o->mlx, o->g_img, o->m);
	return (0);
}

int32_t	main(int argc, char *argv[])
{
	t_options	*o;

	o = ft_calloc(1, sizeof(t_options));
	o->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	o->g_img = NULL;
	if (!o->mlx)
		return (EXIT_FAILURE);
	o->g_img = mlx_new_image(o->mlx, WIDTH, HEIGHT);
	if (minirt(o, argc, argv) == EXIT_FAILURE)
	{
		mlx_delete_image(o->mlx, o->g_img);
		mlx_terminate(o->mlx);
		return (EXIT_FAILURE);
	}
	mlx_image_to_window(o->mlx, o->g_img, 0, 0);
	mlx_loop_hook(o->mlx, &key_hook, o);
	mlx_close_hook(o->mlx, (void (*)(void *))mlx_close_window, o->mlx);
	mlx_loop(o->mlx);
	mlx_delete_image(o->mlx, o->g_img);
	mlx_terminate(o->mlx);
	free_opt(o);
	return (EXIT_SUCCESS);
}