/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:42:07 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/23 15:36:59 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>


//DELETE FUNCTION ============================================
double	hit_sphere(t_sp *sphere, t_ray *ray)
{
	t_vec oc = substract_vec(&ray->origin, &sphere->pos);
	double a = dot_scalar_product(&ray->dir, &ray->dir);
	double b = 2.0 * dot_scalar_product(&oc, &ray->dir);
	double c = dot_scalar_product(&oc, &oc) - sphere->diam * sphere->diam;
	double disc = b*b - 4*a*c;

	if (disc < 0)
		return (-1.0);
	else
		return ((-b - sqrt(disc) ) / (2.0*a));
}//=========================================================

t_color	ray_color(t_ray *ray, t_scene *scene)
{
	t_color	color;
	t_color	color2;
	t_vec	unit_dir;
	t_sp	test_sph;
	double	a;

	//delete from here ===================================
	test_sph.pos = new_vec(0, 0, -1);
	test_sph.diam = 0.5;
	test_sph.col = new_color(255, 0, 0);
	double hit = hit_sphere(&test_sph, ray);
	if (hit > 0.0)
	{
		// t_vec rayat = ray_at(ray, hit);
		// t_vec rand = new_vec(0,0,-1);
		// t_vec subs = substract_vec(&rayat, &rand);
		// t_vec nml = normalize_vec(&subs);
		color = new_color_doub(0.1, 0.7, 0.5);
		color = mix_colors(scene->ambient.color, color, scene->ambient.ratio);
		return (color);
	}
	//to here ============================================

	unit_dir = normalize_vec(&ray->dir);
	a = 0.5 * (unit_dir.y + 1.0);
	color = new_color_doub(1.0, 1.0, 1.0);
	color2 = new_color_doub(0.2, 0.7, 0.3);
	return (mix_colors(color2, color, a));
}

void	cast_rays(t_mlx *mlx, t_scene *scene)
{
	int		i;
	int		j;
	t_ray	ray;
	t_point	px_center;
	t_vec	ray_dir;
	t_color	color;
	t_vec	tmp[3];

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			tmp[0] = scalar_mult_vec_ret(&scene->cam.px_dlt_u, i);
			tmp[1] = scalar_mult_vec_ret(&scene->cam.px_dlt_v, j);
			tmp[2] = add_vec(&tmp[0], &tmp[1]);
			px_center = add_vec(&scene->cam.px00_loc, &tmp[2]);
			ray_dir = substract_vec(&px_center, &scene->cam.center);
			ray = new_ray(&scene->cam.center, &ray_dir);
			color = ray_color(&ray, scene);
			my_mlx_pixel_put(&mlx->img, i, j, color.hex);
			i++;
		}
		j++;
	}
}
