/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_pb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:10:34 by jmarinel          #+#    #+#             */
/*   Updated: 2024/04/03 17:20:12 by jmarinel         ###   ########.fr       */
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

bool	intersect_ray_paraboloid(t_forms obj, t_ray *ray, t_hit *rec)
{
	t_hcalc		calc;
	t_vec		oc;
	double		denom;

	denom = dot_scalar_product(&obj.pb->dir, &ray->dir);
	if (fabs(denom) < 0)
		return (false);
	oc = substract_vec(&ray->origin, &obj.pb->pos);
	calc.a = dot_scalar_product(&ray->dir, &ray->dir) - pow(dot_scalar_product(&ray->dir, &obj.pb->dir), 2);
	calc.b = 2 * (dot_scalar_product(&oc, &ray->dir) - dot_scalar_product(&ray->dir, &obj.pb->dir)
			* (dot_scalar_product(&oc, &obj.pb->dir) + 2 * obj.pb->rad));
	calc.c = dot_scalar_product(&oc, &oc) - dot_scalar_product(&oc, &obj.pb->dir) \
		* (dot_scalar_product(&oc, &obj.pb->dir) + 4 * obj.pb->rad);
	calc.disc = calc.b * calc.b - 4 * calc.a * calc.c;
	if (calc.disc < 0)
		return (false);
	calc.sqrt = sqrt(calc.disc);
	calc.root = (-calc.b - calc.sqrt) / (2 * calc.a);
	if (calc.root <= rec->ray_tmin || calc.root >= rec->ray_tmax)
	{
		calc.root = (-calc.b + calc.sqrt) / (2 * calc.a);
		if (calc.root <= rec->ray_tmin || calc.root >= rec->ray_tmax)
			return (false);
	}
	rec->t = calc.root;
	rec->point = ray_at(ray, rec->t);
	rec->normal = calculate_normal_pb(obj.pb, rec->point);
	return (true);
}

bool	hit_pb(t_ray *ray, t_forms *obj, t_hit *rec)
{
	return (intersect_ray_paraboloid(*obj, ray, rec));
}
