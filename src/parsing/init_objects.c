/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:17:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/27 18:14:03 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	init_sphere(t_forms *form, char **args)
{
	if (checkrng_dbl(args[2], -LIMIT_RAD, LIMIT_RAD) == ERROR)
		return (ERROR);
	form->sp = my_malloc(sizeof(t_sp));
	form->sp->pos = parse_vector(args[1]);
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
	form->pl->pos = parse_vector(args[1]);
	form->pl->dir = parse_vector(args[2]);
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
	if (checkrng_dbl(args[3], -LIMIT_RAD, LIMIT_RAD) == ERROR)
		return (ERROR);
	if (checkrng_dbl(args[4], -LIMIT_HEIGHT, LIMIT_HEIGHT) == ERROR)
		return (ERROR);
	form->cy = my_malloc(sizeof(t_cy));
	form->cy->pos = parse_vector(args[1]);
	form->cy->dir = parse_vector(args[2]);
	form->cy->dir = unitary_vector(&form->cy->dir);
	form->cy->rad = ft_atod(args[3]) / 2.0;
	form->cy->height = ft_atod(args[4]);
	return (OK);
}

void	init_type_obj(t_objs *obj, char **args, int type)
{
	obj->col = parse_color(args[ft_splitlen(args) - 1]);
	if (type == SP)
	{
		if (ft_splitlen(args) != 4 || init_sphere(&obj->form, args))
			error_msg("Sphere: invalid arguments", -1);
		print_objs(obj, type);
		obj->hit = hit_sphere;
	}
	else if (type == PL)
	{
		if (ft_splitlen(args) != 4 || init_plane(&obj->form, args))
			error_msg("Plane: invalid arguments", -1);
		print_objs(obj, type);
		obj->hit = hit_plane;
	}
	else if (type == CY)
	{
		if (ft_splitlen(args) != 6 || init_cyl(&obj->form, args))
			error_msg("Cylinder: invalid arguments", -1);
		print_objs(obj, type);
		obj->hit = hit_cyl;
	}
}

t_objs	*add_objects(t_objs *objs, char **args, int type)
{
	t_objs	*tmp;

	tmp = objs;
	objs = ft_listlast_obj(objs);
	if (objs == NULL)
	{
		objs = malloc(sizeof(t_objs));
		init_type_obj(objs, args, type);
		objs->next = NULL;
		return (objs);
	}
	objs->next = malloc(sizeof(t_objs));
	objs = objs->next;
	init_type_obj(objs, args, type);
	objs->next = NULL;
	objs = tmp;
	return (objs);
}
