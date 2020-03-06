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

void	ft_unit_vector(t_vector *vector)
{
	// t_vector	result;
	double		modul_v;

	modul_v = ft_vector_modul(vector);
	vector->x /= modul_v;
	vector->y /= modul_v;
	vector->z /= modul_v;
	// return (result);
}

t_vector	ft_rotation_vector(t_rtv *p, t_vector *ray)
{
	t_vector	dot;
	double		x;
	// t_fdf *p;
	// p = (t_fdf *)param;

	dot.y = ray->y * cos(p->angle_x) + ray->z * sin(p->angle_x);
	dot.z = -ray->y * sin(p->angle_x) + ray->z * cos(p->angle_x);
	dot.x = ray->x * cos(p->angle_y) + ray->z * sin(p->angle_y);
	dot.z = -ray->x * sin(p->angle_y) + ray->z * cos(p->angle_y);
	x = dot.x;
	dot.x = x * cos(p->angle_z) - dot.y * sin(p->angle_z);
	dot.y = x * sin(p->angle_z) + dot.y * cos(p->angle_z);
	return (dot);
}

void	ft_rotat_vector(double alfa, double betta, double gamma, t_vector *ray)
{
	double		y;
	double		x;

	y = ray->y;
	ray->y = y * cos(alfa) + ray->z * sin(alfa);
	ray->z = -y * sin(alfa) + ray->z * cos(alfa);
	x = ray->x;
	ray->x = x * cos(betta) + ray->z * sin(betta);
	ray->z = -x * sin(betta) + ray->z * cos(betta);
	x = ray->x;
	ray->x = x * cos(gamma) - ray->y * sin(gamma);
	ray->y = x * sin(gamma) + ray->y * cos(gamma);
}

void		ft_solve_discriminant(t_discr *discr)
{
	discr->discr = discr->b * discr->b - 4 * discr->a * discr->c;
}
