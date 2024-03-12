/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:10:56 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/12 10:59:28 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec	ray_at(t_ray *ray, double t)
{
	t_vec	temp;

	temp = scalar_mult_vec_ret(&ray->dir, t);
	return (add_vec(&ray->origin, &temp));
}

t_ray	new_ray(t_point *origin, t_point *dir)
{
	t_ray	new;

	new.origin = new_vec(origin->x, origin->y, origin->z);
	new.dir = new_vec(dir->x, dir->y, dir->z);
	return (new);
}
