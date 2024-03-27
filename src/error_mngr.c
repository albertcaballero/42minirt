/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mngr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:24:41 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/27 16:55:44 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	error_msg(char *msg, int line)
{
	write (2, "Error: ", 7);
	if (line >= 0)
	{
		ft_putstr_fd("on line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		write (2, "General Error\n", 15);
	//free_all
	exit(EXIT_FAILURE);
	return (1);
}
