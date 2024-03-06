/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:10:02 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/06 16:40:59 by alcaball         ###   ########.fr       */
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

void print_vec(t_vec vec, char *name)
{
	printf("%s is %f, %f, %f\n", name, vec.x, vec.y, vec.z);
}

void	calculate_viewport(t_camera *cam)
{
	t_vec	vp_up_left;
	t_vec	aux[5];
	t_vec	tmpaxis;
	t_vec	axis[3]; //0 = u, 1 = v, 2 = w

	cam->focal_len = 1.0;
	cam->vp_w = 2.0 * tan(deg2rad(cam->fov) / 2) * cam->focal_len;
	cam->vp_h = cam->vp_w * ((double)WIN_H / (double)WIN_W);
	cam->center = new_vec(0, 0, 0);
	cam->vup = new_vec(0, 1, 0);
	axis[2] = cam->dir;
	// scalar_mult_vec(&axis[2], -1); //esto gira la camara, no se si es necesario
	if (fabs(dot_scalar_product(&cam->vup, &axis[2])) == 1)
		axis[2].x += 0.001;
	tmpaxis = cross_product(&cam->vup, &axis[2]);
	axis[0] = normalize_vec(&tmpaxis);
	axis[1] = cross_product(&axis[2], &axis[0]);
	cam->vp_u = scalar_mult_vec_ret(&axis[0], cam->vp_w);
	tmpaxis = scalar_mult_vec_ret(&axis[1], -1);
	cam->vp_v = scalar_mult_vec_ret(&tmpaxis, cam->vp_h);
	cam->px_dlt_u = scalar_div_vec_ret(&cam->vp_u, WIN_W);
	cam->px_dlt_v = scalar_div_vec_ret(&cam->vp_v, WIN_H);
	scalar_mult_vec(&axis[2], cam->focal_len);
	aux[1] = scalar_div_vec_ret(&cam->vp_u, 2.0);
	aux[2] = scalar_div_vec_ret(&cam->vp_v, 2.0);
	aux[3] = add_vec(&aux[1], &aux[2]);
	aux[4] = substract_vec(&cam->center, &axis[2]);
	vp_up_left = substract_vec(&aux[4], &aux[3]);
	calculate_px00_loc(cam, &vp_up_left);
}
