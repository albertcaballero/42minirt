/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operators3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:29:04 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/21 17:35:59 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vectors.h>

void	scalar_mult_vec(t_vec *vec, double f)
{
	vec->x *= f;
	vec->y *= f;
	vec->z *= f;
}

void	scalar_div_vec(t_vec *vec, double f)
{
	vec->x /= f;
	vec->y /= f;
	vec->z /= f;
}

t_vec	scalar_mult_vec_ret(t_vec *vec, double f)
{
	t_vec	new;

	new.x = vec->x * f;
	new.y = vec->y * f;
	new.z = vec->z * f;
	return (new);
}

t_vec	scalar_div_vec_ret(t_vec *vec, double f)
{
	t_vec	new;

	new.x = vec->x / f;
	new.y = vec->y / f;
	new.z = vec->z / f;
	return (new);
}
