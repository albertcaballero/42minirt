/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:29 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/12 11:16:16 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int mlx_recalc_point(int button, int x, int y, t_scene *scene) //delete
{
	t_ray	ray;
	t_point	px_center;
	t_vec	ray_dir;
	t_color	color;
	t_vec	tmp[3];

	if (button != 1)
		return (1);
	printf("=========pixel[%i, %i]==========\n", x, y);
	tmp[0] = scalar_mult_vec_ret(&scene->cam.px_dlt_u, x);
	tmp[1] = scalar_mult_vec_ret(&scene->cam.px_dlt_v, y);
	tmp[2] = add_vec(&tmp[0], &tmp[1]);
	px_center = add_vec(&scene->cam.px00_loc, &tmp[2]);
	ray_dir = substract_vec(&px_center, &scene->cam.center);
	ray = new_ray(&scene->cam.center, &ray_dir);
	color = ray_color(&ray, scene);
	printf("Color %i, %i, %i\n", color.r, color.g, color.b);
	return (0);
}

int	close_program(t_mlx *mlx)
{
	(void) mlx;
	exit (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	t_mlx	mlx;

	if (argc != 2)
		return (error_msg("invalid argc"));
	scene = my_malloc(sizeof(*scene));
	scene->winsize = WIN_H * WIN_W;
	scene->asp_ratio = (double)WIN_W / (double)WIN_H;
	scene->objs = NULL;
	scene->light = NULL;
	if (open_map(argv[1], scene) < 0)
		return (error_msg("invalid argc"));
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "MINIRT");
	mlx.img.img = mlx_new_image(mlx.mlx, WIN_W, WIN_H);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, \
		&mlx.img.line_length, &mlx.img.endian);
	// mlx_hook(mlx.win, 2, 0, register_hooks, &mlx);
	mlx_mouse_hook(mlx.win, mlx_recalc_point, scene);
	cast_rays(&mlx, scene); //funcion dibujo
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_hook(mlx.win, CLOSE, 0, close_program, (&mlx));
	mlx_loop(mlx.mlx);
}
