/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_key_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:26:26 by msole             #+#    #+#             */
/*   Updated: 2021/01/24 16:17:08 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	zoom(int key, t_rtv *p)
{
	int	width;

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
	p->filter = e_no_effect;
	ft_paint_scene(p);
}

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