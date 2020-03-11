#include "rtv1.h"

float		ft_ray_trace_object(t_vector *ray, t_object *obj)
{
	float		len_dist;

		if (obj->id == 'S')
			len_dist = ft_intersect_ray_sphere(ray, obj);
		if (obj->id == 'P' && obj->pos_cam < 0.001)
			len_dist = ft_intersect_ray_plane(ray, obj);
		if (obj->id == 'C')
			len_dist = ft_intersect_ray_cilinder(ray, obj);
		if (obj->id == 'K')
			len_dist = ft_intersect_ray_cone(ray, obj);
		return (len_dist);
}

void	ft_intersection_object(t_vector *ray, t_object **obj, int *id, float *min_dist)
{
	int		n;
	float	len_dist;

	*id = -1;
	*min_dist = INT_MAX;
	n = 0;
	while (obj[n] != NULL)
	{
		len_dist = ft_ray_trace_object(ray, obj[n]);
		if (len_dist != -1 && len_dist > 0.001f && len_dist < *min_dist)
		{
			*min_dist = len_dist;
			*id = n;
		}
		n += 1;
	}
}

int		ft_light_object(t_rtv *p, t_vector *ray, t_object **obj, t_light *l)
{
	t_vector	interset;
	t_vector	v_norm;
	float		len_ray;
	int			color;
	int			id;
	float		min_dist;

	ft_intersection_object(ray, obj, &id, &min_dist);
	if (id == -1)
		return (0x0);
	interset = ft_multiply_vector_num(ray, min_dist);
	if (obj[id]->id == 'S' || obj[id]->id == 'C'|| obj[id]->id == 'K')
	{
		obj[id]->norm = ft_subtraction_vector(&interset, &obj[id]->pos);
		if (obj[id]->id == 'C'|| obj[id]->id == 'K')
		{
			len_ray = ft_vector_projection_on_ray(&obj[id]->norm, &obj[id]->norm_p);
			if (obj[id]->id == 'K')
				len_ray = len_ray / pow(cos(0.5 * obj[id]->angle), 2);
			v_norm = ft_multiply_vector_num(&obj[id]->norm_p, len_ray);
			obj[id]->norm = ft_subtraction_vector(&obj[id]->norm, &v_norm);
		}
		ft_unit_vector(&obj[id]->norm);
	}
	color = illuminat_point(l, obj, &interset, id);
	return (color);
}

void	paint_object(t_rtv *p, t_camera *cam, t_object **obj, t_light *l)
{
	int	x;
	int	y;
	int	pixel_color;
	t_vector	ray;

	p->x0 = WIDHT / 2.0;
	p->y0 = HIGHT / 2.0;
	y = 0;
	while (y < HIGHT)
	{
		x = 0;
		while (x < WIDHT)
		{
			cam->dir.x = (float)x - p->x0;
			cam->dir.y = p->y0 - (float)y;
			ray = cam->dir;
			ft_rotat_vector(&p->angle, &ray);
			// ray = ft_rotation_vector(&p->angle, &cam->dir);
			ft_unit_vector(&ray);
			pixel_color = ft_light_object(p, &ray, obj, l);
			p->draw[x + y * WIDHT] = pixel_color;
			x += 1;
		}
		y += 1;
	}
}

void	*thread_paint_object(void *param)
{
	int			x;
	int			pixel_color;
	t_vector	ray;
	t_rtv		*data;

	data = (t_rtv *)param;
	while (data->y_start < data->y_end)
	{
		x = 0;
		while (x < WIDHT)
		{
			data->camera.dir.x = (float)x - data->x0;
			data->camera.dir.y = data->y0 - (float)data->y_start;
			ray = ft_rotation_vector(&data->angle, &data->camera.dir);
			ft_unit_vector(&ray);
			pixel_color = ft_light_object(data, &ray, data->object, &data->light);
			data->draw[x + data->y_start * WIDHT] = pixel_color;
			x += 1;
		}
		data->y_start += 1;
	}
	return (param);
}

void	ft_multi_thread_paint(t_rtv *paint)
{
	pthread_t	id[NUM_THREAD];
	t_rtv		data[NUM_THREAD];
	size_t		n;

	n = 0;
	while (n < NUM_THREAD)
	{
		// data[n] = *paint;
		ft_memcpy((void *)&data[n], (void *)paint, sizeof(t_rtv));
		data[n].y_start = n * HIGHT / NUM_THREAD;
		data[n].y_end = (n + 1) * HIGHT / NUM_THREAD;
		pthread_create(&id[n], NULL, thread_paint_object, &data[n]);
		n += 1;
	}
	n = 0;
	while (n < NUM_THREAD)
	{
		pthread_join(id[n], NULL);
		n += 1;
	}
	// mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
}
