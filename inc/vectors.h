/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:43:31 by jmarinel          #+#    #+#             */
/*   Updated: 2024/02/15 17:00:44 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

/*========== STRUCTURE ==========*/
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vec;

/*========== VECTORS ==========*/
t_vec	*new_vec(double x, double y, double z);
t_vec	*add_vec(t_vec *vec1, t_vec *vec2);
t_vec	*substract_vec(t_vec *vec1, t_vec *vec2);
t_vec	*scalar_mult_vec(t_vec *vec, double f);
double	length_vec(t_vec *vec);
t_vec	*normalize_vec(t_vec *vec);
double	dot_scalar_product(t_vec *vec1, t_vec *vec2);
t_vec	*cross_product(t_vec *vec1, t_vec *vec2);


#endif