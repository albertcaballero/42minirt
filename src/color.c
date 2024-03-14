/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:05:07 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/14 12:17:29 by alcaball         ###   ########.fr       */
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

//ratio is for color1 (e.g. ratio 0.7 is 70% color1, 30% color2)
t_color	mix_colors(t_color col1, t_color col2, double ratio)
{
	t_color	new;
	double	col1r = col1.r/255.99;
	double	col1g = col1.g/255.99;
	double	col1b = col1.b/255.99;
	double	col2r = col2.r/255.99;
	double	col2g = col2.g/255.99;
	double	col2b = col2.b/255.99;

	new = new_color_doub(col1r * col2r * ratio, col1g * col2g * ratio, col1b * col2b * ratio);
	/* new.r = ratio * col1.r + (1 - ratio) * col2.r;
	new.g = ratio * col1.g + (1 - ratio) * col2.g;
	new.b = ratio * col1.b + (1 - ratio) * col2.b;
	new.hex = (new.r << 16) + (new.g << 8) + new.b; */
	return (new);
}
