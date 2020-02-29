#include "rtv1.h"

t_vector	ft_vector_intersect(t_vector *ray , float dir, float dist)
{
	float		dot_interset;
	float		unit_v;
	t_vector	interset;

	dot_interset = dir - sqrt(dist);
	unit_v = dot_interset / ft_vector_modul(ray);
	interset = ft_multiply_vector_num(ray, unit_v);
	return (interset);
}

// int		ft_intersect_ray_plane(t_vector *ray, t_object *plane)
// {
// 	float		k_dir;
// 	float		angele;
// 	float		pos_cam;
// 	int			point_color;
// 	t_vector	interset;

// 	// pos_cam = ft_vector_scalar(&plane->norm, &plane->pos) - ft_vector_scalar(&plane->norm, &cam->start);
// 	angele = -ft_vector_scalar(&plane->norm, ray) / ft_vector_modul(&plane->norm) / ft_vector_modul(ray);
// 	if (angele <= 0.001f)// || cam->pos_cam >= 0)
// 		return (-1);
// 	else
// 	{
// 		k_dir = ft_vector_scalar(&plane->pos, &plane->norm) / ft_vector_scalar(&plane->norm, ray);
// 		if (k_dir != 0)
// 		{
// 			interset = ft_multiply_vector_num(ray, k_dir);
// 			point_color = ft_illumination_point(l, plane, &interset, &plane->norm);
// 			return (point_color);
// 		}
// 	}
// 	return (-1);
// }

float		ft_intersect_ray_sphere(t_vector *ray, t_object *s)
{
	float		len_ray;
	float		len_dir;
	float		len_dist;

	len_ray = ft_vector_projection_on_ray(&s->pos, ray);
	len_dir = s->radius - (s->len_pos - pow(len_ray, 2));
	if (len_dir < 0.001f)
		return (-1);
	len_dist = len_ray - sqrt(len_dir);
	return (len_dist);
}

int		ft_ray_trace_object(t_rtv *p, t_vector *ray, t_object **obj, t_light *l)
{
	t_vector	interset;
	float		len_dist;
	float		unit_v;
	int			color;
	int			n;

	p->min_dist = INT_MAX;
	p->id = -1;
	n = 0;
	while (n < 3)
	{
		if (obj[n]->id == 'S')
		{
			len_dist = ft_intersect_ray_sphere(ray, obj[n]);
			if (len_dist != -1 && len_dist < p->min_dist)
			{
				p->min_dist = len_dist;
				p->id = n;
			}
		}
		// else if (obj[n]->id == 'P')
		// {

		// }
		n += 1;
	}
	if (p->id == -1)
		return (0x0);
	else if (obj[p->id]->id == 'S')
	{
		unit_v = p->min_dist / ft_vector_modul(ray);
		interset = ft_multiply_vector_num(ray, unit_v);
		obj[p->id]->norm = ft_subtraction_vectors(&interset, &obj[p->id]->pos);
		color = ft_illumination_point(l, obj[p->id], &interset);
	}
	return (color);
}

void	ft_paint_object(t_rtv *p, t_camera *cam, t_object **obj, t_light *l)
{
	int	x;
	int	y;
	int	pixel_color;
	// t_camera ray;
	t_vector	*ray;

	p->x0 = WIDHT / 2;
	p->y0 = HIGHT / 2;
	ray = &cam->dir;
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
			pixel_color = ft_ray_trace_object(p, &cam->dir, obj, l);
			p->draw[x + y * WIDHT] = pixel_color;
			x += 1;
		}
		y += 1;
	}
}
