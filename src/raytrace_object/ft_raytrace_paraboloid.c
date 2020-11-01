#include "rt.h"

void	calculate_a_b_c_paraboloid(t_object *paraboloid, t_vector *ray)
{
	t_vector	oc;
	t_vector	normal;

	oc = ft_multiply_vector_num(&paraboloid->pos, -1);
	normal = paraboloid->axis;
	ft_unit_vector(&normal);
	paraboloid->discr.a = ft_vector_scalar(ray, ray) - 
		(ft_vector_scalar(ray, &normal) * ft_vector_scalar(ray, &normal));

	paraboloid->discr.b = 2 * (ft_vector_scalar(&oc, ray) - 
		(ft_vector_scalar(ray, &normal) * (ft_vector_scalar(&oc, &normal) + 
		2 * paraboloid->k_paraboloid)));
	
	paraboloid->discr.c = ft_vector_scalar(&oc, &oc) - 
		(ft_vector_scalar(&oc, &normal) * 
		(ft_vector_scalar(&oc, &normal) + 4 * paraboloid->k_paraboloid));
}

t_cross		ft_intersect_ray_paraboloid(t_object *paraboloid, t_vector *ray)
{
	t_cross		result;
	double	check;

	result.id = NO_INTERSECT;
	calculate_a_b_c_paraboloid(paraboloid, ray);
	ft_solve_quadratic_equation(&paraboloid->discr);
	if (paraboloid->discr.discr < 0.0)
		return (result);
	check = check_intersect(ray, &paraboloid->pos, &paraboloid->axis, paraboloid->discr.d_1);
	if (paraboloid->max >= check && check >= paraboloid->min)
	{
		result.id = INTERSECT;
		result.len = paraboloid->discr.d_1;
		return (result);
	}
	check = check_intersect(ray, &paraboloid->pos, &paraboloid->axis, paraboloid->discr.d_2);
	if (paraboloid->max >= check && check >= paraboloid->min)
	{
		result.id = INTERSECT;
		result.len = paraboloid->discr.d_2;
	}
	return (result);
}
