#include "rtv1.h"

/*
** Multiply Vector x Number(Scalar) and return the resulting Vector;
*/

t_vector	ft_multiply_vector_num(t_vector *vector, double num)
{
	t_vector result;

	result.x = num * vector->x;
	result.y = num * vector->y;
	result.z = num * vector->z;
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
	double		x;
	double	cos_x = cos(angle->x);
	double	cos_y = cos(angle->y);
	double	cos_z = cos(angle->z);
	double	sin_x = sin(angle->x);
	double	sin_y = sin(angle->y);
	double	sin_z = sin(angle->z);

	dot.y = ray->y * cos_x + ray->z * sin_x;
	dot.z = -ray->y * sin_x + ray->z * cos_x;
	dot.x = ray->x * cos_y + dot.z * sin_y;
	dot.z = -ray->x * sin_y + dot.z * cos_y;
	x = dot.x;
	dot.x = x * cos_z - dot.y * sin_z;
	dot.y = x * sin_z + dot.y * cos_z;
	return (dot);
}

void		ft_rotat_vector(t_vector *angle, t_vector *ray)
{
	double		y;
	double		x;

	y = ray->y;
	ray->y = y * cos(angle->x) + ray->z * sin(angle->x);
	ray->z = -y * sin(angle->x) + ray->z * cos(angle->x);
	x = ray->x;
	ray->x = x * cos(angle->y) + ray->z * sin(angle->y);
	ray->z = -x * sin(angle->y) + ray->z * cos(angle->y);
	x = ray->x;
	ray->x = x * cos(angle->z) - ray->y * sin(angle->z);
	ray->y = x * sin(angle->z) + ray->y * cos(angle->z);
}

void		ft_solve_discriminant(t_discr *discr)
{
	discr->discr = (double)(discr->b * discr->b - 4 * discr->a * discr->c);
}
