/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:14:27 by alcaball          #+#    #+#             */
/*   Updated: 2024/01/13 17:17:00 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec	*new_vec(double x, double y, double z)
{
	t_vec *new;

	new = malloc(sizeof(t_vec));
	if (!new)
		return (error_msg("Memory allocation failed"));
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}
t_vec	*substract_vec(t_vec *vec1, t_vec *vec2)
{
	t_vec *res;

	res = new_vec(vec1->x - vec2->x, vec1->y - vec2->y, vec1->z - vec2->z);
	if (!res)
		return (NULL);
	return (res);
}

t_vec	multiply_vec(t_vec vec1, t_vec vec2)
{
	return (vec1);
}
