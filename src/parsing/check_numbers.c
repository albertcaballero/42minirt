/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:44 by alcaball          #+#    #+#             */
/*   Updated: 2024/02/16 18:01:16 by alcaball         ###   ########.fr       */
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
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			i++;
			decim++;
			if (decim != f_decim)
				return (0);
		}
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	checkrng_int(char *str, int min, int max)
{
	int	num;

	if (check_numbers(str, 0) == 0)
		return (0);
	num = ft_atoi(str);
	if (num < min || num > max)
		return (0);
	return (1);
}

int	checkrng_double(char *str, double min, double max)
{
	double	num;

	if (check_numbers(str, 1) == 0)
		return (0);
	num = ft_atod(str);
	if (num < min || num > max)
		return (0);
	return (1);
}
