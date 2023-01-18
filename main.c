/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:57:19 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/18 12:56:32 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

int	minirt(int argc, char **argv, mlx_t *mlx, mlx_image_t *g_img)
{
	t_mrt		*m;
	char	***sens;
	(void)	mlx;

	sens = lex(argc, argv);
	if (!sens)
	{
		ft_printf("Parsing failed. Did you supply a *.rt file?\n");
		return (EXIT_FAILURE);
	}
	m = parse(sens);
	if (!m)
		return (EXIT_FAILURE);
	// g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	draw_scene(g_img, m);
	// free_all(&p);
	return (0);
}

int32_t	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*g_img;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	g_img = NULL;
	if (!mlx)
		return (EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (minirt(argc, argv, mlx, g_img) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &key_hook, mlx);
	mlx_close_hook(mlx, (void (*)(void *))mlx_close_window, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}