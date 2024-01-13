/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mngr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:24:41 by alcaball          #+#    #+#             */
/*   Updated: 2024/01/13 13:27:33 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	error_msg(char *msg)
{
	write (2, "Error\n", 7);
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		write (2, "General Error\n", 15);
	return (1);
}
