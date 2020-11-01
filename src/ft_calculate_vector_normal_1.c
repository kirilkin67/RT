#include "rt.h"

t_vector	vector_norm_tube(t_object *object, t_cross *intersect)
{
	t_vector	normal;
	t_vector	v_norm;
	double		len_ray;

	normal = ft_sub_vectors(&intersect->vec3, &object->pos);
	len_ray = ft_vector_projection_on_ray(&normal, &object->axis);
	v_norm = ft_multiply_vector_num(&object->axis, len_ray);
	normal = ft_sub_vectors(&normal, &v_norm);
	ft_unit_vector(&normal);
	return (normal);
}

t_vector	vector_norm_cylindr(t_object *object, t_cross *intersect)
{
	t_vector	normal;

	if (intersect->check == e_body)
		normal = vector_norm_tube(object, intersect);
	if (intersect->check == e_caps)
		normal = object->axis;
	return (normal);
}

t_vector	vector_norm_empty_cone(t_object *object, t_cross *intersect)
{
	t_vector	normal;
	t_vector	v_normal;
	double		len_ray;
	double		half_angle;

	half_angle = cos(0.5 * object->angle);
	normal = ft_sub_vectors(&intersect->vec3, &object->pos);
	len_ray = ft_vector_projection_on_ray(&normal, &object->axis);
	len_ray = len_ray / (half_angle * half_angle);
	v_normal = ft_multiply_vector_num(&object->axis, len_ray);
	normal = ft_sub_vectors(&normal, &v_normal);
	ft_unit_vector(&normal);
	return (normal);
}

t_vector	vector_norm_cone(t_object *object, t_cross *intersect)
{
	t_vector	normal;

	if (intersect->check == e_body)
		normal = vector_norm_empty_cone(object, intersect);
	if (intersect->check == e_caps)
		normal = object->axis;
	return (normal);
}

// t_vector	vector_norm_paraboloid(t_object object, t_coord crossp)
// {
// 	double	m;
// 	t_coord v;
// 	t_coord normal;

// 	v = ft_mult_num_vector(1 / ft_lengthv(object.vectorperp), object.vectorperp);
// 	m = ft_dotprod(ft_substrv(crossp, object.center), v);
// 	normal = ft_substrv(ft_substrv(crossp, object.center), ft_mult_num_vector((m + object.k_paraboloid), v));
// 	//normal = ft_norm_vector(normal);
// 	return(normal);
// }

t_vector	vector_norm_paraboloid(t_object *object, t_cross *intersect)
{
	double		m;
	t_vector	v;
	t_vector	tmp;
	t_vector	tmp_n;
	t_vector	normal;

	// v = ft_mult_num_vector(1 / ft_lengthv(object.vectorperp), object.vectorperp);
	v = ft_multiply_vector_num(&object->axis, 1 / ft_vector_modul(&object->axis)); //axis

	// m = ft_dotprod(ft_substrv(crossp, object.center), v);
	tmp = ft_sub_vectors(&intersect->vec3, &object->pos);
	m = ft_vector_scalar(&tmp, &v);

	// normal = ft_substrv(ft_substrv(crossp, object.center), ft_mult_num_vector((m + object.k_paraboloid), v));
	tmp_n = ft_multiply_vector_num(&object->axis, m + object->k_paraboloid);
	normal = ft_sub_vectors(&tmp, &tmp_n);

	//normal = ft_norm_vector(normal);
	return(normal);
}