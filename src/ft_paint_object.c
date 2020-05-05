/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 00:01:49 by mikhail           #+#    #+#             */
/*   Updated: 2020/05/06 00:39:13 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ft_ray_trace_object(t_vector *ray, t_object *obj)
{
	double		len_dist;

	len_dist = -1;
	if (obj->id == 'S')
		len_dist = ft_intersect_ray_sphere(ray, obj);
	if (obj->id == 'P')// && obj->pos_cam < 0.001)
		len_dist = ft_intersect_ray_plane(ray, obj);
	if (obj->id == 'C')
		len_dist = ft_intersect_ray_cilinder(ray, obj);
	if (obj->id == 'K')
		len_dist = ft_intersect_ray_cone(ray, obj);
	return (len_dist);
}

void	ft_intersect_obj(t_rtv *p, t_vector *ray, int *id, double *min_dist)
{
	int		n;
	double	len_dist;

	*id = -1;
	*min_dist = INT_MAX;
	n = 0;
	while (n < p->num)
	{
		len_dist = ft_ray_trace_object(ray, p->object[n]);
		if (len_dist != -1 && len_dist > 0.001f && len_dist < *min_dist)
		{
			*min_dist = len_dist;
			*id = n;
		}
		n += 1;
	}
}

t_vector	calculate_vector_norm(t_rtv *p, int id, t_vector *intersect)
{
	t_vector	norm;
	t_vector	v_norm;
	double		len_ray;

	if (p->object[id]->id == 'P')
		norm = p->object[id]->norm_p;
	if (p->object[id]->id == 'S' || p->object[id]->id == 'C'|| p->object[id]->id == 'K')
	{
		norm = ft_subtraction_vector(intersect, &p->object[id]->pos);
		if (p->object[id]->id == 'C'|| p->object[id]->id == 'K')
		{
			len_ray = ft_vector_projection_on_ray(&norm, &p->object[id]->norm_p);
			if (p->object[id]->id == 'K')
				len_ray = len_ray / pow(cos(0.5 * p->object[id]->angle), 2);
			v_norm = ft_multiply_vector_num(&p->object[id]->norm_p, len_ray);
			norm = ft_subtraction_vector(&norm, &v_norm);
		}
		ft_unit_vector(&norm);
	}
	return (norm);
}

int		ft_light_object(t_rtv *p, t_vector *ray)
{
	t_vector	intersect;
	t_vector	norm;
	int			id;
	double		min_dist;
	int 		local_color;
	int 		reflect_color = 0;

	ft_intersect_obj(p, ray, &id, &min_dist);
	if (id == -1)
		return (COLOR_BG);
	intersect = ft_multiply_vector_num(ray, min_dist);
	norm = calculate_vector_norm(p, id, &intersect);
	local_color = ft_calculate_lighting(p, &intersect, &norm, id);
	if (p->object[id]->reflection > 0)
		reflect_color = ft_calculate_reflection(p, &intersect, &norm);
	if (reflect_color > 0 )
		local_color = reflection_color(local_color, reflect_color, p->object[id]->reflection);

	return (local_color);
}

void	*thread_paint_object(void *param)
{
	t_data		*data;
	t_vector	ray;
	int			color;

	data = (t_data *)param;
	while (data->y_start < data->y_end)
	{
		data->x = 0;
		while (data->x < WIDHT)
		{
			data->camera.dir.x = (double)data->x - data->x0;
			data->camera.dir.y = data->y0 - (double)data->y_start;
			ray = data->camera.dir;
			ray = ft_rotation_vector(&data->all->camera->angle, &ray);
			ft_unit_vector(&ray);
			color = ft_light_object(data->all, &ray);
			data->all->draw[data->x + data->y_start * WIDHT] = color;
			data->x += 1;
		}
		data->y_start += 1;
	}
	return (NULL);
}

void	ft_multi_thread_paint(t_rtv *p)
{
	pthread_t	id[NUM_THREAD];
	t_data		data[NUM_THREAD];
	size_t		n;

	n = 0;
	while (n < NUM_THREAD)
	{
		data[n].all = p;
		data[n].camera.dir.z = p->width;
		data[n].y_start = n * HIGHT / NUM_THREAD;
		data[n].y_end = (n + 1) * HIGHT / NUM_THREAD;
		data[n].x0 = (double)WIDHT / 2.0;
		data[n].y0 = (double)HIGHT / 2.0;
		pthread_create(&id[n], NULL, thread_paint_object, &data[n]);
		n += 1;
	}
	n = 0;
	while (n < NUM_THREAD)
	{
		pthread_join(id[n], NULL);
		n += 1;
	}
}

void	ft_paint_object(t_rtv *p)
{
	int	x;
	int	y;
	int	pixel_color;
	t_vector	ray;

	y = 0;
	while (y < HIGHT)
	{
		x = 0;
		while (x < WIDHT)
		{
			p->camera->dir.x = (float)(x - p->x0);
			p->camera->dir.y = (float)(p->y0 - y);
			// ray = p->camera->dir;
			// ft_rotat_vector(&p->camera->angle, &ray);
			ray = ft_rotation_vector(&p->camera->angle, &p->camera->dir);
			ft_unit_vector(&ray);
			pixel_color = ft_light_object(p, &ray);
			p->draw[x + y * WIDHT] = pixel_color;
			x += 1;
		}
		y += 1;
	}
}
