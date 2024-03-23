/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:46:48 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/23 17:39:25 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	get_next_ligth(t_scene *scene, t_point point, t_hit *rec)
{
	t_ray	light;
	double	dotprod;
	double	final;
	t_hit	light_rec;
	double	magnitude;

	// while (scene->light)
	// {
		light.origin = scene->light->pos;
		light.dir = substract_vec(&light.origin, &point);
		magnitude = length_vec(&light.dir);
		light.dir = normalize_vec(&light.dir);

		light.dir = substract_vec(&point, &light.origin);
		light.dir = normalize_vec(&light.dir);
		light_rec = nearest_hit(&light, scene);
		light.dir = substract_vec(&light.origin, &point);
		light.dir = normalize_vec(&light.dir);
		if (light_rec.t > 0.0 && light_rec.t + 1e-6 < magnitude)
			dotprod = -1.0;
		else
		{
			dotprod = dot_scalar_product(&rec->normal, &light.dir);
		}
		if (dotprod < 0.0)
			dotprod = 0.0;
		final = scene->light->ratio * dotprod;
		// scene->light = scene->light->next;
	// }
	return (final);
}

t_color	illuminate(t_scene *scene, t_point point, t_hit *rec)
{
	t_ray	light;
	double	dotprod;
	t_color	final;
	t_hit	light_rec;
	double	magnitude;

	final = rec->obj->col;
	// while (scene->light)
	// {
		light.origin = scene->light->pos;
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
		{
			dotprod = dot_scalar_product(&rec->normal, &light.dir);
			if (dotprod > 0.0)
			{
				final = mix_colors(final, scene->light->color, dotprod*scene->light->ratio);
			}
		}
		// scene->light = scene->light->next;
	// }
	final = mix_colors(scene->ambient.color, final, scene->ambient.ratio);
	return (final);
}


//https://www.gamedev.net/blogs/entry/2260865-shadows-and-point-lights/ tiene muuy buena pinta

/* shade(ray, point, normal, lights) 
{
	result = ambient;
	for light in lights
	{
		if (shadow ray not blocked)
			result += shading contribution;
	}
	return result;
} */
