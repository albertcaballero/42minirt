/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_pb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:10:34 by jmarinel          #+#    #+#             */
/*   Updated: 2024/04/01 17:52:20 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec	calculate_normal_pb( t_pb *pb, t_point point)
{
	t_vec	tmp;
	t_vec	tmp2;
	t_vec	normal;

	tmp = substract_vec(&pb->pos, &point);
	tmp2 = scalar_mult_vec_ret(&pb->dir, dot_scalar_product(&tmp, &pb->dir));
	normal = substract_vec(&tmp2, &tmp);
	return (unitary_vector(&normal));
}

t_decisions	solving_quadratic_equation(t_hcalc calc)
{
	t_decisions	decision;
	double		discriminant;

	discriminant = calc.b * calc.b - 4 * calc.a * calc.c;
	if (discriminant < 0)
	{
		decision.t1 = INT_MAX;
		decision.t2 = INT_MAX;
		return (decision);
	}
	decision.t1 = (-calc.b + sqrt(discriminant)) / (2 * calc.a);
	decision.t2 = (-calc.b - sqrt(discriminant)) / (2 * calc.a);
	return (decision);
}

t_decisions	intersect_ray_paraboloid(t_forms obj,
										t_ray *ray)
{
	t_decisions	decision;
	t_hcalc		calc;
	t_vec		oc;

	oc = substract_vec(&ray->origin, &obj.pb->pos);
	/* - - - */
	calc.a = dot_scalar_product(&ray->dir, &ray->dir) - pow(dot_scalar_product(&ray->dir, &obj.pb->dir), 2);
	calc.b = 2 * (dot_scalar_product(&oc, &ray->dir) - dot_scalar_product(&ray->dir, &obj.pb->dir)
			* (dot_scalar_product(&oc, &obj.pb->dir) + 2
				* obj.pb->rad));
	calc.c = dot_scalar_product(&oc, &oc)
		- dot_scalar_product(&oc, &obj.pb->dir)
		* (dot_scalar_product(&oc, &obj.pb->dir) + 4
			* obj.pb->rad);
	decision = solving_quadratic_equation(calc);
	return (decision);
}

bool	hit_pb(t_ray *ray, t_forms *obj, t_hit *rec)
{
	t_decisions	decision;

	decision = intersect_ray_paraboloid(*obj, ray);
	if (decision.t1 >= 0 && decision.t2 >= 0)
	{
		if (decision.t1 < decision.t2)
			rec->t = decision.t1;
		else
			rec->t = decision.t2;
		rec->point = ray_at(ray, rec->t);
		rec->normal = calculate_normal_pb(obj->pb, rec->point);
		return (true);
	}
	else if (decision.t1 >= 0)
	{
		rec->t = decision.t1;
		rec->point = ray_at(ray, rec->t);
		rec->normal = calculate_normal_pb(obj->pb, rec->point);
		return (true);
	}
	else if (decision.t2 >= 0)
	{
		rec->t = decision.t2;
		rec->point = ray_at(ray, rec->t);
		rec->normal = calculate_normal_pb(obj->pb, rec->point);
		return (true);
	}
	return (false);
}
/* 
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
	rec->normal = calculate_normal_pb(obj.pb, rec->point);
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
} */

/* 
bool	hit_sphere(t_ray *ray, t_forms *form, t_hit *rec)
{
	t_sp	*sp;
	t_hcalc	calc;
	t_vec	oc;
	double	recip;

	sp = form->sp;
	oc = substract_vec(&ray->origin, &sp->pos);
	calc.a = length_squared(&ray->dir);
	calc.b = dot_scalar_product(&oc, &ray->dir);
	calc.c = length_squared(&oc) - 1;
	calc.disc = (calc.b * calc.b) - (calc.a * calc.c);
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
} */
//color, coord
//clipY = vec3 
/* 
bool	hit_pb(t_ray *ray, t_forms *obj, t_hit *rec)
{
	//ro = ray->origin
	//rd = ray->dir
	t_vec	abc;
	t_vec	shape;
	t_vec	clip_y;
	double	clip_z;

	shape = new_vec(1.0, 1.0, 1.0);
	clip_y = new_vec(-2.0, 2.0, 0.0);
	clip_z = 2.0;
	



 */
