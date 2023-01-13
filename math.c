/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:14:17 by bhagenlo          #+#    #+#             */
/*   Updated: 2023/01/13 12:24:26 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	d_max(double a, double b)
{
	if (a > b)
		return a;
	return (b);
}

double	degrees_to_radians(double deg)
{
	double	res;

	res = deg * (M_PI / 180.0);
	return (res);
}