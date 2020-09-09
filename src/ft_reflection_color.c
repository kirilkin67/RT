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

int			calculate_reflection_color(float color[][2], int depth)
{
	if (depth == DEPTH)
		depth -= 1;
	while (depth > 0)
	{
		color[depth - 1][0] = reflection_color(color[depth - 1][0],
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
	t_vector	new_dir;
	t_vector	new_start;
	double		min_dist;
	float		color_r[DEPTH][2];
	int			depth;

	new_dir = ft_reflection_ray(intersect, norm);
	depth = 0;
	while (depth < DEPTH && p->object[*id]->reflection > 0)
	{
		new_start = ft_multiply_vector_num(intersect, 0.999);
		*id = ft_intersect_obj(p, &new_dir, &new_start, &min_dist);
		if (*id == NO_INTERSECT)
		{
			color_r[depth][0] = -1;
			break ;
		}
		*intersect = new_intersect(intersect, &new_dir, min_dist);
		*norm = ft_calculate_vector_norm(p->object[*id], intersect);
		color_r[depth][0] = ft_calculate_lighting(p, intersect, norm, *id);
		color_r[depth][1] = p->object[*id]->reflection;
		depth += 1;
		new_dir = ft_reflection_ray(&new_dir, norm);
	}
	return (calculate_reflection_color(color_r, depth));
}
