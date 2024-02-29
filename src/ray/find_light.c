/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:46:48 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/29 10:53:59 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	get_next_ligth(t_scene *scene, t_point origin, t_hit *rec)
{
	t_ray light;
	double dotprod;
	double	final;

	// while (scene->light)
	// {
		light.origin = scene->light->pos;
		light.dir = substract_vec(&light.origin, &origin);
		light.dir = normalize_vec(&light.dir);
		dotprod = dot_scalar_product(&rec->normal, &light.dir);
		//falta update rec->t_max para que no reimpacte consigo mismo por dento
		final = scene->light->ratio * dotprod;
		if (final > 0.0)
			final *= -1;
		// scene->light = scene->light->next;
	// }
	return final;
}

/*
final color is affected by:
	1. object original color
	2. ambient_light * ratio
	3. spotlight * ratio * angulo_de_incidencia
		3.5. multiple lights
todo esto se tiene que computar y sumar/racionar para que tengamos el color final
pero no se como xd
*/

/* while (objects) { //hit function
	if (object->hit(ray, ray_tmin, closest_so_far, temp_rec)) {
		hit_anything = true;
		closest_so_far = temp_rec.t;
		rec = temp_rec;
	}
} 
we update ray_tmax (closest_so_far) so for each object it will be reduced and it will
keep the shortest distance (it wont hit if the obj is further than the temp_rec).
temp_rec keeps the position, the normal, the t and color
*/