/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:46:48 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/27 13:10:52 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	calculate_light(t_vec pos, t_point point, t_scene *scene, t_hit *rec)
{
	t_ray	light;
	double	magnitude;
	double	dotprod;
	t_hit	light_rec;

	light.origin = pos;
	light.dir = substract_vec(&light.origin, &point);
	magnitude = length_vec(&light.dir);
	light.dir = substract_vec(&point, &light.origin);
	light.dir = normalize_vec(&light.dir);
	light_rec = nearest_hit(&light, scene);
	light.dir = substract_vec(&light.origin, &point);
	light.dir = normalize_vec(&light.dir);
	if (light_rec.t > 0.0 && light_rec.t + 1e-6 < magnitude)
		dotprod = -1.0;
	else
		dotprod = dot_scalar_product(&rec->normal, &light.dir);
	return (dotprod);
}

t_color	illuminate(t_scene *scene, t_point point, t_hit *rec)
{
	double	dotprod;
	t_color	final;
	t_color	illum;
	t_light	*lightptr;

	final = mix_colors(scene->ambient.color, rec->obj->col, scene->ambient.ratio);
	lightptr = scene->light;
	while (lightptr)
	{
		dotprod = calculate_light(lightptr->pos, point, scene, rec);
		if (dotprod > 0.0)
		{
			illum = mix_colors(lightptr->color, rec->obj->col, dotprod * lightptr->ratio);
			final = add_colors(final, illum);
		}
		lightptr = lightptr->next;
	}
	return (final);
}
