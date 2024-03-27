/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cyl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:35:06 by jmarinel          #+#    #+#             */
/*   Updated: 2024/03/27 18:02:34 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h> 

t_vec	calculate_normal( t_cy *cyl, t_point point)
{
	t_vec	tmp;
	t_vec	tmp2;
	t_vec	normal;

	tmp = substract_vec(&cyl->pos, &point);
	tmp2 = scalar_mult_vec_ret(&cyl->dir, dot_scalar_product(&tmp, &cyl->dir));
	normal = substract_vec(&tmp2, &tmp);
	return (unitary_vector(&normal));
}

bool	calc_hit_cilinder(t_hcalc calc, t_ray *ray, t_hit *rec, t_forms obj)
{
	double	projection;
	t_vec	tmp;

	if (calc.disc < 0)
		return (false);
	calc.sqrt = sqrt(calc.disc);
	calc.root = (-calc.b - calc.sqrt) / calc.a;
	if (calc.root <= rec->ray_tmin || calc.root >= rec->ray_tmax)
	{
		calc.root = (-calc.b + calc.sqrt) / calc.a;
		if (calc.root <= rec->ray_tmin || calc.root >= rec->ray_tmax)
			return (false);
	}
	tmp = ray_at(ray, calc.root);
	tmp = substract_vec(&tmp, &obj.cy->pos);
	projection = dot_scalar_product(&obj.cy->dir, &tmp);
	if (projection < 0 || projection > obj.cy->height)
		return (false);
	rec->t = calc.root;
	rec->point = ray_at(ray, calc.root);
	rec->normal = calculate_normal(obj.cy, rec->point);
	return (true);
}

bool	hit_body_cylinder(t_ray *ray, t_forms obj, t_hit *rec)
{
	t_vec	oc;
	t_vec	tmp;
	t_vec	direction_parallel;
	t_vec	oc_parallel;
	t_hcalc	calc;

	oc = substract_vec(&ray->origin, &obj.cy->pos);
	tmp = scalar_mult_vec_ret(&obj.cy->dir, \
	dot_scalar_product(&ray->dir, &obj.cy->dir));
	direction_parallel = substract_vec(&ray->dir, &tmp);
	tmp = scalar_mult_vec_ret(&obj.cy->dir, \
	dot_scalar_product(&oc, &obj.cy->dir));
	oc_parallel = substract_vec(&oc, &tmp);
	calc.a = length_squared(&direction_parallel);
	calc.b = dot_scalar_product(&oc_parallel, &direction_parallel);
	calc.c = length_squared(&oc_parallel) - obj.cy->rad * obj.cy->rad;
	calc.disc = calc.b * calc.b - calc.a * calc.c;
	return (calc_hit_cilinder(calc, ray, rec, obj));
}

bool	hit_cyl(t_ray *ray, t_forms *obj, t_hit *rec)
{
	t_disk	disk;
	t_ray	axis;

	axis.origin = obj->cy->pos;
	axis.dir = obj->cy->dir;
	disk.pos = obj->cy->pos;
	disk.dir = obj->cy->dir;
	disk.rad = obj->cy->rad;
	obj->cy->hit[BOT] = hit_disk(ray, &disk, rec);
	if (obj->cy->hit[BOT])
		rec->ray_tmax = rec->t;
	disk.pos = ray_at(&axis, obj->cy->height);
	disk.dir = scalar_mult_vec_ret(&obj->cy->dir, -1);
	obj->cy->hit[BODY] = hit_body_cylinder(ray, *obj, rec);
	if (obj->cy->hit[BODY])
		rec->ray_tmax = rec->t;
	obj->cy->hit[TOP] = hit_disk(ray, &disk, rec);
	if (obj->cy->hit[TOP])
		rec->ray_tmax = rec->t;
	return (obj->cy->hit[BOT] || obj->cy->hit[BODY]
		|| obj->cy->hit[TOP]);
}
