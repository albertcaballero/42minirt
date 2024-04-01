/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:21:47 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/28 17:19:47 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	ft_atod(char *str)
{
	double	numb;
	double	flag;
	int		i;
	int		j;

	i = 0;
	j = 1;
	flag = 1;
	numb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			flag = -1.0;
	}
	while (str[i] >= 48 && str[i] <= 57)
		numb = (numb * 10 + (double)(str[i++] - 48));
	if (str[i] != '.')
		return (numb * flag);
	i++;
	while (str[i] >= 48 && str[i] <= 57 && j < 8)
		numb += (double)(str[i++] - 48) / pow(10, j++);
	return (numb * flag);
}

t_objs	*ft_listlast_obj(t_objs *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

int	ft_clamp(int val1, int lim, int type)
{
	if (type == MAX && val1 >= lim)
		return (lim);
	if (type == MIN && val1 <= lim)
		return (lim);
	return (val1);
}

//mallocs a value and if return is NULL exits program
void	*my_malloc(size_t size)
{
	void	*thing;

	thing = malloc(size);
	if (thing == NULL)
	{
		write(2, "malloc error\n", 14);
		exit (1);
	}
	return (thing);
}
