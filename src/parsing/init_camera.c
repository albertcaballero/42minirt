/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:10:02 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/22 18:03:59 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	calculate_px00_loc(t_camera *cam, t_vec *vp_up_left)
{
	t_vec	px_aux;
	t_vec	halfdist;

	px_aux = add_vec(&cam->px_dlt_u, &cam->px_dlt_v);
	halfdist = scalar_mult_vec_ret(&px_aux, 0.5);
	cam->px00_loc = add_vec(vp_up_left, &halfdist);
}

void	calculate_viewport(t_camera *cam)
{
	t_vec	vp_up_left;
	t_vec	aux[5];

	cam->focal_len = 1.0;
	cam->vp_w = 2.0 * tan(deg2rad(cam->fov) / 2) * cam->focal_len;
	cam->vp_h = cam->vp_w * ((double)WIN_H / (double)WIN_W);
	cam->center = new_vec(0, 0, 0);
	cam->vp_u = new_vec(cam->vp_w, 0, 0); //x - r
	cam->vp_v = new_vec(0, -cam->vp_h, 0); //y - d
	cam->px_dlt_u = scalar_div_vec_ret(&cam->vp_u, WIN_W); //pixel unit ratio
	cam->px_dlt_v = scalar_div_vec_ret(&cam->vp_v, WIN_H);
	aux[0] = new_vec(0, 0, cam->focal_len);
	aux[1] = scalar_div_vec_ret(&cam->vp_u, 2.0);
	aux[2] = scalar_div_vec_ret(&cam->vp_v, 2.0);
	aux[3] = add_vec(&aux[1], &aux[2]);
	aux[4] = substract_vec(&cam->center, &aux[0]);
	vp_up_left = substract_vec(&aux[4], &aux[3]);
	calculate_px00_loc(cam, &vp_up_left);
}
