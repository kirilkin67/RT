#include "rtv1.h"

int		ft_intersect_obj(t_rtv *p, t_vector *ray, t_vector *start, double *dist)
{
	t_object	tmp;
	int			id;
	int			n;
	double		len_dist;

	id = NO_INTERSECT;
	*dist = INT_MAX;
	n = 0;
	while (NULL != p->object[n])
	{
		tmp = *p->object[n];
		if (start != NULL)
			object_data(&tmp, start);
		len_dist = ft_raytrace_objects(ray, &tmp);
		// if (tmp.check != 0)
		// 	p->object[n]->check = tmp.check;
		if (len_dist != -1 && len_dist > 0.001 && len_dist < *dist)
		{
			*dist = len_dist;
			id = n;
			// if (p->object[n]->tip == e_hemisphere)
			// 	p->object[n]->check = tmp.check;
		}
		n += 1;
	}
	return (id);
}

int		ft_calculate_color(t_rtv *p, t_vector *ray, double min_dist, int id)
{
	t_vector	intersect;
	t_vector	start;
	t_vector	norm;
	// t_vector	direct;
	t_array		color;
	double		min_refract;

	color.reflect = NO_COLOR;
	color.refract = NO_COLOR;
	intersect = ft_multiply_vector_num(ray, min_dist);
	norm = calculate_vector_norm(p->object[id], &intersect);
	color.local = ft_local_color(p, &intersect, &norm, id);

	start = intersect;
	if (p->object[id]->refraction > 0)
	{
		min_refract = p->object[id]->refraction;
		color.refract = ft_refraction(p, ray, &start, &min_refract);
	}
	// direct = *ray;
	start = intersect;
	if (p->object[id]->reflection > 0)
		color.reflect = ft_reflection(p, ray, &start, &norm);

	color.local =
	result_color(color.local, color.reflect, p->object[id]->reflection);
	color.local =
	result_color(color.local, color.refract, p->object[id]->refraction);
	return (color.local);
}

int		ft_color_object(t_rtv *p, t_vector *ray, int *id, double *min_dist)
{
	int		color;

	*id = ft_intersect_obj(p, ray, NULL, min_dist);
	if (*id == NO_INTERSECT)
		return (COLOR_BG_BL);
	color = ft_calculate_color(p, ray, *min_dist, *id);
	return (color);
}

void	*thread_paint_object(void *param)
{
	t_data		*data;
	t_vector	ray;
	int			color;
	int			id;
	double		min_dist;

	data = (t_data *)param;
	while (data->y_start < data->y_end)
	{
		data->x = 0;
		while (data->x < data->width)
		{
			data->camera.dir.x = (double)data->x - (double)data->x0;
			data->camera.dir.y = (double)data->y0 - (double)data->y_start;
			ray = data->camera.dir;
			ray = ft_rotation_vector(&data->all->camera->angle, &ray);
			ft_unit_vector(&ray);
			color = ft_color_object(data->all, &ray, &id, &min_dist);
			data->all->draw[data->x + data->y_start * data->width] = color;
			data->x += 1;
		}
		data->y_start += 1;
	}
	return (NULL);
}

void	ft_multi_thread_paint(t_rtv *paint)
{
	pthread_t	id[NUM_THREAD];
	t_data		data[NUM_THREAD];
	size_t		n;

	n = 0;
	while (n < NUM_THREAD)
	{
		data[n].all = paint;
		data[n].camera.dir.z = paint->fov;
		data[n].y_start = n * paint->height / NUM_THREAD;
		data[n].y_end = (n + 1) * paint->height / NUM_THREAD;
		data[n].x0 = (paint->width - 1) / 2.0;
		data[n].y0 = (paint->height - 1) / 2.0;
		data[n].width = paint->width;
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

// void		ft_paint_object(t_rtv *p)
// {
// 	int			x;
// 	int			y;
// 	int			pixel_color;
// 	t_vector	ray;

// 	y = 0;
// 	while (y < HIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDHT)
// 		{
// 			p->camera->dir.x = (float)(x - p->x0);
// 			p->camera->dir.y = (float)(p->y0 - y);
// 			// ray = p->camera->dir;
// 			// ft_rotat_vector(&p->camera->angle, &ray);
// 			ray = ft_rotation_vector(&p->camera->angle, &p->camera->dir);
// 			ft_unit_vector(&ray);
// 			pixel_color = ft_light_object(p, &ray);
// 			p->draw[x + y * WIDHT] = pixel_color;
// 			x += 1;
// 		}
// 		y += 1;
// 	}
// }

// t_array	specular_transparency(t_rtv *p, t_vector *intersect, t_vector *norm, int id)
// {
// 	t_vector	tmp_norm;
// 	t_vector	direct;
// 	t_array		color;

// 	color.reflect = NO_COLOR;
// 	color.refract = NO_COLOR;

// 	direct = *intersect;
// 	if (p->object[id]->refraction > 0)
// 		color.refract = ft_refraction(p, &direct, p->object[id]->refraction);

// 	direct = *intersect;
// 	tmp_norm = *norm;
// 	if (p->object[id]->reflection > 0)
// 		color.reflect = ft_reflection(p, &direct, norm);

// 	return color;
// }

// int		ft_light_object(t_rtv *p, t_vector *ray, int *id, double *min_dist)
// {
// 	t_vector	intersect;
// 	t_vector	norm;
// 	int			local_color;
// 	t_array		color;

// 	*id = ft_intersect_obj(p, ray, NULL, min_dist);
// 	if (*id == NO_INTERSECT)
// 		return (COLOR_BG_BL);
// 	intersect = ft_multiply_vector_num(ray, *min_dist);
// 	norm = calculate_vector_norm(p->object[*id], &intersect, NULL);
// 	local_color = calculate_color(p, &intersect, &norm, *id);
// 	color = specular_transparency(p, &intersect, &norm, *id);
// 	local_color =
// 	result_color(local_color, color.reflect, p->object[*id]->reflection);
// 	local_color =
// 	result_color(local_color, color.refract, p->object[*id]->refraction);
// 	return (local_color);
// }
