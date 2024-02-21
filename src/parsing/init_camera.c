/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:10:02 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/21 15:52:25 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	calculate_viewport(t_camera *cam)
{
	cam->focal_len = 1.0;
	cam->vp_w = 2 * tan(deg2rad(cam->fov) / 2);
	cam->vp_h = cam->vp_w * ((double)WIN_H / (double)WIN_W);
	cam->vp_u = new_vec(cam->vp_w, 0, 0);
	cam->vp_v = new_vec(0, -cam->vp_h, 0);
	scalar_div_vec(&cam->vp_u, WIN_W);
	scalar_div_vec(&cam->vp_v, WIN_H);
	// cam->px00_loc = ;
}

