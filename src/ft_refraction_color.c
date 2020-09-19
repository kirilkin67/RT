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

void	raytrace_refraction(t_rtv *p, t_vector *intersect,
							t_cross *new, float color[][2])
{
	new->start = ft_multiply_vector_num(intersect, 1.001);
	new->id = ft_intersect_obj(p, &new->direct, &new->start, &new->dist);
	if (new->id == NO_INTERSECT)
		color[new->depth][0] = COLOR_BG_BL;
}

t_vector	refraction_ray(t_vector *intersect)
{
	t_vector	refraction_ray;

	refraction_ray = *intersect;
	ft_unit_vector(&refraction_ray);
	return (refraction_ray);
}

int		ft_refraction(t_rtv *p, t_vector *intersect, double min_refract)
{
	t_cross		new;
	float		color[p->depth_refract][2];

	new.direct = refraction_ray(intersect);
	new.depth = 0;
	while (new.depth < p->depth_refract && min_refract > 0.1)
	{
		raytrace_refraction(p, intersect, &new, color);
		if (new.id == NO_INTERSECT)
			break ;
		*intersect = new_intersect(intersect, &new.direct, new.dist);
		new.norm =
		calculate_vector_norm(p->object[new.id], intersect, &new.start);
		color[new.depth][0] = calculate_color(p, intersect, &new.norm, new.id);
		color[new.depth][1] = p->object[new.id]->refraction;
		min_refract *= p->object[new.id]->refraction;
		new.ref = *intersect;
		if (p->object[new.id]->reflection > 0)
			color[new.depth][0] = result_color(color[new.depth][0],
		ft_reflection(p, &new.ref, &new.norm), p->object[new.id]->reflection);
		if (p->object[new.id]->refraction <= 0)
			break ;
		new.depth += 1;
	}
	return (calculate_result_color(color, new.depth, p->depth_refract));
}

// int		ft_refraction(t_rtv *p, t_vector *intersect, t_vector *norm, int *id)
// {
// 	t_cross		new;
// 	int			depth;
// 	double		min_refract;
// 	float		color_r[p->depth_refract][2];
// 	t_vector	vec_reflect;

// 	// new_dir = ft_refraction_ray(intersect, norm, 1.0);
// 	new.direct = *intersect;
// 	ft_unit_vector(&new.direct);
// 	new.norm = *norm; // delete
// 	min_refract = p->object[*id]->refraction;
// 	depth = 0;
// 	while (depth < p->depth_refract && min_refract > 0.1)
// 	{
// 		new.start = ft_multiply_vector_num(intersect, 1.001);
// 		*id = ft_intersect_obj(p, &new.direct, &new.start, &new.dist);
// 		if (*id == NO_INTERSECT)
// 		{
// 			color_r[depth][0] = COLOR_BG_BL;
// 			break ;
// 		}
// 		*intersect = new_intersect(intersect, &new.direct, new.dist);
// 		new.norm = ft_calculate_vector_norm(p->object[*id], intersect, &new.start);
// 		color_r[depth][0] = ft_calculate_color(p, intersect, &new.norm, *id);
// 		color_r[depth][1] = p->object[*id]->refraction;
		
// 		if (p->object[*id]->reflection > 0)
// 		{
// 			vec_reflect = *intersect;
// 			// reflect = ft_reflection(p, &vec_reflect, &new.norm);
// 			color_r[depth][0] = result_color(color_r[depth][0],
// 		ft_reflection(p, &vec_reflect, &new.norm), p->object[*id]->reflection);
// 		}
// 		min_refract *= p->object[*id]->refraction;
// 		if (p->object[*id]->refraction <= 0)
// 			break ;
// 		depth += 1;
// 		// new_dir = ft_refraction_ray(&new_dir, norm, 1);
// 	}
// 	return (calculate_result_color(color_r, depth, p->depth_refract));
// }

// int	ft_calculate_refraction(t_rtv *p, t_vector *intersect, t_vector *norm, int *id)
// {
// 	t_vector	new_dir;
// 	t_vector	new_start;
// 	double		min_dist;
// 	float		color_r[p->depth_refract][2];
// 	int			depth;
// 	double		min_refract;

// 	// new_dir = ft_refraction_ray(intersect, norm, 1.0);
// 	new_dir = *intersect;
// 	ft_unit_vector(&new_dir);
// 	min_refract = p->object[*id]->refraction;
// 	depth = 0;
// 	while (depth < p->depth_refract && min_refract > 0.1 &&
// 		p->object[*id]->refraction > 0)
// 	{
// 		new_start = ft_multiply_vector_num(intersect, 1.01);
// 		*id = ft_intersect_obj(p, &new_dir, &new_start, &min_dist);
// 		if (*id == NO_INTERSECT)
// 		{
// 			color_r[depth][0] = COLOR_BG_BL;
// 			break ;
// 		}
// 		*intersect = new_intersect(intersect, &new_dir, min_dist);
// 		*norm = ft_calculate_vector_norm(p->object[*id], intersect, &new_start);
// 		color_r[depth][0] = ft_calculate_lighting(p, intersect, norm, *id);
// 		color_r[depth][1] = p->object[*id]->refraction;
// 		min_refract *= p->object[*id]->refraction;
// 		depth += 1;
// 		// new_dir = ft_refraction_ray(&new_dir, norm, 1);
// 	}
// 	return (calculate_reflection_color(color_r, depth, p->depth_refract));
// }

	// printf("%f, %f, %f\n", color[0][0], color[1][0], color[2][0]);
