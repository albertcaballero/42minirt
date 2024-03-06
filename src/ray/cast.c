/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:42:07 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/06 17:01:07 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	ray_color(t_ray *ray, t_scene *scene)
{
	t_hit	rec;
	double	light;

	rec = nearest_hit(ray, scene);
	if (rec.t > 0)
	{
		light = get_next_ligth(scene, ray_at(ray, rec.t), &rec);
		return (mix_colors(scene->light->color, rec.obj->col, light));
	}
	return (mix_colors(scene->ambient.color, new_color(100, 100, 100), 0.4));
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
