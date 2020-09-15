/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_local_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 01:33:01 by wrhett            #+#    #+#             */
/*   Updated: 2020/09/15 17:57:29 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ft_illumination(int specular,
							t_vector *ray, t_vector *reflect, t_vector *norm)
{
	double	shade;
	double	shine;

	shine = 0.0;
	// ft_unit_vector(reflect); // Модель Блинна-Фонга
	shade = ft_vector_scalar(norm, ray);
	if (shade < 0)
		shade = 0;
	if (shade >= 0 && specular != 0)
	// shine = ft_vector_scalar(norm, reflect); // Модель Блинна-Фонга
		shine = ft_vector_scalar(ray, reflect);
	if (shine > 0)
		shade = shade + powf(shine, specular);
	return (shade);
}

void		is_point_shadow(t_rtv *p, t_vector *intersect, t_vector *ray,
							double *k_light)
{
	t_object	tmp;
	t_vector	new_start;
	double		len_light;
	double		len;
	int			n;

	len_light = ft_vector_modul(ray);
	ft_unit_vector(ray);
	new_start = ft_multiply_vector_num(intersect, 0.999);
	*k_light = 1;
	n = 0;
	while (NULL != p->object[n])
	{
		tmp = *p->object[n];
		object_data(&tmp, &new_start);
		len = ft_raytrace_objects(ray, &tmp);
		if ((0.001 < len && len < len_light) && len != NO_INTERSECT)
			*k_light *= tmp.refraction;
		n += 1;
	}
}

t_vector	ft_vector_light_cross(t_light *source, t_vector *cross)
{
	t_vector light_cross;

	if (source->tip == e_point)
		light_cross = ft_sub_vectors(&source->pos, cross);
	if (source->tip == e_direct)
		light_cross = source->pos;
	return (light_cross);
}

int			ft_calculate_lighting(t_rtv *p,
									t_vector *cross, t_vector *norm, int id)
{
	t_vector	light_cross;
	t_vector	reflect;
	t_light		*source;
	double		k_light;
	double		shade;

	shade = 0.0;
	source = p->light;
	while (source != NULL)
	{
		if (source->tip == e_ambient)
			shade += source->intensity;
		if (source->tip == e_point || source->tip == e_direct)
		{
			light_cross = ft_vector_light_cross(source, cross);
			reflect = ft_reflection_ray(cross, norm); // Model Fonga
			is_point_shadow(p, cross, &light_cross, &k_light);
			shade += source->intensity * k_light *
		ft_illumination(p->object[id]->specular, &light_cross, &reflect, norm);
		}
		source = source->next;
	}
	return (local_color(&p->object[id]->color, shade));
}

// int			is_point_shadow(t_rtv *p, t_vector *intersect, t_vector *ray)
// {
// 	t_object	tmp;
// 	t_vector	new_start;
// 	float		len_light;
// 	float		len;
// 	int			n;

// 	len_light = ft_vector_modul(ray);
// 	ft_unit_vector(ray);
// 	new_start = ft_multiply_vector_num(intersect, 0.999);
// 	n = 0;
// 	while (n < p->num)
// 	{
// 		tmp = *p->object[n];
// 		object_data(&tmp, &new_start);
// 		len = ft_raytrace_objects(ray, &tmp);
// 		if (len == -1 || len < 0.001 || len > len_light)
// 			n += 1;
// 		else
// 			return (SHADOW);
// 	}
// 	return (NO_SHADOW);
// }

// int			ft_calculate_lighting(t_rtv *p,
// 									t_vector *cross, t_vector *norm, int id)
// {
// 	t_vector	light_cross;
// 	t_vector	reflect;
// 	t_light		*source;
// 	double		shade;

// 	shade = 0.0;
// 	source = p->light;
// 	while (source != NULL)
// 	{
// 		if (source->tip == e_ambient)
// 			shade += source->intensity;
// 		if (source->tip == e_point || source->tip == e_direct)
// 		{
// 			light_cross = ft_vector_light_cross(source, cross);
// 			// reflect = ft_sub_vectors(&light_cross, cross); // Model Блинна-Fonga
// 			reflect = ft_reflection_ray(cross, norm); // Model Fonga
// 			if (is_point_shadow(p, cross, &light_cross) == NO_SHADOW)
// 				shade += source->intensity *
// 		ft_illumination(p->object[id]->specular, &light_cross, &reflect, norm);
// 		}
// 		source = source->next;
// 	}
// 	return (local_color(&p->object[id]->color, shade));
// }
