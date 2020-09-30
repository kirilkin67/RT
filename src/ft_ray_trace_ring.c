#include "rtv1.h"

double	calc_angle(t_vector *pos, t_vector *axis, t_vector *intersect,
					double max)
{
	t_vector	check;
	double		angle;

	if (max == 0.0)
		check = ft_sub_vectors(intersect, pos);
	else
	{
		check = ft_multiply_vector_num(axis, max);
		check = ft_add_vectors(pos, &check);
		check = ft_sub_vectors(intersect, &check);
	}
	ft_unit_vector(&check);
	angle = ft_vector_scalar(&check, axis);
	return (angle);
}

void	init_axis(t_object *ring, t_vector *axis)
{
	axis[0] = (t_vector){1, 0, 0};
	ft_rotat_vector(&ring->angle_n, &axis[0]);
	axis[1] = (t_vector){0, 1, 0};
	ft_rotat_vector(&ring->angle_n, &axis[1]);
	axis[2] = (t_vector){0, 0, 1};
	ft_rotat_vector(&ring->angle_n, &axis[2]);
}

int		check_intersect_ring(t_object *ring, t_vector *intersect)
{
	t_vector	axis[3];
	double		angle_1;
	double		angle_2;
	int			n;

	init_axis(ring, axis);
	n = 0;
	while (n < 3)
	{
		angle_1 = calc_angle(&ring->pos, &axis[n], intersect, -ring->max);
		angle_2 = calc_angle(&ring->pos, &axis[n], intersect, ring->max);
		if (angle_1 >= 0.001f && angle_2 <= 0.001f)
			n += 1;
		else
			break ;
	}
	if (n != 3)
		return (NO_INTERSECT);
	return (INTERSECT);
}

double	ft_intersect_ray_ring(t_vector *ray, t_object *ring)
{
	t_vector	intersect;
	double		proection_ray;
	double		len_dir;
	double		len;

	proection_ray = ft_vector_projection_on_ray(&ring->pos, ray);
	len = ring->radius * ring->radius - ring->len_pos * ring->len_pos +
			proection_ray * proection_ray;
	if (len < 0.0)
		return (NO_INTERSECT);
	len_dir = proection_ray - sqrt(len);
	intersect = ft_multiply_vector_num(ray, len_dir);
	if (check_intersect_ring(ring, &intersect) == INTERSECT)
		return (len_dir);
	len_dir = proection_ray + sqrt(len);
	intersect = ft_multiply_vector_num(ray, len_dir);
	if (check_intersect_ring(ring, &intersect) == INTERSECT)
		return (len_dir);
	return (NO_INTERSECT);
}

double	ft_intersect_ray_hemisphere(t_vector *ray, t_object *s)
{
	double		len_dir;
	double		len_plane;
	double		angle;
	t_vector	check;

	len_dir = ft_intersect_ray_sphere(ray, s);
	if (len_dir == NO_INTERSECT)
		return (NO_INTERSECT);
	else
	{
		angle = ft_vector_scalar(&s->norm_p, ray);
		if (s->max == 0.0)
			len_plane = ft_vector_scalar(&s->pos, &s->norm_p) / angle;
		else
		{
			check = ft_multiply_vector_num(&s->norm_p, s->max);
			check = ft_add_vectors(&s->pos, &check);
			len_plane = ft_vector_scalar(&check, &s->norm_p) / angle;
		}
		if (len_dir - len_plane >= 0.001f)
		// {
		// 	s->check = e_caps;
			return (len_plane);
		// }
	}
	// s->check = e_body;
	return (len_dir);
}
