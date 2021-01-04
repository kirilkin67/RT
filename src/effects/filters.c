/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:25:31 by msole             #+#    #+#             */
/*   Updated: 2021/01/04 13:22:45 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	integer_to_rgb(int color)
{
	return (t_color){(color >> 16) & 255, (color >> 8) & 255, color & 255};
}

t_color			wave_pattern(t_vector *intersect, t_color *color_figure)
{
	double coord_x;
	double coord_y;
	double sinus;

	coord_x = intersect->x * 100;
	coord_y = intersect->y * 100;
	sinus = sin(coord_x * 1.51 + coord_y * 0.502);
	if (sinus < 0)
		return (*color_figure);
	else
		return (integer_to_rgb(COLOR_BG_BL));
}

t_color			set_color_cartoon(t_color color, double light)
{
	t_color new_color;

	if (light < 0.3)
		light = 0.3;
	else if (light < 0.7)
		light = 0.7;
	else
		light = 1.0;
	new_color.red = color.red * light;
	new_color.green = color.green * light;
	new_color.blue = color.blue * light;
	return (new_color);
}
