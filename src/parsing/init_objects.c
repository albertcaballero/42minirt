/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:17:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/04/01 17:01:01 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	init_sphere(t_forms *form, char **args)
{
	if (checkrng_dbl(args[2], 0.01, LIMIT_RAD) == ERROR)
		return (ERROR);
	form->sp = my_malloc(sizeof(t_sp));
	form->sp->pos = parse_vector(args[1], POS);
	form->sp->rad = ft_atod(args[2]) / 2.0;
	return (OK);
}

int	init_plane(t_forms *form, char **args)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(args[2], ',');
	while (i < 3)
	{
		if (checkrng_dbl(split[i], -1, 1) == ERROR)
			return (ERROR);
		i++;
	}
	free_split(split);
	form->pl = my_malloc(sizeof(t_pl));
	form->pl->pos = parse_vector(args[1], POS);
	form->pl->dir = parse_vector(args[2], DIR);
	return (OK);
}

int	init_cyl(t_forms *form, char **args)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(args[2], ',');
	while (i < 3)
	{
		if (checkrng_dbl(split[i], -1, 1) == ERROR)
			return (ERROR);
		i++;
	}
	free_split(split);
	if (checkrng_dbl(args[3], 0.01, LIMIT_RAD) == ERROR)
		return (ERROR);
	if (checkrng_dbl(args[4], 0.01, LIMIT_HEIGHT) == ERROR)
		return (ERROR);
	form->cy = my_malloc(sizeof(t_cy));
	form->cy->pos = parse_vector(args[1], POS);
	form->cy->dir = parse_vector(args[2], DIR);
	form->cy->dir = unitary_vector(&form->cy->dir);
	form->cy->rad = ft_atod(args[3]) / 2.0;
	form->cy->height = ft_atod(args[4]);
	return (OK);
}

int	init_pb(t_forms *form, char **args)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(args[2], ',');
	while (i < 3)
	{
		if (checkrng_dbl(split[i], -1, 1) == ERROR)
			return (ERROR);
		i++;
	}
	free_split(split);
	if (checkrng_dbl(args[3], 0.01, LIMIT_RAD) == ERROR)
		return (ERROR);
	if (checkrng_dbl(args[4], 0.01, LIMIT_HEIGHT) == ERROR)
		return (ERROR);
	form->pb = my_malloc(sizeof(t_pb));
	form->pb->pos = parse_vector(args[1], POS);
	form->pb->dir = parse_vector(args[2], DIR);
	//form->pb->dir = unitary_vector(&form->pb->dir);
	form->pb->rad = ft_atod(args[3]) / 2.0;
	form->pb->height = ft_atod(args[4]);
	return (OK);
}

void	init_type_obj(t_objs *obj, char **args, int type)
{
	obj->col = parse_color(args[ft_splitlen(args) - 1]);
	if (type == SP)
	{
		if (ft_splitlen(args) != 4 || init_sphere(&obj->form, args))
			error_msg("Sphere: invalid arguments", -1, NULL);
		obj->hit = hit_sphere;
	}
	else if (type == PL)
	{
		if (ft_splitlen(args) != 4 || init_plane(&obj->form, args))
			error_msg("Plane: invalid arguments", -1, NULL);
		obj->hit = hit_plane;
	}
	else if (type == CY)
	{
		if (ft_splitlen(args) != 6 || init_cyl(&obj->form, args))
			error_msg("Cylinder: invalid arguments", -1, NULL);
		obj->hit = hit_cyl;
	}
	else if (type == PB)
	{
		if (ft_splitlen(args) != 6 || init_pb(&obj->form, args))
			error_msg("Paraboloid: invalid arguments", -1, NULL);
		obj->hit = hit_pb;
	}
}
