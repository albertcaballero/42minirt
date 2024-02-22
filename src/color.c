/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:05:07 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/22 10:56:03 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && y < WIN_H && x < WIN_W)
	{
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

t_color	new_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b	= b;
	color.hex = (color.r << 16) + (color.g << 8) + color.b;
	return (color);
}

t_color	new_color_doub(double r, double g, double b)
{
	t_color	color;

	color.r = (unsigned int)(r * 255.999);
	color.g = (unsigned int)(g * 255.999);
	color.b	= (unsigned int)(b * 255.999);
	color.hex = (color.r << 16) + (color.g << 8) + color.b;
	return (color);
}
