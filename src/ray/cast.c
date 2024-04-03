/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:42:07 by alcaball          #+#    #+#             */
/*   Updated: 2024/04/03 17:31:48 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	random_number(void)
{
	double	val;
	int		readval;

	if (SAMPLES == 1)
		return (0.5);
	readval = rand();
	if (readval < 0)
		readval *= -1;
	val = (double)readval;
	while (val >= 1)
		val /= 10;
	return (val);
}

t_point	rand_pixel(t_point *deltu, t_point *deltv)
{
	t_point	new;
	t_point	tempx;
	t_point	tempy;
	double	factor;

	factor = -0.5 + random_number();
	tempx = scalar_mult_vec_ret(deltu, factor);
	factor = -0.5 + random_number();
	tempy = scalar_mult_vec_ret(deltv, factor);
	new = add_vec(&tempx, &tempy);
	return (new);
}

t_color	ray_color(t_ray *ray, t_scene *scene)
{
	t_hit	rec;
	t_color	px_color;

	rec = nearest_hit(ray, scene);
	if (rec.t > 0)
	{
		px_color = illuminate(scene, ray_at(ray, rec.t), &rec);
		return (px_color);
	}
	return (mix_colors(scene->ambient.color, new_color(100, 100, 100), 0.4));
}

t_vec	camera_ray(t_scene *scene, int i, int j)
{
	t_vec	px_position[3];
	t_point	px_center;
	t_vec	ray_dir;
	t_vec	px_samp;
	t_ray	ray;

	px_position[0] = scalar_mult_vec_ret(&scene->cam.px_dlt_u, i);
	px_position[1] = scalar_mult_vec_ret(&scene->cam.px_dlt_v, j);
	px_position[2] = add_vec(&px_position[0], &px_position[1]);
	px_center = add_vec(&scene->cam.px00_loc, &px_position[2]);
	px_position[0] = rand_pixel(&scene->cam.px_dlt_u, &scene->cam.px_dlt_v);
	px_samp = add_vec(&px_center, &px_position[0]);
	ray_dir = substract_vec(&px_samp, &scene->cam.center);
	ray = new_ray(&scene->cam.center, &ray_dir);
	return (color_to_point(ray_color(&ray, scene)));
}

void	cast_rays(t_mlx *mlx, t_scene *scene)
{
	int		i;
	int		j;
	int		samp;
	t_point	pt;
	t_point	pt2;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			samp = 0;
			pt2 = new_vec(0, 0, 0);
			while (samp < SAMPLES)
			{
				pt = camera_ray(scene, i, j);
				pt2 = add_vec(&pt, &pt2);
				samp++;
			}
			my_mlx_pixel_put(&mlx->img, i, j, average_color(pt2));
			i++;
		}
		j++;
	}
}
