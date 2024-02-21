/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:14:43 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/21 15:54:17 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"

typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

t_vec	ray_at(t_ray *ray, double t);

#endif