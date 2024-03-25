/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:46:48 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/25 17:15:12 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

/* double	get_next_ligth(t_scene *scene, t_point point, t_hit *rec)
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
} */

t_color	illuminate(t_scene *scene, t_point point, t_hit *rec)
{
	t_ray	light;
	double	dotprod;
	t_color	final;
	t_hit	light_rec;
	double	magnitude;
	t_color	magia;
	t_light	*lightptr;

	final = mix_colors(scene->ambient.color, rec->obj->col, scene->ambient.ratio);
	lightptr = scene->light;
	while (lightptr)
	{
		light.origin = lightptr->pos;
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
		if (dotprod > 0.0)
		{
			magia = mix_colors(lightptr->color, rec->obj->col, dotprod * lightptr->ratio);
			final = add_colors(final, magia);
		}
		lightptr = lightptr->next;
	}
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
