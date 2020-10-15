#include "rtv1.h"

t_cross		ft_intersect_objects(t_rtv *p, t_vector *ray, t_vector *start)
{
	t_object	tmp_object;
	t_cross		result;
	t_cross		intersect;
	int			n;

	intersect.id = NO_INTERSECT;
	intersect.len = INT_MAX;
	n = 0;
	while (NULL != p->object[n])
	{
		tmp_object = *p->object[n];
		if (start != NULL)
			object_data(&tmp_object, start);
		result = ft_raytrace_objects(&tmp_object, ray);
		if (result.id == INTERSECT &&
			result.len > 0.001 && result.len < intersect.len)
		{
			intersect.len = result.len;
			intersect.id = n;
			intersect.check = result.check;
		}
		n += 1;
	}
	return (intersect);
}

int		ft_calculate_color(t_rtv *p, t_vector *ray, t_cross *intersect)
{
	t_vector	start;
	t_vector	norm;
	// t_vector	direct;
	t_array		color;
	double		min_refract;

	color = (t_array){.local = NO_COLOR, .reflect = NO_COLOR, .refract = NO_COLOR};
	norm = calculate_vector_norm(p->object[intersect->id], intersect, ray);
	check_normal(ray, &norm);
	color.local = ft_local_color(p, intersect, &norm);

	start = intersect->vec3;
	if (p->object[intersect->id]->refraction > 0)
	{
		min_refract = p->object[intersect->id]->refraction;
		color.refract = ft_refraction(p, ray, &start, &min_refract);
	}

	// direct = *ray;
	start = intersect->vec3;
	if (p->object[intersect->id]->reflection > 0)
		color.reflect = ft_reflection(p, ray, &start, &norm);

	color.local =
	result_color(color.local, color.reflect, p->object[intersect->id]->reflection);
	color.local =
	result_color(color.local, color.refract, p->object[intersect->id]->refraction);
	return (color.local);
}

int		ft_color_object(t_rtv *p, t_vector *ray)
{
	int		color;
	t_cross	intersect;

	intersect = ft_intersect_objects(p, ray, NULL);
	if (intersect.id == NO_INTERSECT)
		return (COLOR_BG_BL);
	intersect.vec3 = ft_multiply_vector_num(ray, intersect.len);
	color = ft_calculate_color(p, ray, &intersect);
	return (color);
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
		while (data->x < data->width)
		{
			data->camera.dir.x = (double)data->x - (double)data->x0;
			data->camera.dir.y = (double)data->y0 - (double)data->y_start;
			ray = data->camera.dir;
			ray = ft_rotation_vector(&data->all->camera->angle, &ray);
			ft_unit_vector(&ray);
			color = ft_color_object(data->all, &ray);
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
// 			// ft_rotate_vector(&p->camera->angle, &ray);
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
