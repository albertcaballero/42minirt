/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:17:32 by alcaball          #+#    #+#             */
/*   Updated: 2024/01/15 18:59:35 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	add_objects(t_objs *objs, char **args, int type)
{
	t_objs	*temp;

	temp = objs;
	objs = ft_listlast_obj(objs);
	if (objs == NULL)
	{
		objs = malloc(sizeof(t_objs));
		init_type_obj(objs, args, type);
		objs->next = NULL;
		return ;
	}
	objs->next = malloc(sizeof(t_objs));
	objs = objs->next;
	init_type_obj(objs, args, type);
	objs->next = NULL;

}

void	init_type_obj(t_objs *obj, char **args, int type)
{
	if (type == SP)
	{
		if (ft_splitlen(args) != 4)
			error_msg("Sphere: invalid arguments");
		dprintf(2, "pppppfasd\n");
		obj->form.sp->diam = ft_atod(args[2]);
		obj->form.sp->pos = parse_vector(args[1]);
		obj->form.sp->col = parse_color(args[3]);
	}
	return ;
}
