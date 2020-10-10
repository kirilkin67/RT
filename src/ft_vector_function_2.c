#include "rtv1.h"

/*
** Multiply Vector x Number(Scalar) and return the resulting Vector;
*/

t_vector	ft_multiply_vector_num(t_vector *vector, double num)
{
	t_vector result;

	// result.x = num * vector->x;
	// result.y = num * vector->y;
	// result.z = num * vector->z;
	result = (t_vector){num * vector->x, num * vector->y, num * vector->z};
	return (result);
}

void		ft_unit_vector(t_vector *vector)
{
	double		modul_v;

	modul_v = ft_vector_modul(vector);
	vector->x /= modul_v;
	vector->y /= modul_v;
	vector->z /= modul_v;
}

t_vector	new_start_vector(t_vector *intersect, t_vector *norm, double delta)
{
	t_vector new_start;

	new_start = ft_multiply_vector_num(norm, delta);
	new_start = ft_add_vectors(intersect, &new_start);
	return(new_start);
}

void		check_normal(t_vector *dir, t_vector *normal)
{
	if (ft_vector_scalar(dir, normal) > 0)
		*normal = ft_multiply_vector_num(normal, -1);
}

// t_vector	ft_rotation_vector(t_vector *angle, t_vector *ray)
// {
// 	t_vector	dot;
// 	double		x;

// 	dot.y = ray->y * cos(angle->x) + ray->z * sin(angle->x);
// 	dot.z = -ray->y * sin(angle->x) + ray->z * cos(angle->x);
// 	dot.x = ray->x * cos(angle->y) + dot.z * sin(angle->y);
// 	dot.z = -ray->x * sin(angle->y) + dot.z * cos(angle->y);
// 	x = dot.x;
// 	dot.x = x * cos(angle->z) - dot.y * sin(angle->z);
// 	dot.y = x * sin(angle->z) + dot.y * cos(angle->z);
// 	return (dot);
// }

t_vector	ft_rotation_vector(t_vector *angle, t_vector *ray)
{
	t_vector	dot;
	t_matrix	val;
	double		x;

	val.cos_x = cos(angle->x);
	val.cos_y = cos(angle->y);
	val.cos_z = cos(angle->z);
	val.sin_x = sin(angle->x);
	val.sin_y = sin(angle->y);
	val.sin_z = sin(angle->z);
	dot.y = ray->y * val.cos_x + ray->z * val.sin_x;
	dot.z = -ray->y * val.sin_x + ray->z * val.cos_x;
	dot.x = ray->x * val.cos_y + dot.z * val.sin_y;
	dot.z = -ray->x * val.sin_y + dot.z * val.cos_y;
	x = dot.x;
	dot.x = x * val.cos_z - dot.y * val.sin_z;
	dot.y = x * val.sin_z + dot.y * val.cos_z;
	return (dot);
}

void		ft_rotat_vector(t_vector *angle, t_vector *ray)
{
	t_matrix	val;
	double		y;
	double		x;

	val.cos_x = cos(angle->x);
	val.cos_y = cos(angle->y);
	val.cos_z = cos(angle->z);
	val.sin_x = sin(angle->x);
	val.sin_y = sin(angle->y);
	val.sin_z = sin(angle->z);
	y = ray->y;
	ray->y = y * val.cos_x + ray->z * val.sin_x;
	ray->z = -y * val.sin_x + ray->z * val.cos_x;
	x = ray->x;
	ray->x = x * val.cos_y + ray->z * val.sin_y;
	ray->z = -x * val.sin_y + ray->z * val.cos_y;
	x = ray->x;
	ray->x = x * val.cos_z - ray->y * val.sin_z;
	ray->y = x * val.sin_z + ray->y * val.cos_z;
}
