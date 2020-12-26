/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:26:31 by msole             #+#    #+#             */
/*   Updated: 2020/12/26 18:52:24 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	effects(int key, t_rtv *p)
{
	if (key == KEY_O)
		p->filter = e_sepia;
	if (key == KEY_I)
		p->filter = e_cartoon;
	if (key == KEY_U)
		p->filter = e_motion_bler;
	if (key == KEY_Y)
		p->filter = e_anaglyph;
	if (key == KEY_T)
		p->filter = e_wave;
	ft_paint_scene(p);
}

void	paint_next_scene(int key, t_rtv *paint)
{
	if (key == PGUP)
	{
		if (paint->current_scene == 1)
			paint->current_scene = paint->scene_num;
		else
			paint->current_scene -= 1;
	}
	if (key == PGDN)
	{
		if (paint->current_scene == paint->scene_num)
			paint->current_scene = 1;
		else
			paint->current_scene += 1;
	}
	mlx_destroy_window(paint->mlx_ptr, paint->win_ptr);
	paint->name_file = paint->scenes[paint->current_scene];
	free_memory(paint);
	read_file(paint, paint->name_file);
	ft_init_configuration(paint);
	ft_init_texture(paint);
	calculate_constant(paint, &paint->camera->start);
	ft_paint_scene(paint);
	ft_hook_operation(paint);
}

void	key_press_next(int key, t_rtv *p)
{
	if (key == KEY_M)
		reflect(p);
	if (key == KEY_N || key == KEY_C)
		aliasing_effects(p);
	if (key == KEY_O || key == KEY_I || key == KEY_U || key == KEY_Y ||
	key == KEY_T)
		effects(key, p);
	if (key == KEY_SPACE)
		camera_start(p);
	if (key == SHIFT_L)
	{
		if (p->visual_effect == e_pull)
			p->visual_effect = e_push;
		else
			p->visual_effect = e_pull;
	}
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
	if (key == KEY_H)
		ft_window_menu(p);
	if ((key == NUM_KEY_8 || key == NUM_KEY_2 || key == NUM_KEY_4 ||
	key == NUM_KEY_6 || key == NUM_KEY_1 || key == NUM_KEY_7) &&
		p->selected_obj != NO_INTERSECT)
		ft_move_object(key, p);
	if (key == PGUP || key == PGDN)
		paint_next_scene(key, p);
	if (key == KEY_P)
		save_bmp_file(p);
	key_press_next(key, p);
	return (0);
}
