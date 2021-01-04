/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_color2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:31:29 by msole             #+#    #+#             */
/*   Updated: 2021/01/04 13:52:13 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		apply2(double shade, t_rtv *p, t_cross *in)
{
	t_color		texture_color;
	int			last_color;

	last_color = 0;
	if (p->object[in->id]->texture == PERLIN)
	{
		texture_color = makenoise_perlin(in, p->object[in->id]->perlin_tab, \
		&p->object[in->id]->color);
		last_color = color(&texture_color, shade);
	}
	else if (p->object[in->id]->texture == MARBLE)
	{
		texture_color = makenoise_marble(in, p->object[in->id]->perlin_tab, \
		&p->object[in->id]->color);
		last_color = color(&texture_color, shade);
	}
	else if (p->object[in->id]->texture == CHESS)
	{
		texture_color = ft_get_texture_color(p->object[in->id], in->vec3);
		last_color = color(&texture_color, shade);
	}
	return (last_color);
}

int		apply(double shade, t_rtv *p, t_cross *intersect)
{
	t_color		texture_color;
	int			last_color;

	last_color = 0;
	if (p->object[intersect->id]->texture == EARTH ||
		p->object[intersect->id]->texture == BLUR ||
		p->object[intersect->id]->texture == BRICS ||
		p->object[intersect->id]->texture == GRASS)
	{
		texture_color = get_color(p->object[intersect->id], intersect);
		last_color = color(&texture_color, shade);
	}
	else if (p->object[intersect->id]->texture == RAINBOW)
	{
		texture_color = 
	rainbow(p->object[intersect->id], intersect, &p->object[intersect->id]->color);
		last_color = color(&texture_color, shade);
	}
	else if (p->object[intersect->id]->texture == NO_TEXTURE)
		last_color = color(&p->object[intersect->id]->color, shade);
	return (last_color);
}

int		ft_local_color(t_rtv *p, t_cross *intersect, t_vector *norm)
{
	double		shade;
	t_color		filter;
	int			last_color;

	last_color = 0;
	shade = ft_calculate_lighting(p, intersect, norm);
	if (p->object[intersect->id]->texture == PERLIN ||
		p->object[intersect->id]->texture == MARBLE ||
		p->object[intersect->id]->texture == CHESS)
		last_color = apply2(shade, p, intersect);
	else
		last_color = apply(shade, p, intersect);
	if (p->filter == e_sepia)
		last_color = sepia(last_color);
	if (p->filter == e_wave)
	{
		filter = wave_pattern(&intersect->vec3, &p->object[intersect->id]->color);
		last_color = color(&filter, shade);
	}
	if (p->filter == e_cartoon)
	{
		filter = set_color_cartoon(p->object[intersect->id]->color, shade);
		last_color = color(&filter, shade);
	}
	return (last_color);
}
