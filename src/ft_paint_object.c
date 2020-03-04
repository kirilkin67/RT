#include "rtv1.h"

/* Check if the ray and cilinder intersect
** A = (Ray - ft_vector_scalar(Ray, Nor) * Nor)^2
** Vector = (Ray - ft_vector_scalar(Ray, Nor) * Nor)
** Vector = ft_multiply_vector_num(Nor, ft_vector_scalar(Ray, Nor))
** Vector = ft_subtraction_vector(Ray, Vector)
** A = ft_vector_scalar(Vector, Vector)
** B = 2 * (Ray - ft_vector_scalar(Ray, Nor) * Nor) * -1 * Vector_Pos)
** B = 2 * ft_vector_scalar(Vector, -1 * Vector_Pos)
** C = ft_vector_scalar(Vector_Pos, Vector_Pos) - Radius
** float discr = B * B - 4 * A * C;
*/

float		ft_intersect_ray_cilinder(t_vector *ray, t_object *cil)
{
	t_vector	vector;
	float	a;
	float	b;
	float	c;
	float	discr;
	float	sqrt_discr;
	float	len_dist_0;
	float	len_dist_1;

	vector = ft_multiply_vector_num(&cil->norm_p, ft_vector_scalar(ray, &cil->norm_p));
	vector = ft_subtraction_vector(ray, &vector);
	a = ft_vector_scalar(&vector, &vector);
	b = -2 * ft_vector_scalar(&vector, &cil->pos);
	c = ft_vector_scalar( &cil->pos,  &cil->pos) - cil->radius;
	discr = b * b - 4 * a * c;
	// printf("DISCR- %f", discr);
	if (discr < 0)
		return (-1);
	else
	{
		sqrt_discr = sqrtf(discr);
		len_dist_0 = (-b - sqrt_discr)/(2 * a);
		len_dist_1 = (-b + sqrt_discr)/(2 * a);
		if (len_dist_0 > 0.001f && len_dist_1 > 0.001f)
		{
			if (len_dist_0 < len_dist_1)
				return (len_dist_0);
			else
				return (len_dist_1);
		}
		else if (len_dist_0 > 0.001f && len_dist_1 < 0.001f)
			return (len_dist_0);
		else if (len_dist_0 < 0.001f && len_dist_1 > 0.001f)
			return (len_dist_1);
	}
	return (-1);
}

int		ft_ray_trace_object(t_rtv *p, t_vector *ray, t_object **obj, t_light *l)
{
	t_vector	interset;
	t_vector	v_plane;
	t_vector	v_norm;
	float		len_dist;
	float		len_ray;
	int			color;
	int			n;

	p->min_dist = INT_MAX;
	p->id = -1;
	n = 0;
	while (n < 5)
	{
		if (obj[n]->id == 'S')
			len_dist = ft_intersect_ray_sphere(ray, obj[n]);
		else if (obj[n]->id == 'P' && obj[n]->pos_cam < 0)
			len_dist = ft_intersect_ray_plane(ray, obj[n]);
		else if (obj[n]->id == 'C')
			len_dist = ft_intersect_ray_cilinder(ray, obj[n]);
		if (len_dist != -1 && len_dist < p->min_dist)
			{
				p->min_dist = len_dist;
				p->id = n;
			}
		n += 1;
	}
	if (p->id == -1)
		return (0x0);
	interset = ft_multiply_vector_num(ray, p->min_dist);
	if (obj[p->id]->id == 'S')
	{
		obj[p->id]->norm = ft_subtraction_vector(&interset, &obj[p->id]->pos);
		color = ft_illumination_point(l, obj[p->id], &interset);
	}
	else if (obj[p->id]->id == 'P')
		color = ft_illumination_point(l, obj[p->id], &interset);
	else if (obj[p->id]->id == 'C')
	{
		v_plane = ft_subtraction_vector(&interset, &obj[p->id]->pos);
		len_ray = ft_vector_projection_on_ray(&v_plane, &obj[p->id]->norm_p);
		v_norm = ft_multiply_vector_num(&obj[p->id]->norm_p, len_ray);
		v_plane = ft_add_vector(&obj[p->id]->pos, &v_norm);
		obj[p->id]->norm = ft_subtraction_vector(&interset, &v_plane);
		color = ft_illumination_point(l, obj[p->id], &interset);
	}
	return (color);
}

void	ft_paint_object(t_rtv *p, t_camera *cam, t_object **obj, t_light *l)
{
	int	x;
	int	y;
	int	pixel_color;
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
			ray = ft_rotation_vector(p, &cam->dir);
			// ray = ft_rotat_vector(p->angle_x, p->angle_y, p->angle_z, &cam->dir);
			ft_unit_vector(&ray);
			// p->len_ray = ft_vector_modul(&ray);
			// printf("X- %f, Y- %f, Z- %f\n", ray.x, ray.y, ray.z);
			pixel_color = ft_ray_trace_object(p, &ray, obj, l);
			p->draw[x + y * WIDHT] = pixel_color;
			x += 1;
		}
		y += 1;
	}
}
