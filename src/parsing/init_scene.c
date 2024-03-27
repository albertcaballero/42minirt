/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:13:20 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/27 12:15:41 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_scene(t_scene *scene)
{
	dprintf(2, "========= AMBIENT LIGHT =======\n");
	dprintf(2, "ratio: %f\ncolor: %i,%i,%i\n", scene->ambient.ratio, \
		scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);
	dprintf(2, "========= CAMERA ==============\n");
	dprintf(2, "fov: %i\npos: %f,%f,%f\nrot:%f,%f,%f\n", scene->cam.fov, \
		scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z, \
		scene->cam.dir.x, scene->cam.dir.y, scene->cam.dir.z);
	dprintf(2, "========= LIGHT ===============\n");
	dprintf(2, "ratio: %f\npos: %f,%f,%f\n", scene->light->ratio, \
		scene->light->pos.x, scene->light->pos.y, scene->light->pos.z);

}

void	print_objs(t_objs *objs, int type)
{
	if (type == SP )
	{
		dprintf(2, "========= SPHERE ===============\n");
		dprintf(2, "rad: %f\npos: %f,%f,%f\ncol: %i,%i,%i\n", objs->form.sp->rad, \
			objs->form.sp->pos.x, objs->form.sp->pos.y, objs->form.sp->pos.z, \
			objs->col.r, objs->col.g, objs->col.b);
	}
	else if (type == PL )
	{
		dprintf(2, "========= PLANE ===============\n");
		dprintf(2, "pos: %f,%f,%f\ncol: %i,%i,%i\n", \
			objs->form.pl->pos.x, objs->form.pl->pos.y, objs->form.pl->pos.z, \
			objs->col.r, objs->col.g, objs->col.b);
	}
	else if (type == CY )
	{
		dprintf(2, "========= CYLINDER ===============\n");
		dprintf(2, "rad: %f\npos: %f,%f,%f\ncol: %i,%i,%i\n", objs->form.sp->rad, \
			objs->form.cy->pos.x, objs->form.cy->pos.y, objs->form.cy->pos.z, \
			objs->col.r, objs->col.g, objs->col.b);
	}
}


t_color	parse_color(char *line)
{
	t_color	color;
	char	**spl;
	int		i;

	spl = ft_split(line, ',');
	if (ft_splitlen(spl) != 3)
	{
		free_split(spl);
		error_msg("Wrong color count [3]");
	}
	i = 0;
	while (i < 3)
	{
		if (checkrng_int(spl[i], 0, 255) == ERROR)
			error_msg("Color out of range [0, 255]");
		i++;
	}
	color.r = ft_atoi(spl[0]);
	color.g = ft_atoi(spl[1]);
	color.b = ft_atoi(spl[2]);
	color.hex = (color.r << 16) + (color.g << 8) + color.b;
	free_split(spl);
	return (color);
}

t_vec	parse_vector(char *line)
{
	t_vec	vec;
	char	**spl;

	spl = ft_split(line, ',');
	if (ft_splitlen(spl) != 3)
	{
		free_split(spl);
		error_msg("Wrong vector count [3]");
	}
	vec.x = ft_atod(spl[0]);
	vec.y = ft_atod(spl[1]);
	vec.z = ft_atod(spl[2]);
	free_split(spl);
	return (vec);
}

void	init_type(t_scene *scene, char **args, int type)
{
	if (type == AMBI)
	{
		if (ft_splitlen(args) != 3)
			error_msg("Ambient light: invalid argument count [2]");
		if (checkrng_dbl(args[1], 0.0, 1.0))
			error_msg("Ambient light: ratio out of range [0.0, 1.0]");
		scene->ambient.ratio = ft_atod(args[1]);
		scene->ambient.color = parse_color(args[2]);
	}
	else if (type == CAM)
	{
		if (ft_splitlen(args) != 4)
			error_msg("Camera: invalid argument count [3]");
		if (checkrng_int(args[3], 1, 179))
			error_msg("Camera: FoV out of range [1, 179]");
		scene->cam.pos = parse_vector(args[1]);
		scene->cam.dir = parse_vector(args[2]);
		scene->cam.fov = ft_atoi(args[3]);
		calculate_viewport(&scene->cam);
	}
	else if (type == LIGHT)
		init_lights(scene, args);
	else
		scene->objs = add_objects(scene->objs, args, type);
}
