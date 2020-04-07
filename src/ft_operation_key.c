/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 16:09:11 by wrhett            #+#    #+#             */
/*   Updated: 2020/04/06 01:40:53 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	solve_constant(t_rtv *p, t_vector *start)
{
	int n;
	
	p->light->pos = ft_subtraction_vector(&p->light->pos, start);
	n = 0;
	while (p->object[n] != NULL)
	{
		object_data(p->object[n], start);
		n += 1;
	}
}

void	look_2(int key, t_rtv *p)
{
	t_vector	start;

	start.x = 0;
	start.y = 0;
	start.z = 0;
	if (key == NUM_KEY_2)
		start.z -= K_ZOOM;
	else if (key == NUM_KEY_8)
		start.z += K_ZOOM;
	else if (key == NUM_KEY_1 || key ==  NUM_DOWN)
		start.y -= K_ZOOM;
	else if (key == NUM_KEY_7 || key ==  NUM_UP)
		start.y += K_ZOOM;
	else if (key == NUM_KEY_4 || key ==  NUM_LEFT)
		start.x -= K_ZOOM;
	else if (key == NUM_KEY_6 || key ==  NUM_RIGHT)
		start.x += K_ZOOM;
	p->camera->start.x += start.x;
	p->camera->start.y += start.y;
	p->camera->start.z += start.z;
	solve_constant(p, &start);
	ft_paint_scene(p);
}

void	look(int key, t_rtv *p)
{
	if (key == KEY_S)
		p->camera->angle.x -= K_DIR;
	else if (key == KEY_W)
		p->camera->angle.x += K_DIR;
	else if (key == KEY_A)
		p->camera->angle.y -= K_DIR;
	else if (key == KEY_D)
		p->camera->angle.y += K_DIR;
	ft_paint_scene(p);
}

void	zoom(int key, t_rtv *p)
{
	if (key == NUM_KEY_PLUS)
		p->width += K_FOV;
	else if (key == NUM_KEY_MINUS)
		p->width -= K_FOV;
	if (p->width <= 0)
		p->width = K_FOV;
	p->camera->dir.z = p->width;
	ft_paint_scene(p);
}

int		key_press(int key, t_rtv *p)
{
	t_vector	start;
	t_vector	tmp;

	if (key == KEY_ESC)
		exit(0);
	if (key == NUM_KEY_PLUS || key == NUM_KEY_MINUS)
		zoom(key, p);
	if (key == KEY_D || key == KEY_W || key == KEY_A || key == KEY_S)
		look(key, p);
	if (key ==  NUM_KEY_8 || key ==  NUM_KEY_2 || key == NUM_KEY_4 ||\
		key == NUM_KEY_6 || key == NUM_KEY_1 || key == NUM_KEY_7 ||\
		key ==  NUM_LEFT || key ==  NUM_RIGHT || key ==  NUM_UP ||\
		key ==  NUM_DOWN)
		look_2(key, p);
	if (key == KEY_SPACE)
	{
		start.x = 0;
		start.y = 0;
		start.z = -15;
		p->camera->angle.x = 0;
		p->camera->angle.y = 0;
		p->camera->angle.z = 0;
		tmp = start;
		start = ft_subtraction_vector(&start, &p->camera->start);
		p->camera->start = tmp;
		solve_constant(p, &start);
		ft_paint_scene(p);
	}
	return (0);
}
