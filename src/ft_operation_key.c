/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 16:09:11 by wrhett            #+#    #+#             */
/*   Updated: 2020/11/01 20:10:04 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** New look for mouse camera direction
*/

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
	ft_rotate_vector(&p->camera->angle, &start); // перемещение 
	p->camera->start.x += start.x;
	p->camera->start.y += start.y;
	p->camera->start.z += start.z;
	calculate_constant(p, &start);
	ft_paint_scene(p);
}

void	zoom(int key, t_rtv *p)
{
	int width;
	
	width = p->width;
	if (key == NUM_KEY_PLUS)
		p->fov += K_FOV;
	else if (key == NUM_KEY_MINUS)
		p->fov -= K_FOV;
	if (p->fov <= 0)
		p->fov = K_FOV;
	p->camera->dir.z = p->fov;
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
	start = ft_sub_vectors(&start, &p->camera->start);
	p->camera->start = tmp;
	calculate_constant(p, &start);
	p->fov = (double)p->width;
	p->depth_mirror = DEPTH_REFL;
	p->samples = MIN_SAMPLE;
	ft_paint_scene(p);
}

// void	camera_start_2(t_rtv *p)
// {
// 	// t_vector	start;
// 	// t_vector	tmp;
// 	free_memory(p);
// 	init_tab_object(p, p->name_file);
// 	calculate_constant(p, &p->camera->start);
// 	p->fov = (double)p->width;
// 	p->depth_mirror = 1;
// 	ft_paint_scene(p);
// }

void	reflect(t_rtv *p)
{
	p->depth_mirror += 1;
	if (p->depth_mirror == DEPTH)
		p->depth_mirror = 1;
	ft_paint_scene(p);
}

void	aliasing_effects(t_rtv *p)
{
	if (p->samples < MAX_SAMPLE)
		p->samples += 1;
	else
		p->samples = MIN_SAMPLE;
	ft_paint_scene(p);
}

void effects(int key, t_rtv *p)
{
	if (key == KEY_O)
		p->filter = 'O'; //sepia
	if (key == KEY_T)
		p->filter = 'S'; // cartoon
	if (key == KEY_B)
		p->filter = 'B'; //motion_blur
	if (key == KEY_L)
		p->filter = 'X'; //wave
	if (key == KEY_M)
		p->filter = 'D'; //color_to_anaglyph
	ft_paint_scene(p);
}

void	ft_move_object(int key, t_rtv *p)
{
	int num;
	t_vector move;

	move = (t_vector){0, 0, 0};
	num = p->selected_obj;
	if (key == NUM_KEY_8)
		p->object[num]->pos.z += K_MOVE;
	else if (key == NUM_KEY_2)
		p->object[num]->pos.z -= K_MOVE;
	else if (key == NUM_KEY_6)
		p->object[num]->pos.x += K_MOVE;
	else if (key == NUM_KEY_4)
		p->object[num]->pos.x -= K_MOVE;
	else if (key == NUM_KEY_7)
		p->object[num]->pos.y += K_MOVE;
	else if (key == NUM_KEY_1)
		p->object[num]->pos.y -= K_MOVE;
	object_data(p->object[num], &move);
	ft_paint_scene(p);
	
}

int		key_press(int key, t_rtv *p)
{
	if (key == KEY_ESC)
		close_window(p);
	if (key == NUM_KEY_PLUS || key == NUM_KEY_MINUS)
		zoom(key, p);
	if (key == KEY_Q || key == KEY_W || key == KEY_E || key == KEY_A ||
	key == KEY_S || key == KEY_D || key == KEY_LEFT || key == KEY_RIGHT ||
	key == KEY_UP || key == KEY_DOWN)
		look(key, p);
	if (key == KEY_M)
		reflect(p);
	if (key == KEY_N || key == KEY_C)
		aliasing_effects(p);
	if (key == KEY_O || key == KEY_T || key == KEY_B || key == KEY_L || key == KEY_M)
		effects(key, p);
	if (key == KEY_P)
		// save_ppm_file(p);
		save_bmp_file(p);
	if (key == KEY_SPACE)
		camera_start(p);
	if (key == KEY_H)
		ft_window_menu(p);
	if ((key == NUM_KEY_8 || key == NUM_KEY_2 || key == NUM_KEY_4 ||
	key == NUM_KEY_6 || key == NUM_KEY_1 || key == NUM_KEY_7) && 
		p->selected_obj != NO_INTERSECT)
		ft_move_object(key, p);
	return (0);
}
