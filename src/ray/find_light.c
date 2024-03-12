/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:46:48 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/12 18:48:28 by jmarinel         ###   ########.fr       */
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
	t_ray	inv;

	// while (scene->light)
	// {
		light.origin = scene->light->pos;
		light.dir = substract_vec(&light.origin, &point);
		light.dir = normalize_vec(&light.dir);

		inv.origin = point;
		inv.dir = substract_vec(&scene->light->pos, &inv.origin);
		magnitude = length_vec(&inv.dir);
		light_rec = nearest_hit(&inv, scene);
		if (light_rec.t > 0.0 && light_rec.t + 1e-6 < magnitude) //si se cumple es sombra y se encuentra or delate de la luz
				dotprod = -1.0;
		else
			dotprod = dot_scalar_product(&rec->normal, &light.dir);
		if (dotprod < 0.0)
			dotprod = 0.0;
		final = scene->light->ratio * dotprod;
		// scene->light = scene->light->next;
	// }
	return (final);
}
