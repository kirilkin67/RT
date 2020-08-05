/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_local_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 01:33:01 by wrhett            #+#    #+#             */
/*   Updated: 2020/07/27 20:37:33 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		is_point_shadow(t_rtv *p, t_vector *intersect, t_vector *ray)
{
	t_object	tmp;
	t_vector	new_start;
	float		len_light;
	float		len;
	int			n;

	len_light = ft_vector_modul(ray);
	ft_unit_vector(ray);
	new_start = ft_multiply_vector_num(intersect, 0.9);
	n = 0;
	while (n < p->num)
	{
		tmp = *p->object[n];
		object_data(&tmp, &new_start);
		len = ft_ray_trace_object(ray, &tmp);
		if (len == -1 || len < 0.001 || len > len_light)
			n += 1;
		else
			return (SHADOW);
	}
	return (NO_SHADOW);
}

double	ft_illumination(int s, t_vector *ray, t_vector *median, t_vector *norm)
{
	double	shade;
	double	shine;

	shine = 0.0;
	ft_unit_vector(median);
	shade = ft_vector_scalar(norm, ray);
	if (shade < 0)
		shade = 0;
	if (shade != 0)
		shine = ft_vector_scalar(norm, median);
	if (shine < 0)
		shine = 0;
	shade = shade + powf(shine, s);
	return (shade);
}

int		ft_calculate_lighting(t_rtv *p, t_vector *cross, t_vector *norm, int n)
{
	t_vector	light_cross;
	t_vector	median;
	t_light		*source;
	double		shade;

	shade = 0.0;
	source = p->light;
	while (source != NULL)
	{
		if (source->tip == 'A')
			shade += source->intensity;
		if (source->tip == 'P' || source->tip == 'D')
		{
			if (source->tip == 'P')
				light_cross = ft_subtraction_vector(&source->pos, cross);
			if (source->tip == 'D')
				light_cross = source->pos;
			median = ft_subtraction_vector(&light_cross, cross);
			if (is_point_shadow(p, cross, &light_cross) == NO_SHADOW)
				shade += source->intensity \
		* ft_illumination(p->object[n]->specular, &light_cross, &median, norm);
		}
		source = source->next;
	}
	return (local_color(&p->object[n]->color, shade));
}

// t_vector	ft_vector_light_cross(t_light *source, t_vector *cross)
// {
// 	t_vector light_cross;

// 	if (source->tip == 'P')
// 		light_cross = ft_subtraction_vector(&source->pos, cross);
// 	if (source->tip == 'D')
// 		light_cross = source->pos;
// 	return (light_cross);
// }

// int		ft_calculate_lighting(t_rtv *p, t_vector *cross, t_vector *norm, int n)
// {
// 	t_vector	new_ray;
// 	t_vector	median;
// 	t_light		*source;
// 	float		shade;

// 	shade = 0.0;
// 	source = p->light;
// 	while (source != NULL)
// 	{
// 		if (source->tip == 'A')
// 		{
// 			shade += source->intensity;
// 			source = source->next;
// 		}
// 		if (source->tip == 'P')
// 			new_ray = ft_subtraction_vector(&source->pos, cross);
// 		if (source->tip == 'D')
// 			new_ray = source->pos;
// 		median = ft_subtraction_vector(&new_ray, cross);
// 		if (is_point_shadow(p, cross, &new_ray) == SHADOW)
// 			source = source->next;
// 		else
// 		{
// 			shade += source->intensity \
// 			* ft_illumination(p->object[n]->specular, &new_ray, &median, norm);
// 			source = source->next;
// 		}
// 	}
// 	return (local_color(&p->object[n]->color, shade));
// }
