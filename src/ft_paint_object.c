#include "rtv1.h"

float		ft_intersect_ray_sphere(t_vector *ray, t_object *s)
{
	float	proection_ray;
	float	len_dir;
	float	len_dist;

	proection_ray = ft_vector_projection_on_ray(&s->pos, ray);
	len_dir = s->radius - (s->len_pos - pow(proection_ray, 2));
	if (len_dir < 0.001f)
		return (-1);
	len_dist = proection_ray - sqrt(len_dir);
	return (len_dist);
}

float		ft_intersect_ray_plane(t_vector *ray, float len_ray, t_object *plane)
{
	float		angele;
	float		k_dir;
	float		len_dist;

	angele = -ft_vector_scalar(&plane->norm, ray) / plane->len_norm / len_ray;
	if (angele <= 0.001f)
		return (-1);
	k_dir = ft_vector_scalar(&plane->pos, &plane->norm) / ft_vector_scalar(&plane->norm, ray);
	len_dist = k_dir * len_ray;
	return (len_dist);
}

int		ft_ray_trace_object(t_rtv *p, t_vector *ray, t_object **obj, t_light *l)
{
	t_vector	interset;
	float		len_dist;
	float		unit_vector;
	int			color;
	int			n;

	p->len_ray = ft_vector_modul(ray);
	p->min_dist = INT_MAX;
	p->id = -1;
	n = 0;
	while (n < 4)
	{
		if (obj[n]->id == 'S')
			len_dist = ft_intersect_ray_sphere(ray, obj[n]);
		else if (obj[n]->id == 'P' && obj[n]->pos_cam < 0)
			len_dist = ft_intersect_ray_plane(ray, p->len_ray, obj[n]);
		if (len_dist != -1 && len_dist < p->min_dist)
			{
				p->min_dist = len_dist;
				p->id = n;
			}
		n += 1;
	}
	if (p->id == -1)
		return (0x0);
	unit_vector = p->min_dist / p->len_ray;
	interset = ft_multiply_vector_num(ray, unit_vector);
	if (obj[p->id]->id == 'S')
	{
		// unit_v = p->min_dist / ft_vector_modul(ray);
		// interset = ft_multiply_vector_num(ray, unit_v);
		obj[p->id]->norm = ft_subtraction_vector(&interset, &obj[p->id]->pos);
		color = ft_illumination_point(l, obj[p->id], &interset);
	}
	else if (obj[p->id]->id == 'P')
		color = ft_illumination_point(l, obj[p->id], &interset);

	return (color);
}

void	ft_paint_object(t_rtv *p, t_camera *cam, t_object **obj, t_light *l)
{
	int	x;
	int	y;
	int	pixel_color;
	// t_camera ray;
	t_vector	ray;

	p->x0 = WIDHT / 2;
	p->y0 = HIGHT / 2;
	y = 0;
	while (y < HIGHT)
	{
		x = 0;
		while (x < WIDHT)
		{
			cam->dir.x = x - p->x0;
			cam->dir.y = p->y0 - y;
			// ray->x = x - p->x0;
			// ray->y = p->y0 - y;
			ray = ft_rotation_vector(p, &cam->dir);
			// printf("X- %f, Y- %f, Z- %f\n", ray.x, ray.y, ray.z);
			pixel_color = ft_ray_trace_object(p, &ray, obj, l);
			p->draw[x + y * WIDHT] = pixel_color;
			x += 1;
		}
		y += 1;
	}
}
