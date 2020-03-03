#include "rtv1.h"

float		ft_intersect_ray_sphere(t_vector *ray, t_object *s)
{
	float	proection_ray;
	float	len_dir;
	float	len_dist;

	proection_ray = ft_vector_projection_on_ray(&s->pos, ray);
	len_dir = s->radius - (s->len_pos - pow(proection_ray, 2));
	if (len_dir < 0.001f)
		return (-1);
	len_dist = proection_ray - sqrt(len_dir);
	return (len_dist);
}

float		ft_intersect_ray_plane(t_vector *ray, t_object *plane)
{
	float		angele;
	float		len_dist;

	angele = -ft_vector_scalar(&plane->norm, ray);
	if (angele <= 0.001f)
		return (-1);
	len_dist = ft_vector_scalar(&plane->pos, &plane->norm) / ft_vector_scalar(&plane->norm, ray);
	return (len_dist);
}

	/* (p0 - c).(p0 - c) - r^2 */
	
	/* Solving the discriminant */
	// float discr = B * B - 4 * A * C;
	
	/* If the discriminant is negative, there are no real roots.
	 * Return false in that case as the ray misses the sphere.
	 * Return true in all other cases (can be one or two intersections)
	 */
	// if (discr < 0)

// /* A = dd, векторное произведение точек направления * /
// 	float A = vectorDot (& r-> dir, & r-> dir); 

// 	/ * Нам нужен вектор, представляющий расстояние между началом 
// 	* луча и положением круга.
// 	 * Это термин (p0 - c) 
// 	 * /
// 	 vector dist = vectorSub (& r-> start, & s-> pos);

// 	 / * 2d. (P0 - c) * /  
// 	 float B = 2 * vectorDot (& r-> dir, & dist);

// 	 / * (p0 - c). (p0 - c) - r ^ 2 * /
// 	 float C = vectorDot (& dist, & dist) - (s-> radius * s-> radius);

// 	/ * Решение дискриминанта * /
// 	float discr = B * B - 4 * A * C;

// 	/ * Если дискриминант отрицательный, реальных корней нет.
// 	* В этом случае верните false, поскольку луч не попадает в сферу.
// 	* Верните true во всех других случаях (может быть одно или два пересечения)
// 	* /