/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:46:15 by jmarinel          #+#    #+#             */
/*   Updated: 2024/03/14 13:04:12 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	hit_disk(t_ray *ray, t_disk *disk, t_hit *rec)
{
	double	denom;
	t_vec	oc;
	double	t;
	t_vec	p;
	t_vec	to_center;

	denom = dot_scalar_product(&disk->dir, &ray->dir);
	if (fabs(denom) < 1e-6)
		return (false);
	oc = substract_vec(&disk->pos, &ray->origin);
	t = dot_scalar_product(&oc, &disk->dir) / denom;
	if (t <= rec->ray_tmin || t >= rec->ray_tmax)
		return (false);
	p = ray_at(ray, t);
	to_center = substract_vec(&p, &disk->pos);
	if (dot_scalar_product(&to_center, &to_center) > disk->rad * disk->rad)
		return (false);
	rec->t = t;
	rec->point = p;
	rec->normal = scalar_mult_vec_ret(&disk->dir, -1);
	return (true);
}

bool	hit_plane(t_ray *ray, t_forms *form, t_hit *rec)
{
	t_pl	*pl;
	double	denom;
	double	d;
	double	t;

	pl = form->pl;
	denom = dot_scalar_product(&pl->dir, &ray->dir);
	if (fabs(denom) < 1e-6) //0.0000001
		return (false);
	d = dot_scalar_product(&pl->dir, &pl->pos);
	t = (d - dot_scalar_product(&pl->dir, &ray->origin)) / denom;
	if (t < rec->ray_tmin || t > rec->ray_tmax)
		return (false);
	rec->t = t;
	rec->point = ray_at(ray, t);
	rec->normal = pl->dir;
	return (true);
}

bool	hit_sphere(t_ray *ray, t_forms *form, t_hit *rec)
{
	t_sp	*sp;
	t_hcalc	calc;
	t_vec	oc;

	sp = form->sp;
	oc = substract_vec(&ray->origin, &sp->pos);
	calc.a = length_squared(&ray->dir);
	calc.b = dot_scalar_product(&oc, &ray->dir);
	calc.c = length_squared(&oc) - (sp->rad * sp->rad);
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
	//fprintf(stderr, "t hit plane is: %f\n", rec->t);
	rec->point = ray_at(ray, rec->t);
	rec->normal = substract_vec(&rec->point, &sp->pos);
	rec->normal = normalize_vec(&rec->normal);
	return (true);
}
	//scalar_div_vec(&rec->normal, sp->rad);

t_hit	nearest_hit(t_ray *ray, t_scene *scene)
{
	t_objs	*obj;
	t_hit	rec;

	rec.ray_tmin = 0.0000001;
	rec.ray_tmax = INT_MAX;
	rec.t = -1.0;
	obj = scene->objs;
	while (obj)
	{
		if (obj->hit(ray, &obj->form, &rec) == true)
		{
			//fprintf(stderr, "obj col is %d\n", (int)obj->col.r);
			rec.ray_tmax = rec.t;
			rec.obj = obj;
		}
		obj = obj->next;
	}
	return (rec);
}
