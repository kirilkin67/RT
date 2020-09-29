#include "rtv1.h"

// double	check_angle(t_vector *pos, t_vector *axis, t_vector *intersect, double max)
// {
// 	t_vector	check;
// 	double		angle;

// 	if (max == 0.0)
// 		check = ft_sub_vectors(intersect, pos);
// 	else
// 	{
// 		check = ft_multiply_vector_num(axis, max);
// 		check = ft_add_vectors(pos, &check);
// 		check = ft_sub_vectors(intersect, &check);
// 	}
// 	ft_unit_vector(&check);
// 	angle = ft_vector_scalar(&check, axis);
// 	return (angle);
// }

double		ft_intersect_ray_sphere(t_vector *ray, t_object *sphere)
{
	t_vector	intersect;
	double		proection_ray;
	double		len_dir;
	double		len;

	proection_ray = ft_vector_projection_on_ray(&sphere->pos, ray);
	len = sphere->radius * sphere->radius - sphere->len_pos * sphere->len_pos +
			proection_ray * proection_ray;
	if (len < 0.0)
		return (NO_INTERSECT);
	len_dir = proection_ray - sqrt(len);
	if (ABS(sphere->hight) < sphere->radius)
	{
		intersect = ft_multiply_vector_num(ray, len_dir);
		if (check_angle(&sphere->pos, &sphere->norm_p, &intersect, sphere->hight) <= 0.001)
			return (len_dir);
		len_dir = proection_ray + sqrt(len);
		intersect = ft_multiply_vector_num(ray, len_dir);
		if (check_angle(&sphere->pos, &sphere->norm_p, &intersect, sphere->hight) <= 0.001)
			return (len_dir);
	}
	return (NO_INTERSECT);
}

double		ft_intersect_ray_plane(t_vector *ray, t_object *plane)
{
	double		angle;
	double		len_dist;

	angle = ft_vector_scalar(&plane->norm_p, ray);
	if (angle >= 0.001f)
		return (NO_INTERSECT);
	len_dist = ft_vector_scalar(&plane->pos, &plane->norm_p) / angle;
	return (len_dist);
}

// double		ft_intersect_circle_plane(t_vector *ray, t_object *plane, double r)
// {
// 	double		len_dist;
// 	t_vector	delta;

// 	len_dist = ft_intersect_ray_plane(ray, plane);
// 	if (len_dist == NO_INTERSECT)
// 		return (NO_INTERSECT);
// 	delta = ft_multiply_vector_num(ray, len_dist);
// 	delta= ft_sub_vectors(&delta, &plane->pos);
// 	if (ft_vector_scalar(&delta, &delta) > (r * r))
// 		return (NO_INTERSECT);
// 	return (len_dist);
// }

double		ft_intersect_ray_hemisphere(t_vector *ray, t_object *s)
{
	double	len_dir;
	double	len_plane;
	double	angle;
	t_vector	check;

	len_dir = ft_intersect_ray_sphere(ray, s);
	if (len_dir == NO_INTERSECT)
		return (NO_INTERSECT);
	else
	{
		angle = ft_vector_scalar(&s->norm_p, ray);
		if (s->hight == 0.0)
			len_plane = ft_vector_scalar(&s->pos, &s->norm_p) / angle;
		else
		{
			check = ft_multiply_vector_num(&s->norm_p, s->hight);
			check = ft_add_vectors(&s->pos, &check);
			len_plane = ft_vector_scalar(&check, &s->norm_p) / angle;
		}
		if (len_plane <= len_dir)
		{
			s->check = e_caps;
			return (len_plane);
		}
	}
	s->check = e_body;
	return (len_dir);
}

double		ft_intersect_ray_cylinder(t_vector *ray, t_object *cyl)
{
	t_vector	v1;
	t_vector	intersect;
	double		angle_1;
	double		angle_2;

	v1 = ft_multiply_vector_num(&cyl->norm_p,\
								ft_vector_scalar(ray, &cyl->norm_p));
	v1 = ft_sub_vectors(ray, &v1);
	cyl->discr.a = ft_vector_scalar(&v1, &v1);
	cyl->discr.b = 2 * ft_vector_scalar(&v1, &cyl->discr.v2);
	ft_solve_quadratic_equation(&cyl->discr);
	if (cyl->discr.discr < 0)
		return (NO_INTERSECT);
	else
	{
		intersect = ft_multiply_vector_num(ray, cyl->discr.d_1);
		angle_1 = check_angle(&cyl->pos, &cyl->norm_p, &intersect, 0.0);
		angle_2 = check_angle(&cyl->pos, &cyl->norm_p, &intersect, cyl->hight);
		if (angle_1 >= 0.001f && angle_2 <= 0.001f)
			return (cyl->discr.d_1);
		else
		{
			intersect = ft_multiply_vector_num(ray, cyl->discr.d_2);
			angle_1 = check_angle(&cyl->pos, &cyl->norm_p, &intersect, 0.0);
			angle_2 = check_angle(&cyl->pos, &cyl->norm_p, &intersect, cyl->hight);
			if (angle_1 >= 0.001f && angle_2 <= 0.001f)
				return (cyl->discr.d_2);
		}
	}
	return (NO_INTERSECT);
}

