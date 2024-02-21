/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:10:56 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/21 15:54:12 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec	ray_at(t_ray *ray, double t)
{
	scalar_mult_vec(&ray->dir, t);
	return (add_vec(&ray->origin, &ray->dir));
}
