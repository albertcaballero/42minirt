/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:46:48 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/12 16:12:06 by alcaball         ###   ########.fr       */
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
		inv.dir = substract_vec(&inv.origin, &scene->light->pos);
		magnitude = length_vec(&inv.dir);
		scalar_mult_vec(&inv.dir, -1.0);
		// inv.dir = normalize_vec(&inv.dir);
		light_rec = nearest_hit(&inv, scene);
		if (light_rec.t > 0.0) //si se cumple es sombra
		{
			// printf("%f and %f\n", light_rec.t, magnitude);
			// if (magnitude  < light_rec.t + 1e-6)
			// 	dotprod = dot_scalar_product(&rec->normal, &light.dir);
			// else
				dotprod = -1.0;
		}
		else
			dotprod = dot_scalar_product(&rec->normal, &light.dir);
		if (dotprod < 0.0)
			dotprod = 0.0;
		final = scene->light->ratio * dotprod;
		// scene->light = scene->light->next;
	// }
	return (final);
}