double		ft_intersect_ray_cone(t_vector *ray, t_object *cone)
{
	t_discr	conus;
	double	ray_norm;
	double	ray_ray;
	double	ray_pos;
	double	len_dist;

	ray_ray = ft_vector_scalar(ray, ray);
	ray_norm = ft_vector_scalar(ray, &cone->norm_p);
	ray_pos = ft_vector_scalar(ray, &cone->pos);
	conus.a = ray_ray - cone->discr.k_tan * (ray_norm * ray_norm);
	conus.b = 2 * (cone->discr.k_tan * ray_norm * cone->discr.pos_n_p - ray_pos);
	conus.c = cone->discr.c;
	len_dist = ft_solve_quadratic_equation_2(&conus);
	return (len_dist);
}

double	ft_raytrace_objects(t_vector *ray, t_object *object)
{
	double		len_dist;

	len_dist = -1;
	if (object->tip == e_sphere)
		len_dist = ft_intersect_ray_sphere(ray, object);
	if (object->tip == e_plane) 
		len_dist = ft_intersect_ray_plane(ray, object);
	if (object->tip == e_cylindr)
		len_dist = ft_intersect_ray_cylinder(ray, object);
	if (object->tip == e_cone)
		len_dist = ft_intersect_ray_cone(ray, object);
	if (object->tip == e_hemisphere)
		len_dist = ft_intersect_ray_hemisphere(ray, object);
	if (object->tip == e_ring)
		len_dist = ft_intersect_ray_ring(ray, object);
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
** B = -2 * (Ray|Pos - (Ray|Nor_p)*(Pos|Nor_p))
** C = Pos|Pos - (Pos|Nor_p)^2 - Radius * Radius
** double discr = B * B - 4 * A * C;
** void		ft_solve_discriminant(t_discr *discr)
** {
** 	discr->discr = discr->b * discr->b - 4 * discr->a * discr->c;
** }
*/

// double		ft_intersect_ray_cylinder(t_vector *ray, t_object *cil)
// {
// 	t_vector	v1;
// 	t_discr		cilindr;
// 	double		len_dist;

// 	v1 = ft_multiply_vector_num(&cil->norm_p,\
// 								ft_vector_scalar(ray, &cil->norm_p));
// 	v1 = ft_sub_vectors(ray, &v1);
// 	cilindr.a = ft_vector_scalar(&v1, &v1);
// 	cilindr.b = 2 * ft_vector_scalar(&v1, &cil->discr.v2);
// 	cilindr.c = cil->discr.c;
// 	len_dist = ft_solve_quadratic_equation(&cilindr);
// 	return (len_dist);
// }

// t_vector	**init_axis(t_object *ring, t_vector **axis)
// {
// 	int n;
// 	axis = (t_vector **)malloc(sizeof(t_vector *) * 4);
// 	if (axis == NULL)
// 		ft_exit(ERR_CREAT_TO_ARR);
// 	n = 0;
// 	while (n < 3)
// 	{
// 		axis[n] = ft_memalloc(sizeof(t_vector));
// 		if (axis[n] == NULL)
// 			ft_exit(ERR_CREAT_TO_ARR);
// 		n += 1;
// 	}
// 	axis[n] =NULL;
// 	axis[0]->x = 1;
// 	axis[0]->y = 0;
// 	axis[0]->z = 0;
// 	ft_rotat_vector(&ring->angle_n, axis[0]);
// 	// printf("%f %f %f\n", axis[0]->x, axis[0]->y, axis[0]->z);
// 	axis[1]->x = 0;
// 	axis[1]->y = 1;
// 	axis[1]->z = 0;
// 	ft_rotat_vector(&ring->angle_n, axis[1]);
// 	// printf("%f %f %f\n", axis[1]->x, axis[1]->y, axis[1]->z);
// 	axis[2]->x = 0;
// 	axis[2]->y = 0;
// 	axis[2]->z = 1;
// 	ft_rotat_vector(&ring->angle_n, axis[2]);
// 	// printf("%f %f %f\n", axis[2]->x, axis[2]->y, axis[2]->z);
// 	return (axis);
// }
