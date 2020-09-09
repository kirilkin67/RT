#include "rtv1.h"

t_vector	ft_refraction_ray(t_vector *dir, t_vector *norm, float n2)
{
	double		k_refraction;
	double		const_1;
	double		const_2;
	t_vector	refraction_ray;
	t_vector	tmp;

	k_refraction = N_1 / n2;
	refraction_ray = *dir;
	ft_unit_vector(&refraction_ray);
	const_1 = ft_vector_scalar(dir, norm);
	const_2 = sqrt(1 - (k_refraction * k_refraction) * (1 - const_1 * const_1));
	refraction_ray = ft_multiply_vector_num(&refraction_ray, k_refraction);
	tmp = ft_multiply_vector_num(norm, const_2 + k_refraction * const_1);
	refraction_ray = ft_sub_vectors(&refraction_ray, &tmp);
	return (refraction_ray);
}

int	ft_calculate_refraction(t_rtv *p, t_vector *intersect, t_vector *norm, int *id)
{
	t_vector	new_dir;
	t_vector	new_start;
	double		min_dist;
	float		color_r[DEPTH][2];
	int			depth;

	// new_dir = ft_refraction_ray(intersect, norm, 1.5);
	new_dir = *intersect;
	depth = 0;
	while (depth < DEPTH && p->object[*id]->refraction > 0)
	{
		new_start = ft_multiply_vector_num(intersect, 1.001);
		*id = ft_intersect_obj(p, &new_dir, &new_start, &min_dist);
		if (*id == NO_INTERSECT)
		{
			color_r[depth][0] = COLOR_BG1;
			break ;
		}
		*intersect = new_intersect(intersect, &new_dir, min_dist);
		*norm = ft_calculate_vector_norm(p->object[*id], intersect);
		color_r[depth][0] = ft_calculate_lighting(p, intersect, norm, *id);
		color_r[depth][1] = p->object[*id]->refraction;
		depth += 1;
		new_dir = ft_refraction_ray(&new_dir, norm, 1);
	}
	return (calculate_reflection_color(color_r, depth));
}
