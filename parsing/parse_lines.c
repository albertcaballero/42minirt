/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:03:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/01/15 13:18:39 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	check_identifiers(char *str)
{
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
	error_msg("Unrecognized identifier (A, C, L, sp, cy, pl)");
	return (0);
}
