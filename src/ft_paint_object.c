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

void	ft_intersection_object(t_rtv *p, t_vector *ray, t_object **obj)
{
	int		n;
	float	len_dist;

	p->id = -1;
	p->min_dist = INT_MAX;
	n = 0;
	while (obj[n] != NULL)
	{
		len_dist = ft_ray_trace_object(ray, obj[n]);
		if (len_dist != -1 && len_dist > 0.001f && len_dist < p->min_dist)
		{
			p->min_dist = len_dist;
			p->id = n;
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

	ft_intersection_object(p, ray, obj);
	if (p->id == -1)
		return (0x0);
	interset = ft_multiply_vector_num(ray, p->min_dist);
	if (obj[p->id]->id == 'S' || obj[p->id]->id == 'C'|| obj[p->id]->id == 'K')
	{
		obj[p->id]->norm = ft_subtraction_vector(&interset, &obj[p->id]->pos);
		if (obj[p->id]->id == 'C'|| obj[p->id]->id == 'K')
		{
			len_ray = ft_vector_projection_on_ray(&obj[p->id]->norm, &obj[p->id]->norm_p);
			if (obj[p->id]->id == 'K')
				len_ray = len_ray / pow(cos(0.5 * obj[p->id]->angle), 2);
			v_norm = ft_multiply_vector_num(&obj[p->id]->norm_p, len_ray);
			obj[p->id]->norm = ft_subtraction_vector(&obj[p->id]->norm, &v_norm);
		}
		ft_unit_vector(&obj[p->id]->norm);
	}
	color = ft_illumination_point(l, obj, &interset, p->id);
	return (color);
}

void	ft_paint_object(t_rtv *p, t_camera *cam, t_object **obj, t_light *l)
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
			ray = ft_rotation_vector(&p->angle, &cam->dir);
			ft_unit_vector(&ray);
			pixel_color = ft_light_object(p, &ray, obj, l);
			p->draw[x + y * WIDHT] = pixel_color;
			x += 1;
		}
		y += 1;
	}
}
