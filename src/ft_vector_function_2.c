#include "rtv1.h"

/*
** Multiply Vector x Number(Scalar) and return the resulting Vector;
*/

t_vector	ft_multiply_vector_num(t_vector *vector, float num)
{
	t_vector result;

	result.x = num * vector->x;
	result.y = num * vector->y;
	result.z = num * vector->z;
	return (result);
}

void	ft_unit_vector(t_vector *vector)
{
	// t_vector	result;
	float		modul_v;

	modul_v = ft_vector_modul(vector);
	vector->x /= modul_v;
	vector->y /= modul_v;
	vector->z /= modul_v;
	// return (result);
}

t_vector	ft_rotation_vector(t_vector *angle, t_vector *ray)
{
	t_vector	dot;
	float		x;

	dot.y = ray->y * cos(angle->x) + ray->z * sin(angle->x);
	dot.z = -ray->y * sin(angle->x) + ray->z * cos(angle->x);
	dot.x = ray->x * cos(angle->y) + dot.z * sin(angle->y);
	dot.z = -ray->x * sin(angle->y) + dot.z * cos(angle->y);
	x = dot.x;
	dot.x = x * cos(angle->z) - dot.y * sin(angle->z);
	dot.y = x * sin(angle->z) + dot.y * cos(angle->z);
	return (dot);
}

void		ft_rotat_vector(t_vector *angle, t_vector *ray)
{
	float		y;
	float		x;

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
	discr->discr = discr->b * discr->b - 4 * discr->a * discr->c;
}

// y = ray->y;
// 	dot.y = y * cos(angle->x) + ray->z * sin(angle->x);
// 	dot.z = -y * sin(angle->x) + ray->z * cos(angle->x);
// 	x = ray->x;
// 	dot.x = x * cos(angle->y) + ray->z * sin(angle->y);
// 	dot.z = -x * sin(angle->y) + ray->z * cos(angle->y);
// 	x = dot.x;
// 	dot.x = x * cos(angle->z) - dot.y * sin(angle->z);
// 	dot.y = x * sin(angle->z) + dot.y * cos(angle->z);