/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mngr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinel <jmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:24:41 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/28 17:49:05 by jmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	error_msg(char *msg, int line, t_scene *scene)
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
	free_all(scene);
	exit(EXIT_FAILURE);
	return (1);
}

void	free_all(t_scene *scene)
{
	t_light	*tmp_l;
	t_objs	*tmp_o;

	tmp_l = NULL;
	tmp_o = NULL;
	if (!scene)
		return ;
	while (scene->light)
	{
		tmp_l = scene->light->next;
		free (scene->light);
		scene->light = tmp_l;
	}
	while (scene->objs)
	{
		tmp_o = scene->objs->next;
		free(scene->objs);
		scene->objs = tmp_o;
	}
}

