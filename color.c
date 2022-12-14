/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:49:15 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/12/14 16:06:24 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	dcolor(double r, double g, double b)
{
	return (color(r * 255, g * 255, b * 255));
}

uint32_t	colora(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	color(u_int8_t r, u_int8_t g, u_int8_t b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}
