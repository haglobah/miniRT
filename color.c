/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:49:15 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/02/01 09:34:54 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_clr(t_clr clr)
{
	printf("Color: ");
	printf("r: %i, ", clr.r);
	printf("g: %i, ", clr.g);
	printf("b: %i", clr.b);
	printf("\n");
}

uint32_t	rgb(u_int8_t r, u_int8_t g, u_int8_t b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

t_clr	sum_clr(t_clr v, t_clr w)
{
	t_clr		new;
	uint16_t	r;
	uint16_t	g;
	uint16_t	b;

	r = (uint16_t)v.r + (uint16_t)w.r;
	if (r > 255)
		r = 255;
	g = (uint16_t)v.g + (uint16_t)w.g;
	if (g > 255)
		g = 255;
	b = (uint16_t)v.b + (uint16_t)w.b;
	if (b > 255)
		b = 255;
	new = (t_clr){r, g, b, 0};
	return (new);
}

t_clr	mul_clr(double k, t_clr v)
{
	t_clr	new;

	new = (t_clr){k * v.r, k * v.g, k * v.b, 0};
	return (new);
}
