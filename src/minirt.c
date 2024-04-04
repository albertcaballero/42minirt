/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:29 by alcaball          #+#    #+#             */
/*   Updated: 2024/04/04 11:43:35 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	close_program(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit (0);
	return (1);
}

int	get_key(int key, t_mlx *mlx)
{
	if (key == ESC)
		close_program(mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	t_mlx	mlx;

	if (argc != 2)
		return (error_msg("invalid argc [1]", -1, NULL));
	scene.winsize = WIN_H * WIN_W;
	scene.asp_ratio = (double)WIN_W / (double)WIN_H;
	scene.objs = NULL;
	scene.light = NULL;
	open_map(argv[1], &scene);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "MINIRT");
	mlx.img.img = mlx_new_image(mlx.mlx, WIN_W, WIN_H);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, \
		&mlx.img.line_length, &mlx.img.endian);
	mlx_key_hook(mlx.win, get_key, (&mlx));
	cast_rays(&mlx, &scene);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_hook(mlx.win, CLOSE, 0, close_program, (&mlx));
	mlx_loop(mlx.mlx);
}
