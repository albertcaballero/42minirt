/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:46:48 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/11 19:07:21 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	get_next_ligth(t_scene *scene, t_point origin, t_hit *rec)
{
	t_ray	light;
	double	dotprod;
	double	final;
	t_hit	light_rec;

	// while (scene->light)
	// {
		light.origin = scene->light->pos;
		light.dir = substract_vec(&light.origin, &origin);
		light.dir = normalize_vec(&light.dir);
		light_rec = nearest_hit(&light, scene);
		if (light_rec.t > 0.0)
		{
			// printf("%f\n", light_rec.t);
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
