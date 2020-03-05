#include "rtv1.h"

double		ft_intersect_ray_sphere(t_vector *ray, t_object *s)
{
	double	proection_ray;
	double	len_dir;
	double	len_dist;

	proection_ray = ft_vector_projection_on_ray(&s->pos, ray);
	len_dir = s->radius - (s->len_pos - pow(proection_ray, 2));
	if (len_dir < 0.001f)
		return (-1);
	len_dist = proection_ray - sqrt(len_dir);
	return (len_dist);
}

double		ft_intersect_ray_plane(t_vector *ray, t_object *plane)
{
	double		angele;
	double		len_dist;

	angele = -ft_vector_scalar(&plane->norm, ray);
	if (angele <= 0.001f)
		return (-1);
	len_dist = ft_vector_scalar(&plane->pos, &plane->norm) \
				/ ft_vector_scalar(&plane->norm, ray);
	return (len_dist);
}

/*
**Check if the ray and cilinder intersect
** FIST
** V_1 = (Ray - ft_vector_scalar(Ray, Nor) * Nor)
** V_1 = ft_multiply_vector_num(Nor, ft_vector_scalar(Ray, Nor))
** V_1 = ft_subtraction_vector(Ray, V_1)
** A = ft_vector_scalar(V_1, V_1)
** V_2 = ft_vector_scalar(Pos, Nor) * Nor) - Pos
** V_2 = ft_multiply_vector_num(Nor, ft_vector_scalar(Pos, Nor))
** V_2 = ft_subtraction_vector(V_2, Pos)
** B = 2 * (Ray - ft_vector_scalar(Ray, Nor) * Nor) * -1 * (Vector_Pos * V_2)
** B = 2 * ft_vector_scalar(V_1, V_2)
** C = ft_vector_scalar(V_2, V_2) - Radius^2
** SECOND
** A = Ray|Ray - (Ray|Nor_p)^2
** B = 2 * (Ray|Pos - (Ray|Nor_p)*(Pos|Nor_p))
** C = Pos|Pos - (Pos|Nor_p)^2 - Radius * Radius
** double discr = B * B - 4 * A * C;
*/

double		ft_solve_quadratic_equation(t_discr *discr)
{
	discr->sqrt_discr = sqrtf(discr->discr);
	discr->a = 2 * discr->a;
	discr->d_1 = (-discr->b - discr->sqrt_discr) / discr->a;
	discr->d_2 = (-discr->b + discr->sqrt_discr) / discr->a;
	if (discr->d_1 > 0.001f && discr->d_2 > 0.001f)
	{
		discr->d_1 = (discr->d_1 <= discr->d_2) ? discr->d_1 : discr->d_2;
		return (discr->d_1);
	}
	else if (discr->d_1 > 0.001f && discr->d_2 < 0.001f)
		return (discr->d_1);
	else if (discr->d_1 < 0.001f && discr->d_2 > 0.001f)
		return (discr->d_2);
	return (-1);
}

double		ft_intersect_ray_cilinder(t_vector *ray, t_object *c)
{
	t_vector	v1;
	double		len_dist;

	v1 = ft_multiply_vector_num(&c->norm_p, ft_vector_scalar(ray, &c->norm_p));
	v1 = ft_subtraction_vector(ray, &v1);
	c->discr.a = ft_vector_scalar(&v1, &v1);
	c->discr.b = 2 * ft_vector_scalar(&v1, &c->discr.v2);
	// printf("B_CILINDR- %f\n", c->discr.b);
	c->discr.discr = c->discr.b * c->discr.b - 4 * c->discr.a * c->discr.c;
	if (c->discr.discr < 0)
		return (-1);
	len_dist = ft_solve_quadratic_equation(&c->discr);
	return (len_dist);
}

/*
**Solving the discriminant
** double discr = B * B - 4 * A * C;
**
** If the discriminant is negative, there are no real roots.
** Return false in that case as the ray misses the sphere.
** Return true in all other cases (can be one or two intersections)
*/
