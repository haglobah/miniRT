/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:49:15 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/15 14:24:04 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static int	red(int clr)
// {
// 	return ((clr >> 24) & 0xFF);
// }

// static int	green(int clr)
// {
// 	return ((clr >> 16) & 0xFF);
// }

// static int	blue(int clr)
// {
// 	return ((clr >> 8) & 0xFF);
// }

void	printclr(t_clr clr)
{
	printf("r: %i,", clr.r);
	printf("g: %i,", clr.g);
	printf("b: %i", clr.b);
	printf("\n");
}

u_int32_t	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * end + percentage * start));
}

int	color(t_clr s, t_clr e, double percent)
{
	int	r;
	int	g;
	int	b;

	r = get_light(s.r, e.r, percent);
	g = get_light(s.g, e.g, percent);
	b = get_light(s.b, s.b, percent);
	return ((r << 24) | (g << 16) | (b << 8) | (255));
}

uint32_t	dcolor(double r, double g, double b)
{
	return (rgb((u_int8_t)(r * 255), 
				  (u_int8_t)(g * 255),
				  (u_int8_t)(b * 255)));
}

uint32_t	rgba(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

uint32_t	rgb(u_int8_t r, u_int8_t g, u_int8_t b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}
