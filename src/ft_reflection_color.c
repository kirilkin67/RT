#include "rtv1.h"

// add_reflection_color(color_r, &n);

// void		calculate_reflection_color(float color[][2], int *depth)
// {
// 	int	n;

// 	n = *depth;
// 	if (n == DEPTH)
// 		n -= 1;
// 	while (n > 0)
// 	{
// 		color[n - 1][0] = \
// 		reflection_color(color[n - 1][0], color[n][0], color[n - 1][1]);
// 		n -= 1;
// 	}
// 	*depth = n;
// }

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

int			ft_calculate_reflection(t_rtv *p, t_vector *intersect,
	t_vector *norm, int *id)
{
	t_cross		new;
	double		min_dist;
	float		color_r[p->depth_mirror][2];
	int			depth;

	new.id = *id;
	new.direct = ft_reflection_ray(intersect, norm);
	depth = 0;
	while (depth < p->depth_mirror && p->object[new.id]->reflection > 0)
	{
		new.start = ft_multiply_vector_num(intersect, 0.999);
		new.id = ft_intersect_obj(p, &new.direct, &new.start, &min_dist);
		if (new.id == NO_INTERSECT)
		{
			color_r[depth][0] = NO_COLOR;
			break ;
		}
		*intersect = new_intersect(intersect, &new.direct, min_dist);
		new.norm = ft_calculate_vector_norm(p->object[new.id], intersect, &new.start);
		color_r[depth][0] = ft_calculate_lighting(p, intersect, &new.norm, new.id);
		color_r[depth][1] = p->object[new.id]->reflection;
		if (p->object[new.id]->reflection > 0)
			depth += 1;
		new.direct = ft_reflection_ray(&new.direct, &new.norm);
	}
	return (calculate_result_color(color_r, depth, p->depth_mirror));
}
