/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:17:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/27 17:29:58 by jmarinel         ###   ########.fr       */
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
	/* void	inti_func_cylinder(t_world *cy)
{
	t_ray	ray;

	cy->type.cy->dir = unit_vector(&cy->type.cy->dir);
	ray.dir = cy->type.cy->dir;
	ray.orig = cy->type.cy->center;
	cy->type.cy->center = ray_at(&ray, -(cy->type.cy->height / 2));
	cy->hit = hit_cylinder;
	cy->get_position_pointer = get_position_cylinder;
	cy->get_color = get_color_cylinder;
}*/
	return (OK);
}

void	init_type_obj(t_objs *obj, char **args, int type)
{
	//fprintf(stderr, "split len is: -- %i -- \n", ft_splitlen(args) - 1);
	obj->col = parse_color(args[ft_splitlen(args) - 1]);
	if (type == SP)
	{
		if (ft_splitlen(args) != 4 || init_sphere(&obj->form, args))
			error_msg("Sphere: invalid arguments");
		print_objs(obj, type);
		obj->hit = hit_sphere;
	}
	else if (type == PL)
	{
		if (ft_splitlen(args) != 4 || init_plane(&obj->form, args))
			error_msg("Plane: invalid arguments");
		print_objs(obj, type);
		obj->hit = hit_plane;
	}
	else if (type == CY)
	{
		if (ft_splitlen(args) != 6 || init_cyl(&obj->form, args))
			error_msg("Cylinder: invalid arguments");
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

/*DELTE
color ray_color(const ray& r) {
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}
*/