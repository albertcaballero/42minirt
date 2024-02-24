/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:46:48 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/24 18:27:44 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	get_next_ligth(t_scene *scene, t_point origin)
{
	t_vec	p2l; //point to light
	t_ray	ray;

	while (scene->light)
	{
		p2l = substract_vec(&scene->light->pos, &origin);
		p2l = normalize_vec(&p2l);
		ray = new_ray(&origin, &p2l);
		scene->light = scene->light->next;
	}
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

/* while (objects) {
	if (object->hit(ray, ray_tmin, closest_so_far, temp_rec)) {
		hit_anything = true;
		closest_so_far = temp_rec.t;
		rec = temp_rec;
	}
} 
we update ray_tmax (closest_so_far) so for each object it will be reduced and it will
keep the shortest distance (it wont hit if the obj is further than the temp_rec).
temp_rec keeps the position, the normal, the t and color
temp_rec {
	t_point	p;
    t_vec3	normal;
    double	t;
    bool	front_face;
}
*/