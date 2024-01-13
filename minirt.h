/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/01/13 19:08:41 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>
# include <fcntl.h>
// =================================== DEFINITIONS =============================
# define WIN_H 800
# define WIN_W 800

/*========== COLORS ==========*/
# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define CYAN 0x00FFFF
# define YELLOW 0xFFFF00
# define BLACK 0x000000
# define TURQ 0x5DC1B9
# define SPRING 0x5ef38c
# define FAN 0xa80874

// ================================= STRUCTURES =============================

typedef enum e_scene
{
	AMBI = 1,
	CAM = 2,
	LIGHT = 3,
	SP = 4,
	CY = 5,
	PL = 6
}	e_types;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ambientLight
{
	float		ratio;
	t_vec		color;
}	t_ambient;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	rot;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_vec	pos;
	float	ratio;
}	t_light;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	cam;
	t_light		light;
}	t_scene;

// =================================== FUNCTIONS =============================
/*========== MAIN =============*/
/* ERROR_MNGR.C */
int	error_msg(char *msg);

/*========== PARSING ==========*/
/* open_map.c */
int	open_map(char *fname, t_scene *scene);

/* parse_lines.c */
int	check_identifiers(char *str);

#endif