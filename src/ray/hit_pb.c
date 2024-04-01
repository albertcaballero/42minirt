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
}
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
