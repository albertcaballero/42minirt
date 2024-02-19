/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:29:44 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/16 18:01:31 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_valid_name(char *fname)
{
	int	i;

	i = ft_strlen(fname);
	i--;
	if (i < 4)
		error_msg("Invalid file format (*.rt)");
	if (fname[i] != 't')
		error_msg("Invalid file format (*.rt)");
	if (fname[i - 1] != 'r')
		error_msg("Invalid file format (*.rt)");
	if (fname[i - 2] != '.')
		error_msg("Invalid file format (*.rt)");
	return (0);
}

int	open_map(char *fname, t_scene *scene)
{
	int		fd;
	int		type;
	char	*line;
	char	**split;

	check_valid_name(fname);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		error_msg("Invalid file");
	line = get_next_line(fd);
	if (line == NULL)
		error_msg("Empty file");
	while (line)
	{
		line = ft_strtrim(line, "\n\t ");
		if (line && ft_strlen(line) != 0)
		{
			split = ft_split(line, ' ');
			type = check_identifiers(split[0]);
			if (type != '#')
				init_type(scene, split, type);
			free_split(split);
		}
		free(line);
		line = get_next_line(fd);
	}
	print_scene(scene);
	close (fd);
	return (0);
}
