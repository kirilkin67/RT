/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 16:09:11 by wrhett            #+#    #+#             */
/*   Updated: 2020/06/24 13:35:59 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	else if (key == KEY_Q)
		p->camera->angle.z += K_DIR;
	else if (key == KEY_E)
		p->camera->angle.z -= K_DIR;
	ft_paint_scene(p);
}

void	look_2(int key, t_rtv *p)
{
	t_vector	start;

	start.x = 0;
	start.y = 0;
	start.z = 0;
	if (key == NUM_KEY_2 || key == KEY_3)
		start.z -= K_ZOOM;
	else if (key == NUM_KEY_8 || key == KEY_2)
		start.z += K_ZOOM;
	else if (key == NUM_KEY_1 || key == KEY_DOWN)
		start.y -= K_ZOOM;
	else if (key == NUM_KEY_7 || key == KEY_UP)
		start.y += K_ZOOM;
	else if (key == NUM_KEY_4 || key == KEY_LEFT)
		start.x -= K_ZOOM;
	else if (key == NUM_KEY_6 || key == KEY_RIGHT)
		start.x += K_ZOOM;
	p->camera->start.x += start.x;
	p->camera->start.y += start.y;
	p->camera->start.z += start.z;
	calculate_constant(p, &start);
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

void	camera_start(t_rtv *p)
{
	t_vector	start;
	t_vector	tmp;

	start = p->camera->pos;
	p->camera->angle.x = 0;
	p->camera->angle.y = 0;
	p->camera->angle.z = 0;
	tmp = start;
	start = ft_subtraction_vector(&start, &p->camera->start);
	p->camera->start = tmp;
	calculate_constant(p, &start);
	ft_paint_scene(p);
}

int		key_press(int key, t_rtv *p)
{
	if (key == KEY_ESC)
		exit(0);
	if (key == NUM_KEY_PLUS || key == NUM_KEY_MINUS)
		zoom(key, p);
	if (key == KEY_D || key == KEY_W || key == KEY_A || key == KEY_S ||\
		key == KEY_Q || key == KEY_E)
		look(key, p);
	if (key == NUM_KEY_8 || key == NUM_KEY_2 || key == NUM_KEY_4 ||\
		key == NUM_KEY_6 || key == NUM_KEY_1 || key == NUM_KEY_7 ||\
		key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP ||\
		key == KEY_DOWN || key == KEY_2 || key == KEY_3)
		look_2(key, p);
	if (key == KEY_SPACE)
		camera_start(p);
	return (0);
}

int		mouse_press(int button, int x, int y, t_rtv *p)
{
	if (y >= 0 && y <= (HIGHT - 1) && x >= 0 && x <= (WIDHT - 1))
	{
		if (button == 1)
		{
			// printf("X- %d P->X- %d\n", x, p->x0);
			p->camera->angle.y += asin((double)(x - p->x0) / p->width);
			// printf("Angle_X- %f\n", p->camera->angle.y);
			p->camera->angle.x += asin((double)(p->y0 - y) / p->width);
		}
	}
	ft_paint_scene(p);
	return (0);
}
