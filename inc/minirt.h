/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/04/04 11:45:20 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <vectors.h>
# include <ray.h>
# include <limits.h>
# include <stdbool.h>

// =================================== DEFINITIONS =============================
# define WIN_W 1500
# define WIN_H 1000

# define CLOSE 17
# define ESC 53
# define INIT 1
# define MIN 1
# define MAX 2
# define DIR 1.0
# define POS 10000.0
# define SAMPLES 1

# define ERROR 1
# define OK 0
# define LIMIT_RAD 99999
# define LIMIT_HEIGHT 99999
# define LIMIT_VEC 99999

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

/*========== HIT CYL ==========*/
# define BODY 0
# define BOT 1
# define TOP 2

// ================================= STRUCTURES =============================
/*  ===== INPUT ========== */
typedef enum e_scenetypes
{
	AMBI = 1,
	CAM = 2,
	LIGHT = 3,
	SP = 4,
	CY = 5,
	PL = 6,
	CN = 7,
	PB = 8
}	t_stypes;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	hex;
}	t_color;

typedef struct s_parse_scene
{
	int	line;
	int	identifier;
	int	camcount;
	int	lightcount;
	int	ambicount;
	int	spcount;
	int	cycount;
	int	plcount;
	int	pbcount;
}	t_parsing;

/* ==========  OBJECTS  ========== */
typedef struct s_sphere
{
	double	rad;
	t_point	pos;
}	t_sp;

typedef struct s_plane
{
	t_vec	dir;
	t_point	pos;
}	t_pl;

typedef struct s_cylinder
{
	double	rad;
	double	height;
	t_point	pos;
	t_vec	dir;
	bool	hit[3];
}	t_cy;

typedef struct s_decisions
{
	double	t1;
	double	t2;
}	t_decisions;

typedef struct s_paraboloid
{
	t_vec		pos;
	t_vec		dir;
	double		rad;
}	t_pb;

typedef struct s_disk
{
	t_point			pos;
	t_vec			dir;
	double			rad;
}	t_disk;

/*=============== IDENTIFIERS  ==========*/
typedef struct s_ambientLight
{
	float		ratio;
	t_color		color;
}	t_ambient;

typedef struct s_camera
{
	t_point	pos;
	t_vec	dir;
	int		fov;
	double	vp_h;
	double	vp_w;
	double	focal_len;
	t_vec	center;
	t_vec	vp_u;
	t_vec	vp_v;
	t_vec	vup;
	t_vec	px_dlt_u;
	t_vec	px_dlt_v;
	t_point	px00_loc;
}	t_camera;

typedef struct s_light
{
	t_point			pos;
	float			ratio;
	t_color			color;
	struct s_light	*next;
}	t_light;

/*=============== SCENE ==========*/
typedef union u_forms
{
	t_sp	*sp;
	t_cy	*cy;
	t_pl	*pl;
	t_pb	*pb;
}	t_forms;

/*=============== HIT ==========*/
typedef struct s_hit_calc
{
	double				a;
	double				b;
	double				c;
	double				disc;
	double				root;
	double				sqrt;
}						t_hcalc;

typedef struct s_hit
{
	struct s_objects	*obj;
	t_point				point;
	t_color				color;
	t_vec				normal;
	double				t;
	double				ray_tmin;
	double				ray_tmax;
}						t_hit;

typedef struct s_objects
{
	t_forms				form;
	t_color				col;
	bool				(*hit)(t_ray *, t_forms *, t_hit *);
	int					type;
	struct s_objects	*next;
}	t_objs;

typedef struct s_scene
{
	t_camera	cam;
	t_objs		*objs;
	t_ambient	ambient;
	t_light		*light;
	size_t		winsize;
	double		asp_ratio;
}	t_scene;

/*=============== MINILIBX ==========*/
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_data	img;
}	t_mlx;

// =================================== FUNCTIONS =============================
/*========== MAIN =============*/
/* ERROR_MNGR.C */
int		error_msg(char *msg, int line, t_scene *scene);
void	free_all(t_scene *scene);

/* color.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_color	new_color(unsigned char r, unsigned char g, unsigned char b);
t_color	new_color_doub(double r, double g, double b);
t_color	mix_colors(t_color col1, t_color col2, double ratio);
t_color	add_colors(t_color col1, t_color col2);

int		average_color(t_vec color);
t_vec	color_to_point(t_color col1);

/* utils.c */
void	*my_malloc(size_t size);
double	ft_atod(char *str);
t_objs	*ft_listlast_obj(t_objs *lst);
int		ft_clamp(int val1, int max, int type);

/*========== PARSING ==========*/
/* open_map.c */
int		open_map(char *fname, t_scene *scene);

/* parse_lines.c */
int		check_identifiers(char *str, int line);
void	count_identifiers(int type, t_parsing *counter, int method);
void	check_counters(t_parsing *counter);

/* INIT_SCENE.C */
void	init_type(t_scene *scene, char **args, int type);
void	print_scene(t_scene *scene);
void	print_objs(t_objs *objs);
t_vec	parse_vector(char *line, int type);
t_color	parse_color(char *line);

/* check_numbers.c */
int		checkrng_int(char *str, int min, int max);
int		checkrng_dbl(char *str, double min, double max);

/* init_objects.c */
t_objs	*add_objects(t_objs *objs, char **args, int type);
void	init_type_obj(t_objs *obj, char **args, int type);

/* init_camera.c */
void	calculate_viewport(t_camera *cam);

/* init_lights.c */
void	init_lights(t_scene *scene, char **args);

/*========== RAYS ==========*/
/* casting.c */
void	cast_rays(t_mlx *mlx, t_scene *scene);
t_color	ray_color(t_ray *ray, t_scene *scene);

/* find_lights.c */
t_color	illuminate(t_scene *scene, t_point point, t_hit *rec);

/* hit.c */
t_hit	nearest_hit(t_ray *ray, t_scene *scene);
bool	hit_sphere(t_ray *ray, t_forms *form, t_hit *rec);
bool	hit_plane(t_ray *ray, t_forms *form, t_hit *rec);
bool	hit_cyl(t_ray *ray, t_forms *obj, t_hit *rec);
bool	hit_disk(t_ray *ray, t_disk *disk, t_hit *rec);
bool	hit_pb(t_ray *ray, t_forms *obj, t_hit *rec);

#endif
