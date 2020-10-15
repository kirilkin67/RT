#include "rtv1.h"

int			calculate_result_color(float color[][2], int depth, int max_depth)
{
	if (depth == max_depth)
		depth -= 1;
	while (depth > 0)
	{
		color[depth - 1][0] = result_color(color[depth - 1][0],
								color[depth][0], color[depth - 1][1]);
		depth -= 1;
	}
	return (int)color[0][0];
}

t_vector	ft_reflection_ray(t_vector *ray, t_vector *norm)
{
	t_vector reflection_ray;

	reflection_ray = *ray;
	// reflection_ray.x = ray->x;
	// reflection_ray.y = ray->y;
	// reflection_ray.z = ray->z;
	// ft_unit_vector(&reflection_ray);
	reflection_ray =
		ft_multiply_vector_num(norm, 2 * ft_vector_scalar(norm, ray));
	reflection_ray = ft_sub_vectors(ray, &reflection_ray);
	ft_unit_vector(&reflection_ray);
	return (reflection_ray);
}

/*
** Vector intersection относительно положения light
*/

t_vector	new_intersect(t_vector *intersect, t_vector *dir, double dist)
{
	t_vector	new_intersect;

	new_intersect = ft_multiply_vector_num(dir, dist);
	new_intersect = ft_add_vectors(intersect, &new_intersect);
	return (new_intersect);
}

void		raytrace_reflection(t_rtv *p, t_vector *intersect,
			t_start *new, float color[][2])
{
	new->start = ft_multiply_vector_num(intersect, 0.999);
	new->id = ft_intersect_objects(p, &new->direct, &new->start, &new->dist);
	if (new->id == NO_INTERSECT)
		color[new->depth][0] = NO_COLOR;
}

int			ft_reflection(t_rtv *p, t_vector *ray, t_vector *intersect, t_vector *norm)
{
	t_start		new;
	float		color[p->depth_mirror][2];
	double		min_refract;
	int			ref_color;

	new.direct = ft_reflection_ray(ray, norm);
	new.depth = 0;
	while (new.depth < p->depth_mirror)
	{
		
		// new.start = ft_multiply_vector_num(intersect, 0.999);
		new.start = new_start_vector(intersect, &new.direct, 0.001);
		new.id = ft_intersect_objects(p, &new.direct, &new.start, &new.dist);
		if (new.id == NO_INTERSECT)
		{
			color[new.depth][0] = NO_COLOR;
			break ;
		}
		// raytrace_reflection(p, intersect, &new, color);
		// if (new.id == NO_INTERSECT)
		// 	break ;
		*intersect = new_intersect(intersect, &new.direct, new.dist);
		new.norm =
		// calculate_vector_norm(p->object[new.id], intersect, &new.start);
		calculate_vector_norm(p->object[new.id], intersect);
		color[new.depth][0] = ft_local_color(p, intersect, &new.norm, new.id);
		color[new.depth][1] = p->object[new.id]->reflection;
		new.ref = *intersect;
		if (p->object[new.id]->refraction > 0)
		{
			min_refract = p->object[new.id]->refraction;
			ref_color = ft_refraction(p, &new.direct, &new.ref, &min_refract);
			color[new.depth][0] = result_color(color[new.depth][0], ref_color,
			p->object[new.id]->refraction);
		}

			// color[new.depth][0] = result_color(color[new.depth][0],
			// ft_refraction(p, &new.direct, &new.ref, p->object[new.id]->refraction),
			// p->object[new.id]->refraction);
		if (p->object[new.id]->reflection <= 0)
			break ;
		new.depth += 1;
		new.direct = ft_reflection_ray(&new.direct, &new.norm);
	}
	return (calculate_result_color(color, new.depth, p->depth_mirror));
}

// int		ft_reflection(t_rtv *p, t_vector *intersect, t_vector *norm, int *id)
// {
// 	t_cross		new;
// 	float		color[p->depth_mirror][2];
// 	int			depth;

// 	new.id = *id;
// 	new.direct = ft_reflection_ray(intersect, norm);
// 	depth = 0;
// 	while (depth < p->depth_mirror && p->object[new.id]->reflection > 0)
// 	{
// 		raytrace_reflection(p, intersect, &new);
// 		if (new.id == NO_INTERSECT)
// 		{
// 			color[depth][0] = NO_COLOR;
// 			break ;
// 		}
// 		*intersect = new_intersect(intersect, &new.direct, new.dist);
// 		new.norm = ft_calculate_vector_norm(p->object[new.id], intersect, &new.start);
// 		color[depth][0] = ft_calculate_lighting(p, intersect, &new.norm, new.id);
// 		color[depth][1] = p->object[new.id]->reflection;
// 		if (p->object[new.id]->reflection > 0)
// 			depth += 1;
// 		new.direct = ft_reflection_ray(&new.direct, &new.norm);
// 	}
// 	return (calculate_result_color(color, depth, p->depth_mirror));
// }
