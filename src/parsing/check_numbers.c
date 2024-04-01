/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:44 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/28 17:10:08 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_numbers(char *str, int f_decim)
{
	int	i;
	int	decim;

	i = 0;
	decim = 0;
	if (!str)
		return (ERROR);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			i++;
			decim++;
			if (decim != f_decim)
				return (ERROR);
		}
		if (ft_isdigit(str[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (OK);
}

int	checkrng_int(char *str, int min, int max)
{
	int	num;

	if (check_numbers(str, 0) == ERROR)
		return (ERROR);
	num = ft_atoi(str);
	if (num < min || num > max)
		return (ERROR);
	return (OK);
}

int	checkrng_dbl(char *str, double min, double max)
{
	double	num;

	if (check_numbers(str, 1) == ERROR)
		return (ERROR);
	num = ft_atod(str);
	if (num < min || num > max)
		return (ERROR);
	return (OK);
}
