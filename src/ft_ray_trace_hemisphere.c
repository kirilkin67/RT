#include "rtv1.h"

// double		check_intersect_old(t_vector *ray, t_object *obj)
// {
// 	t_vector	intersect;
// 	double		angle_1;
// 	double		angle_2;

// 	intersect = ft_multiply_vector_num(ray, obj->discr.d_1);
// 	angle_1 = calc_angle(&obj->pos, &obj->norm_p, &intersect, obj->min);
// 	angle_2 = calc_angle(&obj->pos, &obj->norm_p, &intersect, obj->max);
// 	if (angle_1 >= 0.001f && angle_2 <= 0.001f)
// 		return (obj->discr.d_1);
// 	intersect = ft_multiply_vector_num(ray, obj->discr.d_2);
// 	angle_1 = calc_angle(&obj->pos, &obj->norm_p, &intersect, obj->min);
// 	angle_2 = calc_angle(&obj->pos, &obj->norm_p, &intersect, obj->max);
// 	if (angle_1 >= 0.001f && angle_2 <= 0.001f)
// 		return (obj->discr.d_2);
// 	return (NO_INTERSECT);
// }

double		check_intersect(t_vector *ray, t_vector *pos,t_vector *axis, double len)
{
	t_vector	intersect;
	double		check;

	intersect = ft_multiply_vector_num(ray, len);
	intersect = ft_sub_vectors(&intersect, pos);
	check = ft_vector_projection_on_ray(&intersect, axis);
	return (check);
}

double	calculate_len_plane(t_vector *ray, t_object *sphere)
{
	t_vector	intersect;
	double		angle;
	double		len_plane;

	angle = ft_vector_scalar(&sphere->norm_p, ray);
	if (sphere->min == 0.0)
		len_plane = ft_vector_scalar(&sphere->pos, &sphere->norm_p) / angle;
	else
	{
		intersect = ft_multiply_vector_num(&sphere->norm_p, sphere->min);
		intersect = ft_add_vectors(&sphere->pos, &intersect);
		len_plane = ft_vector_scalar(&intersect, &sphere->norm_p) / angle;
	}
	return (len_plane);
}

double		ft_intersect_ray_hemisphere(t_vector *ray, t_object *sphere)
{
	double		proection_ray;
	double		len_dir;
	double		len;
	double		check;
	double		len_plane;

	proection_ray = ft_vector_projection_on_ray(&sphere->pos, ray);
	len = sphere->radius * sphere->radius - sphere->len_pos * sphere->len_pos +
			proection_ray * proection_ray;
	if (len < 0)
		return (NO_INTERSECT);
	len_dir = proection_ray - sqrt(len);
	check = check_intersect(ray, &sphere->pos, &sphere->norm_p, len_dir);
	if (check <= sphere->min)
		return (len_dir);
	len_dir = proection_ray + sqrt(len);
	check = check_intersect(ray, &sphere->pos, &sphere->norm_p, len_dir);
	if (check <= sphere->min)
	{
		len_plane = calculate_len_plane(ray, sphere);
		return (len_plane);
	}
	return (NO_INTERSECT);
}
