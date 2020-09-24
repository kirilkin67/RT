/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 01:33:01 by wrhett            #+#    #+#             */
/*   Updated: 2020/09/24 12:07:46 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		illumination(int specular,
					t_vector *ray, t_vector *reflect, t_vector *norm)
{
	double	shade;
	double	shine;

	shine = 0.0;
	shade = ft_vector_scalar(norm, ray);
	if (shade < 0)
		shade = 0;
	if (shade >= 0 && specular != 0)
		shine = ft_vector_scalar(ray, reflect);
	if (shine > 0)
		shade = shade + powf(shine, specular);
	return (shade);
}

double		is_point_shadow(t_object **object,
	t_vector *intersect, t_vector *ray, double *k_light)
{
	t_object	tmp;
	t_vector	new_start;
	double		len_light;
	double		len;
	int			n;

	len_light = ft_vector_modul(ray);
	ft_unit_vector(ray);
	// new_start = ft_multiply_vector_num(intersect, 0.999);
	new_start = new_start_vector(intersect, ray, 0.001);
	*k_light = 1.0;
	n = 0;
	while (NULL != object[n])
	{
		tmp = *object[n];
		object_data(&tmp, &new_start);
		len = ft_raytrace_objects(ray, &tmp);
		if ((0.001 < len && len < len_light) && len != NO_INTERSECT)
		{
			*k_light *= tmp.refraction;
			if (tmp.refraction == 0)
				return (*k_light);
		}
		n += 1;
	}
	return (*k_light);
}

t_vector	ft_vector_light_cross(t_light *source, t_vector *intersect)
{
	t_vector light_cross;

	if (source->tip == e_point)
		light_cross = ft_sub_vectors(&source->pos, intersect);
	if (source->tip == e_direct)
		light_cross = source->pos;
	return (light_cross);
}

double		ft_calculate_lighting(t_rtv *p,
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
			k_light = is_point_shadow(p->object, cross, &light_cross, &k_light);
			shade += source->intensity * k_light *
		illumination(p->object[id]->specular, &light_cross, &reflect, norm);
		}
		source = source->next;
	}
	return (shade);
}

int			ft_local_color(t_rtv *p, t_vector *cross, t_vector *norm, int id)
{
	double		shade;

	shade = ft_calculate_lighting(p, cross, norm, id);
	return (color(&p->object[id]->color, shade));
}

// int			ft_calculate_lighting(t_rtv *p,
// 								t_vector *intersect, t_vector *norm, int id)
// {
// 	t_vector	light_cross;
// 	t_vector	reflect;
// 	t_light		*source;
// 	double		k_light;
// 	double		shade;

// 	shade = 0.0;
// 	source = p->light;
// 	while (source != NULL)
// 	{
// 		if (source->tip == e_ambient)
// 			shade += source->intensity;
// 		if (source->tip == e_point || source->tip == e_direct)
// 		{
// 			light_cross = ft_vector_light_cross(source, intersect);
// 			reflect = ft_reflection_ray(intersect, norm); // Model Fonga
// 			is_point_shadow(p->object, intersect, &light_cross, &k_light);
// 			shade += source->intensity * k_light *
// 		ft_illumination(p->object[id]->specular, &light_cross, &reflect, norm);
// 		}
// 		source = source->next;
// 	}
// 	return (color(&p->object[id]->color, shade));
// }

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
