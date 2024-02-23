/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:46:15 by jmarinel          #+#    #+#             */
/*   Updated: 2024/02/23 13:34:28 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	nearest_hit(t_ray *ray, t_scene *scene)
{
	//ray starts at max length
	double	ray_len;
	t_color	color;

	ray_len = INT_MAX;
	//for each ray we check if it intersects, and store the distance to the point and the point
	while (scene->objs)
	{
		//hit_sphere ?
			//t_intersect = new intersect
		//len < ray_len ? 
			//ray_len = len;
			
		scene->objs = scene->objs->next;
	}
}