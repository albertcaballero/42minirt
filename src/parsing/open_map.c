/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:29:44 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/27 18:15:43 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_valid_name(char *fname)
{
	int	i;

	i = ft_strlen(fname);
	i--;
	if (i < 4)
		error_msg("Invalid file format (*.rt)", -1);
	if (fname[i] != 't')
		error_msg("Invalid file format (*.rt)", -1);
	if (fname[i - 1] != 'r')
		error_msg("Invalid file format (*.rt)", -1);
	if (fname[i - 2] != '.')
		error_msg("Invalid file format (*.rt)", -1);
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

int	open_map(char *fname, t_scene *scene)
{
	int			fd;
	int			type;
	char		*line;
	char		**split;
	t_parsing	counter;

	check_valid_name(fname);
	count_identifiers(0, &counter, INIT);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		error_msg("Could not open file", -1);
	line = get_next_line(fd);
	if (line == NULL)
		error_msg("Empty file", -1);
	while (line)
	{
		counter.line++;
		fix_line(line);
		if (line && ft_strlen(line) != 0)
		{
			split = ft_split(line, ' ');
			type = check_identifiers(split[0], counter.line);
			count_identifiers(type, &counter, !INIT);
			if (type != '#')
				init_type(scene, split, type);
			free_split(split);
		}
		free(line);
		line = get_next_line(fd);
	}
	check_counters(&counter);
	print_scene(scene);
	close (fd);
	return (0);
}
