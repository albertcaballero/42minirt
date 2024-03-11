/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:46:15 by jmarinel          #+#    #+#             */
/*   Updated: 2024/03/11 10:58:41 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	hit_sphere(t_ray *ray, t_forms *form, t_hit *rec)
{
	t_sp	*sp;
	t_hcalc	calc;
	t_vec	oc;

	sp = form->sp;
	oc = substract_vec(&ray->origin, &sp->pos);
	calc.a = length_squared(&ray->dir);
	calc.b = dot_scalar_product(&oc, &ray->dir);
	calc.c = length_squared(&oc) - sp->rad * sp->rad;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	if (calc.disc < 0)
		return (false);
	calc.sqrt = sqrt(calc.disc);
	calc.root = (-calc.b - calc.sqrt) / calc.a;
	if (calc.root <= rec->ray_tmin || rec->ray_tmax <= calc.root)
	{
		calc.root = (-calc.b + calc.sqrt) / calc.a;
		if (calc.root <= rec->ray_tmin || rec->ray_tmax <= calc.root)
			return (false);
	}
	rec->t = calc.root;
	rec->point = ray_at(ray, rec->t);
	rec->normal = substract_vec(&rec->point, &sp->pos);
	rec->normal = normalize_vec(&rec->normal);
	return (true);
}


t_hit	nearest_hit(t_ray *ray, t_scene *scene)
{
	t_objs	*obj;
	t_hit	rec;

	rec.ray_tmin = 0.1;
	rec.ray_tmax = INT_MAX;
	rec.t = -1.0;
	obj = scene->objs;
	while (obj)
	{
		if (obj->hit(ray, &obj->form, &rec) == true)
		{
			rec.ray_tmax = rec.t;
			rec.obj = obj;
		}
		obj = obj->next;
	}
	return (rec);
}
