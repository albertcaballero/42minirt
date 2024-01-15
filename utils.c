/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:21:47 by alcaball          #+#    #+#             */
/*   Updated: 2024/01/15 12:12:20 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_atod(char *str)
{
	int		i;
	long	numb;
	int		flag;

	i = 0;
	numb = 0;
	flag = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		flag = -2 * (str[i] == '-') + 1;
	while (str[i] >= 48 && str[i] <= 57)
	{
		numb = (numb * 10 + (str[i] - 48));
		i++;
	}
	return (numb * flag);
}
