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

t_cross	raytrace_refraction(t_rtv *p, t_vector *intersect, t_start *new, float color[][2])
{
	t_cross		refract;

	new->start = ft_multiply_vector_num(intersect, 1.001);
	refract = ft_intersect_objects(p, &new->direct, &new->start);
	if (refract.id == NO_INTERSECT)
		color[new->depth][0] = COLOR_BG_BL;
		// color[new->depth][0] = NO_COLOR;
	else
	{
		refract.vec3 = ft_multiply_vector_num(&new->direct, refract.len);
		*intersect = ft_add_vectors(intersect, &refract.vec3);
		refract.vec3 = *intersect;
	}
	return (refract);
}

int		ft_refraction(t_rtv *p, t_vector *ray, t_vector *intersect, double *min_refract)
{
	t_cross		refract;
	t_start		new;
	float		color[p->depth_refract][2];
	int ref_color;

	new.direct = *ray;
	new.depth = 0;
	while (new.depth < p->depth_refract && *min_refract > 0.1)
	{
		/*
		new.start = ft_multiply_vector_num(intersect, 1.001);
		refract = ft_intersect_objects(p, ray, &new.start);
		if (refract.id == NO_INTERSECT)
		{
			color[new.depth][0] = COLOR_BG_BL;
			break ;
		}
		refract.vec3 = ft_multiply_vector_num(ray, refract.len);
		*intersect = ft_add_vectors(intersect, &refract.vec3);
		refract.vec3 = *intersect;
		*/

		refract = raytrace_refraction(p, intersect, &new, color);
		if (refract.id == NO_INTERSECT)
			break ;
		new.norm = calculate_vector_norm(p->object[refract.id], &refract, ray);
		color[new.depth][0] = ft_local_color(p, &refract, &new.norm);
		color[new.depth][1] = p->object[refract.id]->refraction;
		
		new.ref = *intersect;
		// *min_refract *= p->object[new.id]->refraction;
		if (p->object[refract.id]->reflection > 0)// && *min_refract > 0.1)
		{
			ref_color = ft_reflection(p, ray, &new.ref, &new.norm);
			color[new.depth][0] = result_color(color[new.depth][0],
		ref_color, p->object[refract.id]->reflection);
		}

		if (p->object[refract.id]->refraction <= 0)
			break ;
		*min_refract *= p->object[refract.id]->refraction;
		new.depth += 1;
	}
	return (calculate_result_color(color, new.depth, p->depth_refract));
}


// int		ft_refraction(t_rtv *p, t_vector *intersect, double min_refract)
// {
// 	t_cross		new;
// 	float		color[p->depth_refract][2];

// 	new.direct = refraction_ray(intersect);
// 	new.depth = 0;
// 	while (new.depth < p->depth_refract && min_refract > 0.1)
// 	{
// 		raytrace_refraction(p, intersect, &new, color);
// 		if (new.id == NO_INTERSECT)
// 			break ;
// 		*intersect = new_intersect(intersect, &new.direct, new.dist);
// 		new.norm =
// 		calculate_vector_norm(p->object[new.id], intersect, &new.start);
// 		color[new.depth][0] = calculate_color(p, intersect, &new.norm, new.id);
// 		color[new.depth][1] = p->object[new.id]->refraction;
// 		min_refract *= p->object[new.id]->refraction;
// 		new.ref = *intersect;
// 		if (p->object[new.id]->reflection > 0)
// 			color[new.depth][0] = result_color(color[new.depth][0],
// 		ft_reflection(p, &new.ref, &new.norm), p->object[new.id]->reflection);
// 		if (p->object[new.id]->refraction <= 0)
// 			break ;
// 		new.depth += 1;
// 	}
// 	return (calculate_result_color(color, new.depth, p->depth_refract));
// }

	// printf("%f, %f, %f\n", color[0][0], color[1][0], color[2][0]);
