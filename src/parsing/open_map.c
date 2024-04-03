/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:29:44 by alcaball          #+#    #+#             */
/*   Updated: 2024/04/03 15:43:33 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_valid_name(char *fname)
{
	int	i;

	i = ft_strlen(fname);
	i--;
	if (i < 4)
		error_msg("Invalid file format (*.rt)", -1, NULL);
	if (fname[i] != 't')
		error_msg("Invalid file format (*.rt)", -1, NULL);
	if (fname[i - 1] != 'r')
		error_msg("Invalid file format (*.rt)", -1, NULL);
	if (fname[i - 2] != '.')
		error_msg("Invalid file format (*.rt)", -1, NULL);
	return (0);
}

void	fix_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}

void	split_map(int fd, t_scene *scene, t_parsing *counter)
{
	char		*line;
	char		**split;
	int			type;

	line = get_next_line(fd);
	if (line == NULL)
		error_msg("Empty file", -1, scene);
	while (line)
	{
		counter->line++;
		fix_line(line);
		if (line && ft_strlen(line) != 0)
		{
			split = ft_split(line, ' ');
			type = check_identifiers(split[0], counter->line);
			count_identifiers(type, counter, !INIT);
			if (type != '#')
				init_type(scene, split, type);
			free_split(split);
		}
		free(line);
		line = get_next_line(fd);
	}
}

int	open_map(char *fname, t_scene *scene)
{
	int			fd;
	t_parsing	counter;

	check_valid_name(fname);
	count_identifiers(0, &counter, INIT);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		error_msg("Could not open file", -1, NULL);
	split_map(fd, scene, &counter);
	check_counters(&counter);
	close (fd);
	return (0);
}

void	print_objs(t_objs *objs)
{
	if (objs->type == SP)
	{
		dprintf(2, "========= SPHERE ===============\n");
		dprintf(2, "rad: %f\npos: %f,%f,%f\ncol: %i,%i,%i\n",\
			objs->form.sp->rad, objs->form.sp->pos.x, objs->form.sp->pos.y, \
			objs->form.sp->pos.z, objs->col.r, objs->col.g, objs->col.b);
	}
	else if (objs->type == PL)
	{
		dprintf(2, "========= PLANE ===============\n");
		dprintf(2, "pos: %f,%f,%f\ncol: %i,%i,%i\n", \
			objs->form.pl->pos.x, objs->form.pl->pos.y, objs->form.pl->pos.z, \
			objs->col.r, objs->col.g, objs->col.b);
	}
	else if (objs->type == CY)
	{
		dprintf(2, "========= CYLINDER ===============\n");
		dprintf(2, "rad: %f\npos: %f,%f,%f\ncol: %i,%i,%i\n", \
			objs->form.cy->rad, objs->form.cy->pos.x, objs->form.cy->pos.y, \
			objs->form.cy->pos.z, objs->col.r, objs->col.g, objs->col.b);
	}
	else if (objs->type == PB)
	{
		dprintf(2, "========= PARABOLOID ===============\n");
		dprintf(2, "rad: %f\npos: %f,%f,%f\ncol: %i,%i,%i\n", \
			objs->form.pb->rad, objs->form.pb->pos.x, objs->form.pb->pos.y, \
			objs->form.pb->pos.z, objs->col.r, objs->col.g, objs->col.b);
	}
}
