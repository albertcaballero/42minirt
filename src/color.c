/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:05:07 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/27 13:18:32 by alcaball         ###   ########.fr       */
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
	color.b = b;
	color.hex = (color.r << 16) + (color.g << 8) + color.b;
	return (color);
}

t_color	new_color_doub(double r, double g, double b)
{
	t_color	color;

	color.r = (unsigned int)(r * 255.999);
	color.g = (unsigned int)(g * 255.999);
	color.b = (unsigned int)(b * 255.999);
	color.hex = (color.r << 16) + (color.g << 8) + color.b;
	return (color);
}

t_color	mix_colors(t_color col1, t_color col2, double ratio)
{
	t_color	new;
	t_point	dcol1;
	t_point	dcol2;

	dcol1.x = col1.r / 255.9999;
	dcol1.y = col1.g / 255.9999;
	dcol1.z = col1.b / 255.9999;
	dcol2.x = col2.r / 255.9999;
	dcol2.y = col2.g / 255.9999;
	dcol2.z = col2.b / 255.9999;

	new = new_color_doub(dcol1.x * dcol2.x * ratio, \
		dcol1.y * dcol2.y * ratio, dcol1.z * dcol2.z * ratio);
	return (new);
}

t_color	add_colors(t_color col1, t_color col2)
{
	t_color			new;

	new.r = ft_clamp(col1.r + col2.r, 255, MAX);
	new.g = ft_clamp(col1.g + col2.g, 255, MAX);
	new.b = ft_clamp(col1.b + col2.b, 255, MAX);
	new.hex = (new.r << 16) + (new.g << 8) + new.b;
	return (new);
}
