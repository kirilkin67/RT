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

t_vector	ft_reflection_ray(t_vector *dir, t_vector *norm)
{
	t_vector reflection_ray;

	// reflection_ray = *dir;
	reflection_ray.x = dir->x;
	reflection_ray.y = dir->y;
	reflection_ray.z = dir->z;
	ft_unit_vector(&reflection_ray);
	reflection_ray =
		ft_multiply_vector_num(norm, 2 * ft_vector_scalar(norm, dir));
	reflection_ray = ft_sub_vectors(dir, &reflection_ray);
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
			t_cross *new, float color[][2])
{
	new->start = ft_multiply_vector_num(intersect, 0.999);
	new->id = ft_intersect_obj(p, &new->direct, &new->start, &new->dist);
	if (new->id == NO_INTERSECT)
		color[new->depth][0] = NO_COLOR;
}

int			ft_reflection(t_rtv *p, t_vector *intersect, t_vector *norm)
{
	t_cross		new;
	float		color[p->depth_mirror][2];

	new.direct = ft_reflection_ray(intersect, norm);
	new.depth = 0;
	while (new.depth < p->depth_mirror)
	{
		raytrace_reflection(p, intersect, &new, color);
		if (new.id == NO_INTERSECT)
			break ;
		// new.ref = *intersect;
		*intersect = new_intersect(intersect, &new.direct, new.dist);
		new.norm =
		calculate_vector_norm(p->object[new.id], intersect, &new.start);
		color[new.depth][0] = calculate_color(p, intersect, &new.norm, new.id);
		color[new.depth][1] = p->object[new.id]->reflection;
		new.ref = ft_multiply_vector_num(&new.direct, new.dist);
		if (p->object[new.id]->refraction > 0)
		{
			int ref_color = ft_refraction(p, &new.ref, p->object[new.id]->refraction);
			color[new.depth][0] = result_color(color[new.depth][0],ref_color,
			p->object[new.id]->refraction);
		}

			// color[new.depth][0] = result_color(color[new.depth][0],
			// ft_refraction(p, &new.direct, p->object[new.id]->refraction),
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
