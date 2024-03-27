/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/27 16:51:35 by jmarinel         ###   ########.fr       */
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
# define WIN_W 800
# define WIN_H 800

# define CLOSE 17

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
	CN = 7
}	t_stypes;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				hex;
}	t_color;


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
int		error_msg(char *msg);

/* color.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_color	new_color(unsigned char r, unsigned char g, unsigned char b);
t_color	new_color_doub(double r, double g, double b);
t_color	mix_colors(t_color col1, t_color col2, double ratio);

/* utils.c */
void	*my_malloc(size_t size);
double	ft_atod(char *str);
t_objs	*ft_listlast_obj(t_objs *lst);

/*========== PARSING ==========*/
/* open_map.c */
int		open_map(char *fname, t_scene *scene);

/* parse_lines.c */
int		check_identifiers(char *str);

/* INIT_SCENE.C */
void	init_type(t_scene *scene, char **args, int type);
void	print_scene(t_scene *scene);
void	print_objs(t_objs *objs, int type);
t_vec	parse_vector(char *line);
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
double	get_next_ligth(t_scene *scene, t_point origin, t_hit *rec);

/* hit.c */
t_hit	nearest_hit(t_ray *ray, t_scene *scene);
bool	hit_sphere(t_ray *ray, t_forms *form, t_hit *rec);
bool	hit_plane(t_ray *ray, t_forms *form, t_hit *rec);
bool	hit_cyl(t_ray *ray, t_forms *obj, t_hit *rec);
bool	hit_disk(t_ray *ray, t_disk *disk, t_hit *rec);

#endif

/* 

t_vec3	calculate_normal(const t_cylinder *cylinder, const t_point3 p)
{
	t_vec3	tmp;
	t_vec3	tmp2;
	t_vec3	normal;

	tmp = substract_vec3(&cylinder->center, &p);
	tmp2 = product_vec3_r(&cylinder->dir, dot(&tmp, &cylinder->dir));
	normal = substract_vec3(&tmp2, &tmp);
	return (unit_vector(&normal));
}

bool	calc_hit_cilinder(t_evars vars, const t_ray *ray, t_hit *rec,
		t_objects obj)
{
	double	projection;
	t_vec3	tmp;

	if (vars.discriminant < 0)
		return (false);
	vars.sqrtd = sqrt(vars.discriminant);
	vars.root = (-vars.half_b - vars.sqrtd) / vars.a;
	if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
	{
		vars.root = (-vars.half_b + vars.sqrtd) / vars.a;
		if (vars.root <= rec->ray_tmin || vars.root >= rec->ray_tmax)
			return (false);
	}
	tmp = ray_at(ray, vars.root);
	tmp = substract_vec3(&tmp, &obj.cy->center);
	projection = dot(&obj.cy->dir, &tmp);
	if (projection < 0 || projection > obj.cy->height)
		return (false);
	rec->t = vars.root;
	rec->p = ray_at(ray, vars.root);
	rec->normal = calculate_normal(obj.cy, rec->p);
	return (true);
}

bool	hit_body_cylinder(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_vec3	oc;
	t_vec3	tmp;
	t_vec3	direction_parallel;
	t_vec3	oc_parallel;
	t_evars	vars;

	oc = substract_vec3(&ray->orig, &obj.cy->center);
	tmp = product_vec3_r(&obj.cy->dir, dot(&ray->dir, &obj.cy->dir));
	direction_parallel = substract_vec3(&ray->dir, &tmp);
	tmp = product_vec3_r(&obj.cy->dir, dot(&oc, &obj.cy->dir));
	oc_parallel = substract_vec3(&oc, &tmp);
	vars.a = length_squared(&direction_parallel);
	vars.half_b = dot(&oc_parallel, &direction_parallel);
	vars.c = length_squared(&oc_parallel) - obj.cy->radius * obj.cy->radius;
	vars.discriminant = vars.half_b * vars.half_b - vars.a * vars.c;
	return (calc_hit_cilinder(vars, ray, rec, obj));
}

bool	hit_cylinder(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_disk	disk;
	t_ray	displace;

	displace.orig = obj.cy->center;
	displace.dir = obj.cy->dir;
	disk.center = obj.cy->center;
	disk.dir = obj.cy->dir;
	disk.radius = obj.cy->radius;
	obj.cy->hit[H_DISK_BA] = hit_disk(ray, &disk, rec);
	if (obj.cy->hit[H_DISK_BA])
		rec->ray_tmax = rec->t;
	disk.center = ray_at(&displace, obj.cy->height);
	disk.dir = product_vec3_r(&obj.cy->dir, -1);
	obj.cy->hit[H_DISK_TA] = hit_disk(ray, &disk, rec);
	if (obj.cy->hit[H_DISK_TA])
		rec->ray_tmax = rec->t;
	obj.cy->hit[H_CYLINDER] = hit_body_cylinder(ray, obj, rec);
	return (obj.cy->hit[H_DISK_BA] || obj.cy->hit[H_DISK_TA]
		|| obj.cy->hit[H_CYLINDER]);
}


bool	hit_disk(const t_ray *ray, t_disk *disk, t_hit *rec)
{
	double	denom;
	t_vec3	oc;
	double	t;
	t_vec3	p;
	t_vec3	to_center;

	denom = dot(&disk->dir, &ray->dir);
	if (fabs(denom) < BIAS)
		return (false);
	oc = substract_vec3(&disk->center, &ray->orig);
	t = dot(&oc, &disk->dir) / denom;
	if (t <= rec->ray_tmin || t >= rec->ray_tmax)
		return (false);
	p = ray_at(ray, t);
	to_center = substract_vec3(&p, &disk->center);
	if (dot(&to_center, &to_center) > disk->radius * disk->radius)
		return (false);
	rec->t = t;
	rec->p = p;
	rec->normal = product_vec3_r(&disk->dir, -1);
	return (true);
} 


t_vec3	product_vec3_r(const t_vec3 *vector, double factor)
{
	t_vec3	res;

	res = *vector;
	res.x *= factor;
	res.y *= factor;
	res.z *= factor;
	return (res);
}

t_vec3	division_vec3_r(const t_vec3 *vector, double factor)
{
	t_vec3	res;

	res = *vector;
	res.x /= factor;
	res.y /= factor;
	res.z /= factor;
	return (res);
}

double	dot(const t_vec3 *v1, const t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}*/