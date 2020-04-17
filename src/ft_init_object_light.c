/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_object_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhail <mikhail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 23:58:08 by mikhail           #+#    #+#             */
/*   Updated: 2020/04/17 23:58:09 by mikhail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_light	*list_create(t_light *light, char **tab)
{
	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	if (ft_lentab(tab) != 5)
		ft_exit(ERR_OBJECT);
	init_coordinates(&light->pos, tab[1]);
	light->intensity = ft_atof(tab[2]);
	// light->color = ft_ahextocolor(tab[3]);
	init_color(&light->color,tab[3]);
	if (ft_strcmp(tab[4], "Point") == 0)
		light->tip = 'P';
	if (ft_strcmp(tab[4], "Direct") == 0)
		light->tip = 'D';
	light->next = NULL;
	return (light);
}

t_light			*init_light(t_light *light, char **tab)
{
	t_light *tmp;

	tmp = NULL;
	if (light == NULL)
		light = list_create(light, tab);
	else
	{
		tmp = list_create(tmp, tab);
		tmp->next = light;
		light = tmp;
	}
	return (light);
}
