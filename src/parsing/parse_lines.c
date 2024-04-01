/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:03:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/04/01 15:05:13 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	check_counters(t_parsing *counter)
{
	if (counter->ambicount == 0)
		error_msg("No ambient light", -1, NULL);
	if (counter->ambicount > 1)
		error_msg("Too many ambient lights", -1, NULL);
	if (counter->camcount == 0)
		error_msg("No camera", -1, NULL);
	if (counter->camcount > 1)
		error_msg("Too many cameras", -1, NULL);
	if (counter->cycount + counter->plcount + counter->spcount > 50)
		error_msg("Too many objects in scene [max 50]", -1, NULL);
}

void	count_identifiers(int type, t_parsing *counter, int method)
{
	if (type == AMBI)
		counter->ambicount++;
	else if (type == CAM)
		counter->camcount++;
	else if (type == LIGHT)
		counter->lightcount++;
	else if (type == SP)
		counter->spcount++;
	else if (type == PL)
		counter->plcount++;
	else if (type == CY)
		counter->cycount++;
	else if (type == PB)
		counter->pbcount++;
	if (method != INIT)
		return ;
	counter->line = 0;
	counter->ambicount = 0;
	counter->camcount = 0;
	counter->lightcount = 0;
	counter->spcount = 0;
	counter->plcount = 0;
	counter->cycount = 0;
	counter->pbcount = 0;
}

int	check_identifiers(char *str, int line)
{
	if (!str)
		return (0);
	if (str[0] == '#')
		return ('#');
	if (ft_strncmp(str, "A", 2) == 0)
		return (AMBI);
	if (ft_strncmp(str, "C", 2) == 0)
		return (CAM);
	if (ft_strncmp(str, "L", 2) == 0)
		return (LIGHT);
	if (ft_strncmp(str, "sp", 3) == 0)
		return (SP);
	if (ft_strncmp(str, "pl", 3) == 0)
		return (PL);
	if (ft_strncmp(str, "cy", 3) == 0)
		return (CY);
	if (ft_strncmp(str, "pb", 3) == 0)
		return (PB);
	error_msg("Unrecognized identifier (A, C, L, sp, cy, pl, pb)", line, NULL);
	return (0);
}
/* 

bool	hit_cylinder(const t_ray *ray, t_objects obj, t_hit *rec)
{
	t_disk	disk;
	t_ray	displace;

	displace.orig = obj.cy->center;
	displace.dir = obj.cy->dir;
	disk.center = obj.cy->center;
	disk.dir = obj.cy->dir;
	disk.radius = obj.cy->radius;
	obj.cy->hit[BOT] = hit_disk(ray, &disk, rec);
	if (obj.cy->hit[BOT])
		rec->ray_tmax = rec->t;
	disk.center = ray_at(&displace, obj.cy->height);
	disk.dir = product_vec3_r(&obj.cy->dir, -1);
	obj.cy->hit[TOP] = hit_disk(ray, &disk, rec);
	if (obj.cy->hit[TOP])
		rec->ray_tmax = rec->t;
	obj.cy->hit[BODY] = hit_body_cylinder(ray, obj, rec);
	return (obj.cy->hit[BOT] || obj.cy->hit[TOP]
		|| obj.cy->hit[BODY]);
} */