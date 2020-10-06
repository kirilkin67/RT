#include "rtv1.h"

double		check_intersect_old(t_vector *ray, t_object *obj)
{
	t_vector	intersect;
	double		angle_1;
	double		angle_2;

	intersect = ft_multiply_vector_num(ray, obj->discr.d_1);
	angle_1 = calc_angle(&obj->pos, &obj->axis, &intersect, obj->min);
	angle_2 = calc_angle(&obj->pos, &obj->axis, &intersect, obj->max);
	if (angle_1 >= 0.001f && angle_2 <= 0.001f)
		return (obj->discr.d_1);
	intersect = ft_multiply_vector_num(ray, obj->discr.d_2);
	angle_1 = calc_angle(&obj->pos, &obj->axis, &intersect, obj->min);
	angle_2 = calc_angle(&obj->pos, &obj->axis, &intersect, obj->max);
	if (angle_1 >= 0.001f && angle_2 <= 0.001f)
		return (obj->discr.d_2);
	return (NO_INTERSECT);
}

double	calculate_len_cups(t_vector *ray, t_object *object)
{
	t_vector	position;
	t_vector	delta;
	double		angle;
	double		len_plane;

	angle = ft_vector_scalar(ray, &object->axis);
	if (angle > 0)
		position = ft_multiply_vector_num(&object->axis, object->min);
	else if (angle < 0)
		position = ft_multiply_vector_num(&object->axis, object->max);
	position = ft_add_vectors(&object->pos, &position);
	len_plane = ft_vector_scalar(&position, &object->axis) / angle;

	delta = ft_multiply_vector_num(ray, len_plane);
	delta= ft_sub_vectors(&delta, &position);
	
	if (ft_vector_scalar(&delta, &delta) >= (object->radius * object->radius))
		return (NO_INTERSECT);
	return (len_plane);
}

double		ft_intersect_ray_cylinder(t_vector *ray, t_object *cylindr)
{
	t_vector	v1;
	double		check;
	double		len_plane;

	v1 = ft_multiply_vector_num(&cylindr->axis,\
								ft_vector_scalar(ray, &cylindr->axis));
	v1 = ft_sub_vectors(ray, &v1);
	cylindr->discr.a = ft_vector_scalar(&v1, &v1);
	cylindr->discr.b = 2 * ft_vector_scalar(&v1, &cylindr->discr.v2);
	ft_solve_quadratic_equation(&cylindr->discr);

	len_plane = calculate_len_cups(ray, cylindr);

	if (cylindr->discr.discr < 0)
		return (len_plane);
	if (cylindr->discr.d_2 > 0.001f)
	{
		check = check_intersect(ray, &cylindr->pos, &cylindr->axis, cylindr->discr.d_1);
		if (cylindr->min <= check && check <= cylindr->max)
			return (cylindr->discr.d_1);
	}
	return (len_plane);
}

double		ft_intersect_ray_tube(t_vector *ray, t_object *tube)
{
	t_vector	v1;
	double		check;

	v1 = ft_multiply_vector_num(&tube->axis,\
								ft_vector_scalar(ray, &tube->axis));
	v1 = ft_sub_vectors(ray, &v1);
	tube->discr.a = ft_vector_scalar(&v1, &v1);
	tube->discr.b = 2 * ft_vector_scalar(&v1, &tube->discr.v2);
	ft_solve_quadratic_equation(&tube->discr);
	if (tube->discr.discr < 0)
		return (NO_INTERSECT);
	check = check_intersect(ray, &tube->pos, &tube->axis, tube->discr.d_1);
	if (tube->max >= check && check >= tube->min)
		return (tube->discr.d_1);
	check = check_intersect(ray, &tube->pos, &tube->axis, tube->discr.d_2);
	if (tube->max >= check && check >= tube->min)
		return (tube->discr.d_2);
	return (NO_INTERSECT);
}

// double		ft_intersect_circle_plane(t_vector *ray, t_object *plane, double r)
// {
// 	double		len_dist;
// 	double		angle;
// 	t_vector	delta;

// 	angle = ft_vector_scalar(&plane->axis, ray);
// 	if (angle >= 0)
// 		return (NO_INTERSECT);
// 	len_dist = ft_vector_scalar(&plane->pos, &plane->axis) / angle;
// 	if (len_dist == NO_INTERSECT)
// 		return (NO_INTERSECT);
// 	delta = ft_multiply_vector_num(ray, len_dist);
// 	delta= ft_sub_vectors(&delta, &plane->pos);
// 	if (ft_vector_scalar(&delta, &delta) > (r * r))
// 		return (NO_INTERSECT);
// 	return (len_dist);
// }
