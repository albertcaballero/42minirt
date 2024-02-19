/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:10:02 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/19 16:04:57 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	calculate_viewport(t_scene *scene)
{
	scene->cam.focal_len = 1.0;
	scene->cam.viewport_width = 2 * tan(deg2rad(scene->cam.fov) / 2);
	scene->cam.viewport_height = scene->cam.viewport_width * ((double)WIN_H / (double)WIN_W);
}
