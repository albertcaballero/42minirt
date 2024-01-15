/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:13:20 by alcaball          #+#    #+#             */
/*   Updated: 2024/01/15 13:18:23 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	parse_color(char *line)
{
	t_color	color;
	char	**spl;
	int		i;

	spl = ft_split(line, ',');
	if (ft_splitlen(spl) != 3)
		error_msg("not enough colors");
	i = 0;
	while (i < 3)
	{
		if (checkrng_int(spl[i], 0, 255) == 0)
			error_msg("color out of range");
		i++;
	}
	color.r = ft_atoi(spl[0]);
	color.g = ft_atoi(spl[1]);
	color.b = ft_atoi(spl[2]);
	color.hex = 0x0; //rgb_to_hex
	free_split(spl);
	return (color);
}

t_vec	parse_vector(char *line)
{
	t_vec	vec;
	(void) line;

	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	return (vec);
}

void	init_type(t_scene *scene, char **args, int type)
{
	if (type == AMBI)
	{
		if (ft_splitlen(args) != 3)
			error_msg("Ambient light: invalid arguments");
		checkrng_double(args[1], 0.0, 1.0);
		scene->ambient.ratio = ft_atod(args[1]);
		scene->ambient.color = parse_color(args[2]);
	}
	else if (type == CAM)
	{
		if (ft_splitlen(args) != 4)
			error_msg("Ambient light: invalid arguments");
		scene->cam.pos = parse_vector(args[1]);
		scene->cam.rot = parse_vector(args[2]);
		scene->cam.fov = checkrng_int(args[3], 1, 179);
	}
	else if (type == LIGHT)
	{
		if (ft_splitlen(args) != 4)
			error_msg("Ambient light: invalid arguments");
		scene->light.pos = parse_vector(args[1]);
		scene->light.ratio = ft_atod(args[2]);
	}
	return ;
}
