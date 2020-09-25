/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_vector_normal.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 18:44:44 by wrhett            #+#    #+#             */
/*   Updated: 2020/09/25 17:20:25 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	vector_norm_cylindr(t_object *object, t_vector *intersect)
{
	t_vector	norm;
	t_vector	v_norm;
	double		len_ray;

	norm = ft_sub_vectors(intersect, &object->pos);
	len_ray = ft_vector_projection_on_ray(&norm, &object->norm_p);
	v_norm = ft_multiply_vector_num(&object->norm_p, len_ray);
	norm = ft_sub_vectors(&norm, &v_norm);
	ft_unit_vector(&norm);
	return (norm);
}

t_vector	vector_norm_cone(t_object *object, t_vector *intersect)
{
	t_vector	normal;
	t_vector	v_normal;
	double		len_ray;
	double		half_angle;

	half_angle = cos(0.5 * object->angle);
	normal = ft_sub_vectors(intersect, &object->pos);
	len_ray = ft_vector_projection_on_ray(&normal, &object->norm_p);
	len_ray = len_ray / (half_angle * half_angle);
	v_normal = ft_multiply_vector_num(&object->norm_p, len_ray);
	normal = ft_sub_vectors(&normal, &v_normal);
	ft_unit_vector(&normal);
	return (normal);
}

t_vector	vector_norm_sphere(t_object *object, t_vector *intersect)
{
	t_vector	normal;

	normal = ft_sub_vectors(intersect, &object->pos);
	ft_unit_vector(&normal);
	return (normal);
}

t_vector	vector_norm_hemisphere(t_object *object, t_vector *intersect)
{
	t_vector	normal;
	double		len_normal;

	normal = ft_sub_vectors(intersect, &object->pos);
	len_normal = ft_vector_modul(&normal);
	if (object->radius - len_normal > 0.001)
		normal = object->norm_p;

	// if (object->check == e_body)
	// 	normal = ft_sub_vectors(intersect, &object->pos);
	// else
	// 	normal = object->norm_p;

	ft_unit_vector(&normal);
	return (normal);
}

t_vector	calculate_vector_norm(t_object *object, t_vector *intersect)
{
	t_vector	norm;

	if (object->tip == e_plane)
		norm = object->norm_p;
	if (object->tip == e_sphere)
		norm = vector_norm_sphere(object, intersect);
	if (object->tip == e_cylindr)
		norm = vector_norm_cylindr(object, intersect);
	if (object->tip == e_cone)
		norm = vector_norm_cone(object, intersect);
	if (object->tip == e_hemisphere)
		norm = vector_norm_hemisphere(object, intersect);
	return (norm);
}

// t_vector	ft_calculate_vector_norm(t_object *object, t_vector *intersect)
// {
// 	t_vector	norm;
// 	t_vector	v_norm;
// 	double		len_ray;

// 	if (object->id == 'P')
// 		norm = object->norm_p;
// 	if (object->id == 'S' || object->id == 'C' || object->id == 'K')
// 	{
// 		norm = ft_sub_vectors(intersect, &object->pos);
// 		if (object->id == 'C' || object->id == 'K')
// 		{
// 			len_ray =
// 			ft_vector_projection_on_ray(&norm, &object->norm_p);
// 			if (object->id == 'K')
// 				len_ray = len_ray /(cos(0.5 * object->angle) *
// 				cos(0.5 * object->angle));
// 			v_norm = ft_multiply_vector_num(&object->norm_p, len_ray);
// 			norm = ft_subtraction_vector(&norm, &v_norm);
// 		}
// 		ft_unit_vector(&norm);
// 	}
// 	return (norm);
// }

// t_vector	ft_calculate_vector_norm(t_rtv *p, int id, t_vector *intersect)
// {
// 	t_vector	norm;
// 	t_vector	v_norm;
// 	double		len_ray;

// 	if (p->object[id]->id == 'P')
// 		norm = p->object[id]->norm_p;
// 	if (p->object[id]->id == 'S' || p->object[id]->id == 'C' ||
// 			p->object[id]->id == 'K')
// 	{
// 		norm = ft_sub_vectors(intersect, &p->object[id]->pos);
// 		if (p->object[id]->id == 'C' || p->object[id]->id == 'K')
// 		{
// 			len_ray =
// 			ft_vector_projection_on_ray(&norm, &p->object[id]->norm_p);
// 			if (p->object[id]->id == 'K')
// 				len_ray = len_ray /(cos(0.5 * p->object[id]->angle) *
// 				cos(0.5 * p->object[id]->angle));
// 			v_norm = ft_multiply_vector_num(&p->object[id]->norm_p, len_ray);
// 			norm = ft_sub_vectors(&norm, &v_norm);
// 		}
// 		ft_unit_vector(&norm);
// 	}
// 	return (norm);
// }
