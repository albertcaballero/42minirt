/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:42:07 by alcaball          #+#    #+#             */
/*   Updated: 2024/04/03 15:58:27 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	ray_color(t_ray *ray, t_scene *scene)
{
	t_hit	rec;
	t_color	px_color;

	rec = nearest_hit(ray, scene);
	//print_objs(rec.obj);
	if (rec.t > 0)
	{
		px_color = illuminate(scene, ray_at(ray, rec.t), &rec);
		return (px_color);
	}
	return (mix_colors(scene->ambient.color, new_color(100, 100, 100), 0.4));
}

t_ray	camera_ray(t_scene *scene, int i, int j)
{
	t_vec	px_position[3];
	t_point	px_center;
	t_vec	ray_dir;
	t_ray	ray;

	px_position[0] = scalar_mult_vec_ret(&scene->cam.px_dlt_u, i);
	px_position[1] = scalar_mult_vec_ret(&scene->cam.px_dlt_v, j);
	px_position[2] = add_vec(&px_position[0], &px_position[1]);
	px_center = add_vec(&scene->cam.px00_loc, &px_position[2]);
	ray_dir = substract_vec(&px_center, &scene->cam.center);
	ray = new_ray(&scene->cam.center, &ray_dir);
	return (ray);
}

void	cast_rays(t_mlx *mlx, t_scene *scene)
{
	int		i;
	int		j;
	t_ray	ray;
	t_color	color;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			ray = camera_ray(scene, i, j);
			color = ray_color(&ray, scene);
			my_mlx_pixel_put(&mlx->img, i, j, color.hex);
			i++;
		}
		j++;
	}
}
