/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:36:12 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/19 15:37:56 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	deg2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double	rad2deg(double radians)
{
	return (radians * (180.0 / M_PI));
}
