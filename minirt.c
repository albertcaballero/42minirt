/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:06:29 by alcaball          #+#    #+#             */
/*   Updated: 2024/01/15 18:21:30 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;

	scene = malloc(sizeof(*scene));
	scene->objs = NULL;
	if (argc != 2)
		return (error_msg("invalid argc"));
	if (open_map(argv[1], scene) < 0)
		return (error_msg("invalid argc"));
}
