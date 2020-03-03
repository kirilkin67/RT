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
	t_vector	result;
	float		modul_v;

	modul_v = ft_vector_modul(vector);
	vector->x /= modul_v;
	vector->y /= modul_v;
	vector->z /= modul_v;
	// return (result);
}

t_vector	ft_rotation_vector(t_rtv *p, t_vector *ray)
{
	t_vector dot;

	dot.y = ray->y * cos(p->angle_x) + ray->z * sin(p->angle_x);
	dot.z = -ray->y * sin(p->angle_x) + ray->z * cos(p->angle_x);
	dot.x = ray->x * cos(p->angle_y) + ray->z * sin(p->angle_y);
	dot.z = -ray->x * sin(p->angle_y) + ray->z * cos(p->angle_y);
	dot.x = dot.x * cos(p->angle_z) - dot.y * sin(p->angle_z);
	dot.y = dot.x * sin(p->angle_z) + dot.y * cos(p->angle_z);
	return (dot);
}

/* Check if the ray and sphere intersect */
// bool intersectRay(t_camera *ray, t_object *obj)
// {
	
// 	/* A = d.d, the vector dot product of the direction */
// 	float A = ft_vector_scalar(&ray->dir, &ray->dir); 
	
// 	/* We need a vector representing the distance between the start of 
// 	** the ray and the position of the circle.
// 	** This is the term (p0 - c) 
// 	 */
// 	t_vector dist = ft_subtraction_vector(&ray->start, &obj->pos);
	
// 	/* 2d.(p0 - c) */  
// 	float B = 2 * ft_vector_scalar(&ray->dir, &dist);
	
// 	/* (p0 - c).(p0 - c) - r^2 */
// 	float C = ft_vector_scalar(&dist, &dist) - obj->radius;
	
// 	/* Solving the discriminant b2 - 4ac*/
// 	float Discr = B * B - 4 * A * C;
	
// 	/* If the discriminant is negative, there are no real roots.
// 	 * Return false in that case as the ray misses the sphere.
// 	 * Return true in all other cases (can be one or two intersections)
// 	 */
// 	if(Discr < 0)
// 		return false;
// 	else
// 		return true;
// }
