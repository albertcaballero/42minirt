/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:42:07 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/23 11:05:27 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>


//DELETE FUNCTION ============================================
double	hit_sphere(t_point *cent, double rad, t_ray *ray)
{
	t_vec oc = substract_vec(&ray->origin, cent);
	double a = dot_scalar_product(&ray->dir, &ray->dir);
	double b = 2.0 * dot_scalar_product(&oc, &ray->dir);
	double c = dot_scalar_product(&oc, &oc) - rad * rad;
	double disc = b*b - 4*a*c;

	if (disc < 0)
		return (-1.0);
	else
		return ((-b - sqrt(disc) ) / (2.0*a));
}//=========================================================


//DELETE FUNCTION ============================================
double hit_plane(t_point *pos, t_vec *dir, t_ray *ray)
{
	double rest = pos->x * dir->x + pos->y * dir->y + pos->z * dir->z;
	double a = dir->x * ray_at(ray, pos->z).x;
	double b = dir->y * ray_at(ray, pos->z).y;
	double c = dir->z * ray_at(ray, pos->z).z;
	double result = a + b + c - rest;
	return result;
}//=========================================================

t_color	ray_color(t_ray *ray)
{
	t_color	color;
	t_color	color2;
	t_vec	unit_dir;
	double	a;

	//delete from here ===================================
	t_point sph = new_vec(0, 0, -1);
	double hit = hit_sphere(&sph, 0.5, ray);
	if (hit > 0.0)
	{
		t_vec rayat = ray_at(ray, hit);
		t_vec rand = new_vec(0,0,-1);
		t_vec subs = substract_vec(&rayat, &rand);
		t_vec nml = normalize_vec(&subs);
		return (new_color_doub(0.5 * (nml.x + 1), 0.5 * (nml.y + 1), 0.5 * (nml.z + 1)));
	}
	t_point plane = new_vec(0, 0, -1.3);
	t_vec	pldir = new_vec(0, -1, 0.3);
	double hit2 = hit_plane(&plane, &pldir, ray);
	if (hit2 > 0.0)
	{
		t_vec rayat = ray_at(ray, hit2);
		t_vec rand = new_vec(0,0,-1);
		t_vec subs = substract_vec(&rayat, &rand);
		t_vec nml = normalize_vec(&subs);
		return (new_color_doub(0.5 * (nml.x + 1), 0.5 * (nml.y + 1), 0.5 * (nml.z + 1)));
	}
	//to here ============================================

	unit_dir = normalize_vec(&ray->dir);
	a = 0.5 * (unit_dir.y + 1.0);
	color = new_color_doub((1.0 - a) * 1.0, (1.0 - a) * 1.0, (1.0 - a) * 1.0);
	color2 = new_color_doub(a * 0.2, a * 0.7, a * 0.3);
	return (new_color(color.r + color2.r, color.g + color2.g, color.b + color2.b));
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
			color = ray_color(&ray);
			my_mlx_pixel_put(&mlx->img, i, j, color.hex);
			i++;
		}
		j++;
	}
}
