/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:14:00 by alcaball          #+#    #+#             */
/*   Updated: 2024/03/27 12:14:44 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	init_lights(t_scene *scene, char **args)
{
	t_light	*temp;

	if (ft_splitlen(args) != 4)
		error_msg("Light: invalid argument count [3]");
	if (!scene->light)
	{
		scene->light = my_malloc(sizeof(t_light));
		temp = scene->light;
	}
	else
	{
		temp = scene->light;
		while (scene->light->next)
			scene->light = scene->light->next;
		scene->light->next = my_malloc(sizeof(t_light));
		scene->light = scene->light->next;
	}
	scene->light->pos = parse_vector(args[1]);
	scene->light->ratio = ft_atod(args[2]);
	scene->light->color = parse_color(args[3]);
	scene->light->next = NULL;
	scene->light = temp;
}
