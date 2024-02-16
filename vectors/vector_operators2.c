/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operators2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:14:27 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/15 16:56:11 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//dot == 0 vectors are orthogonal/perpendicular
//dot == 1 vectors are parallel
//dot == -1 vectors point in opposite directions
double	dot_scalar_product(t_vec *vec1, t_vec *vec2)
{
	double	dot;

	dot = vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
	return (dot);
}

t_vec	*cross_product(t_vec *vec1, t_vec *vec2)
{
	t_vec	*vec3;

	vec3 = new_vec(vec1->y * vec2->z - vec1->z * vec2->y, \
					vec1->z * vec2->x - vec1->x * vec2->z, \
					vec1->x * vec2->y - vec1->y * vec2->x);
	return (vec3);
}

t_vec	*normalize_vec(t_vec *vec)
{
	double	len;
	double	inv_len;

	len = length_vec(vec);
	inv_len = 0;
	if (len > 0)
	{
		inv_len = 1 / len;
		vec->x *= inv_len;
		vec->y *= inv_len;
		vec->z *= inv_len;
		return (vec);
	}
	return (NULL);
}
