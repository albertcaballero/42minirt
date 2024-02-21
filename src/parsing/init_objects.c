/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:17:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/21 17:53:04 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

int	init_sphere(t_forms form, char **args)
{
	if (checkrng_dbl(args[2], -LIMIT_DIAM, LIMIT_DIAM) == ERROR)
		return (ERROR);
	form.sp = my_malloc(sizeof(t_sp));
	form.sp->diam = ft_atod(args[2]);
	form.sp->pos = parse_vector(args[1]);
	form.sp->col = parse_color(args[3]);
	return (OK);
}

int	init_plane(t_forms form, char **args)
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
	form.pl = my_malloc(sizeof(t_pl));
	form.pl->pos = parse_vector(args[1]);
	form.pl->dir = parse_vector(args[2]);
	form.pl->col = parse_color(args[3]);
	return (OK);
}

int	init_cyl(t_forms form, char **args)
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
	if (checkrng_dbl(args[3], -LIMIT_DIAM, LIMIT_DIAM) == ERROR)
		return (ERROR);
	if (checkrng_dbl(args[4], -LIMIT_HEIGHT, LIMIT_HEIGHT) == ERROR)
		return (ERROR);
	form.cy = my_malloc(sizeof(t_cy));
	form.cy->pos = parse_vector(args[1]);
	form.cy->dir = parse_vector(args[2]);
	form.cy->diam = ft_atod(args[3]);
	form.cy->height = ft_atod(args[4]);
	form.cy->col = parse_color(args[5]);
	return (OK);
}

void	init_type_obj(t_objs *obj, char **args, int type)
{
	if (type == SP)
	{
		if (ft_splitlen(args) != 4 || init_sphere(obj->form, args))
			error_msg("Sphere: invalid arguments");
	}
	else if (type == PL)
	{
		if (ft_splitlen(args) != 4 || init_plane(obj->form, args))
			error_msg("Plane: invalid arguments");
	}
	else if (type == CY)
	{
		if (ft_splitlen(args) != 6 || init_cyl(obj->form, args))
			error_msg("Cylinder: invalid arguments");
	}
}
