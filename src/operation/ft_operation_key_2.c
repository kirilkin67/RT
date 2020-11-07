/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_key_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msole <msole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:26:26 by msole             #+#    #+#             */
/*   Updated: 2020/11/07 10:43:46 by msole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	look(int key, t_rtv *p)
{
	t_vector	start;

	start.x = 0;
	start.y = 0;
	start.z = 0;
	if (key == KEY_S || key == 5)
		start.z -= K_ZOOM;
	else if (key == KEY_W || key == 4)
		start.z += K_ZOOM;
	else if (key == KEY_Q || key == KEY_DOWN)
		start.y -= K_ZOOM;
	else if (key == KEY_E || key == KEY_UP)
		start.y += K_ZOOM;
	else if (key == KEY_A || key == KEY_LEFT)
		start.x -= K_ZOOM;
	else if (key == KEY_D || key == KEY_RIGHT)
		start.x += K_ZOOM;
	ft_rotate_vector(&p->camera->angle, &start);
	p->camera->start.x += start.x;
	p->camera->start.y += start.y;
	p->camera->start.z += start.z;
	calculate_constant(p, &start);
	ft_paint_scene(p);
}
