/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:46:48 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/23 15:57:21 by alcaball         ###   ########.fr       */
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
	//ratio, color and angle affect the final color
}
