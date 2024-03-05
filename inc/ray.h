/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:14:43 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/05 12:11:51 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"

typedef struct s_ray
{
	t_point	origin;
	t_vec	dir;
}	t_ray;

t_vec	ray_at(t_ray *ray, double t);
t_ray	new_ray(t_point *origin, t_point *dir);


#endif