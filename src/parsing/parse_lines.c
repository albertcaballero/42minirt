/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:03:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/27 16:56:17 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	check_counters(t_parsing *counter)
{
	if (counter->ambicount == 0)
		error_msg("No ambient light", -1);
	if (counter->ambicount > 1)
		error_msg("Too many ambient lights", -1);
	if (counter->camcount == 0)
		error_msg("No camera", -1);
	if (counter->camcount > 1)
		error_msg("Too many cameras", -1);
	if (counter->cycount + counter->plcount + counter->spcount > 50)
		error_msg("Too many objects in scene [max 50]", -1);
}

void	count_identifiers(int type, t_parsing *counter, int method)
{
	if (method == INIT)
	{
		counter->line = 0;
		counter->ambicount = 0;
		counter->camcount = 0;
		counter->lightcount = 0;
		counter->spcount = 0;
		counter->plcount = 0;
		counter->cycount = 0;
		return ;
	}
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
	error_msg("Unrecognized identifier (A, C, L, sp, cy, pl)", line);
	return (0);
}
