/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:29:44 by alcaball          #+#    #+#             */
/*   Updated: 2024/04/03 17:21:03 by alcaball         ###   ########.fr       */
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
	int	spac;

	i = 0;
	spac = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		if (line[i] == '\n')
			line[i] = '\0';
		if (line[i] == ' ' || line[i] == '\0')
			spac++;
		i++;
	}
	if (i == spac)
		ft_bzero(line, i);
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
