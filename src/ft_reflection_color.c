#include "rtv1.h"

// void		add_reflection_color(float color[][2], int *depth)
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

void		add_reflection_color(float color[][2], int depth)
{
	if (depth == DEPTH)
		depth -= 1;
	while (depth > 0)
	{
		color[depth - 1][0] = \
		reflection_color(color[depth - 1][0], color[depth][0], color[depth - 1][1]);
		depth -= 1;
	}
}

t_vector	ft_reflection_ray(t_vector *dir, t_vector *norm)
{
	t_vector ray;

	// ray = *dir;
	ray.x = dir->x;
	ray.y = dir->y;
	ray.z = dir->z;
	ft_unit_vector(&ray);
	ray = ft_multiply_vector_num(norm, 2 * ft_vector_scalar(norm, dir));
	ray = ft_sub_vectors(dir, &ray);
	ft_unit_vector(&ray);
	return (ray);
}

t_vector	new_intersect(t_vector *intersect, t_vector *dir, double dist)
{
	t_vector	new_intersect;

	new_intersect = ft_multiply_vector_num(dir, dist);
	new_intersect = ft_add_vectors(intersect, &new_intersect);//положение light
	return (new_intersect);
}

int	ft_calculate_reflection(t_rtv *p, t_vector *intersect, t_vector *norm, int *id)
{
	t_vector	new_dir;
	t_vector	new_start;
	double		min_dist;
	float		color_r[DEPTH][2];
	int			n;

	n = 0;
	while (n < DEPTH && p->object[*id]->reflection > 0)
	{
		new_dir = ft_reflection_ray(intersect, norm);
		new_start = ft_multiply_vector_num(intersect, 0.999);
		// new_dir = ft_reflection_ray(intersect, norm);
		*id = ft_intersect_obj(p, &new_dir, &new_start, &min_dist);
		if (*id == NO_INTERSECT)
		{
			color_r[n][0] = -1;
			break ;
		}
		*intersect = new_intersect(intersect, &new_dir, min_dist);
		// *norm = ft_calculate_vector_norm(p, *id, ray);
		*norm = ft_calculate_vector_norm(p->object[*id], intersect);
		if (n > 1)
			// printf("%d, %c, %f, %f, %f\n", n, p->object[*id]->id, norm->x, norm->y, norm->z);
			printf("%f, %f\n", color_r[0][0], color_r[1][0]);
		color_r[n][0] = ft_calculate_lighting(p, intersect, norm, *id);
		color_r[n][1] = p->object[*id]->reflection;
		n += 1;
	}
	// add_reflection_color(color_r, &n);
	add_reflection_color(color_r, n);
	return (color_r[0][0]);
}

// int		ft_calculate_reflection(t_rtv *p, t_vector *intersect, t_vector *norm, int *id)
// {
// 	t_vector	new_dir;
// 	t_vector	new_start;
// 	double		min_dist;
// 	int			color;

// 	new_dir = ft_reflection_ray(intersect, norm);
// 	new_start = ft_multiply_vector_num(intersect, 0.999);
// 	*id = ft_intersect_obj(p, &new_dir, &new_start, &min_dist);
// 	if (*id == -1)
// 		return (-1);
// 	*intersect = new_intersect(intersect, &new_dir, min_dist);
// 	*norm = calculate_vector_norm(p, *id, intersect);
// 	color = ft_calculate_lighting(p, intersect, norm, *id);
// 	return (color);
// }
