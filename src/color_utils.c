/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:20:00 by alcaball          #+#    #+#             */
/*   Updated: 2024/04/01 17:20:45 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec	color_to_point(t_color col1)
{
	t_point	dcol1;

	dcol1.x = col1.r / 255.9999;
	dcol1.y = col1.g / 255.9999;
	dcol1.z = col1.b / 255.9999;
	return (dcol1);
}

t_color average_color(t_vec color)
{
	t_point	dnew;
	double	ratio;

	ratio = 1.0 / (double)SAMPLES;

	dnew.x = color.x;
	dnew.x *= ratio;
	dnew.y = color.y;
	dnew.y *= ratio;
	dnew.z = color.z;
	dnew.z *= ratio;
	return (new_color_doub(dnew.x, dnew.y, dnew.z));
}
