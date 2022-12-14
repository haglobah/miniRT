/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:57:19 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/14 16:17:52 by bhagenlo         ###   ########.fr       */
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
	t_parse		*p;

	p = NULL;
	// p = parse_file(argc, argv);
	// if (p == NULL)
	// {
	// 	ft_printf("Parsing failed. Did you supply a *.rt file?\n");
	// 	return (EXIT_FAILURE);
	// }
	(void)argc;
	(void)argv;
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	raytrace(g_img, p);
	// free_all(&p);
	return (0);
}

int32_t	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*g_img;

	mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	g_img = NULL;
	if (!mlx)
		return (EXIT_FAILURE);
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