/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:29 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/19 11:39:28 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
	if (open_map(argv[1], scene) < 0)
		return (error_msg("invalid argc"));
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "MINIRT");
	mlx.img.img = mlx_new_image(mlx.mlx, WIN_W, WIN_H);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, \
		&mlx.img.line_length, &mlx.img.endian);
	// mlx_hook(mlx.win, 2, 0, register_hooks, &mlx);
	cast_rays(&mlx, scene); //funcion dibujo
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_hook(mlx.win, CLOSE, 0, close_program, (&mlx));
	mlx_loop(mlx.mlx);
}
