#include "rtv1.h"

void		solve_discriminant(t_discr *discr)
{
	discr->discr = discr->b * discr->b - 4 * discr->a * discr->c;
}

double		ft_intersect_ray_cone(t_vector *ray, t_object *k)
{
	double	ray_norm;
	double	ray_ray;
	double	ray_pos;
	double	len_dist;

	ray_ray = ft_vector_scalar(ray, ray);
	ray_norm = ft_vector_scalar(ray, &k->norm_p);
	ray_pos = ft_vector_scalar(ray, &k->pos);
	k->discr.a = ray_ray - k->discr.k_tan * pow(ray_norm, 2);
	k->discr.b = 2 * (ray_pos - k->discr.k_tan * ray_norm * k->discr.pos_n_p);
	k->discr.discr = k->discr.b * k->discr.b - 4 * k->discr.a * k->discr.c;
	// printf("B_CONE- %f\n", k->discr.b);
	// solve_discriminant(&k->discr);
	if (k->discr.discr < 0)
		return (-1);
	len_dist = ft_solve_quadratic_equation(&k->discr);
	return (len_dist);
}

int		ft_ray_trace_object(t_rtv *p, t_vector *ray, t_object **obj, t_light *l)
{
	t_vector	interset;
	t_vector	v_plane;
	t_vector	v_norm;
	double		len_dist;
	int			color;
	int			n;

	p->min_dist = INT_MAX;
	p->id = -1;
	n = 0;
	while (n < 7)
	{
		if (obj[n]->id == 'S')
			len_dist = ft_intersect_ray_sphere(ray, obj[n]);
		else if (obj[n]->id == 'P' && obj[n]->pos_cam < 0)
			len_dist = ft_intersect_ray_plane(ray, obj[n]);
		else if (obj[n]->id == 'C')
			len_dist = ft_intersect_ray_cilinder(ray, obj[n]);
		else if (obj[n]->id == 'K')
			len_dist = ft_intersect_ray_cone(ray, obj[n]);
		if (len_dist != -1 && len_dist < p->min_dist)
			{
				p->min_dist = len_dist;
				p->id = n;
			}
		n += 1;
	}
	if (p->id == -1)
		return (0x7D7D7D);
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
		p->len_ray = ft_vector_projection_on_ray(&v_plane, &obj[p->id]->norm_p);
		v_norm = ft_multiply_vector_num(&obj[p->id]->norm_p, p->len_ray);
		v_plane = ft_add_vector(&obj[p->id]->pos, &v_norm);
		obj[p->id]->norm = ft_subtraction_vector(&interset, &v_plane);
		color = ft_illumination_point(l, obj[p->id], &interset);
	}
	else if (obj[p->id]->id == 'K')
		color = obj[p->id]->color;
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
			ft_unit_vector(&ray);
			pixel_color = ft_ray_trace_object(p, &ray, obj, l);
			p->draw[x + y * WIDHT] = pixel_color;
			x += 1;
		}
		y += 1;
	}
}
