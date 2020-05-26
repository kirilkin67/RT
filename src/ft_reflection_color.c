#include "rtv1.h"

t_vector	reflection_ray(t_vector *dir, t_vector *norm)
{
	t_vector ray;

	ray = *dir;
	ft_unit_vector(&ray);
	ray = ft_multiply_vector_num(norm, 2 * ft_vector_scalar(norm, dir));
	ray = ft_subtraction_vector(dir, &ray);
	ft_unit_vector(&ray);
	return (ray);
}

int			get_light(int color1, int color2, float reflection)
{
	if (reflection > 1.0)
		reflection = 1.0;
	return ((int)(color1 * (1.0 - reflection) + color2 * reflection));
}

int			reflection_color(int color1, int color2, float reflection)
{
	float	red;
	float	green;
	float	blue;

	if (color1 == color2 || color2 < 0)
		return (color1);
	red = get_light((color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF, reflection);
	green = get_light((color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF, reflection);
	blue = get_light(color1 & 0xFF, color2 & 0xFF, reflection);

	return (((int)red << 16) | ((int)green << 8) | (int)blue);
}

t_vector	new_intersect(t_vector *intersect, t_vector *dir, double dist)
{
	t_vector	new_intersect;

	new_intersect = ft_multiply_vector_num(dir, dist);
	new_intersect = ft_add_vector(intersect, &new_intersect);//положение light
	return (new_intersect);
}

int		ft_calculate_reflection(t_rtv *p, t_vector *intersect, t_vector *norm, int *id)
{
	t_vector	new_dir;
	t_vector	new_start;
	double		min_dist;
	int			color[DEPTH];
	float		reflect[DEPTH];
	int			n;

	n = 0;
	while (n < DEPTH && p->object[*id]->reflection > 0)
	{
		new_dir = reflection_ray(intersect, norm);
		new_start = ft_multiply_vector_num(intersect, 0.999);
		*id = ft_intersect_obj(p, &new_dir, &new_start, &min_dist);
		if (*id == -1)
		{
			color[n] = -1;
			break ;
		}
		*intersect = new_intersect(intersect, &new_dir, min_dist);
		*norm = calculate_vector_norm(p, *id, intersect);
		color[n] = ft_calculate_lighting(p, intersect, norm, *id);
		reflect[n] = p->object[*id]->reflection;
		n += 1;
	}
	if (n == DEPTH)
		n = 2;
	while (n > 0)
	{
		color[n - 1] = reflection_color(color[n - 1], color[n], reflect[n - 1]);
		n -= 1;
	}
	return (color[n]);
}

// int		ft_calculate_reflection(t_rtv *p, t_vector *intersect, t_vector *norm, int *id)
// {
// 	t_vector	new_dir;
// 	t_vector	new_start;
// 	double		min_dist;
// 	int			color;

// 	new_dir = reflection_ray(intersect, norm);
// 	new_start = ft_multiply_vector_num(intersect, 0.999);
// 	*id = ft_intersect_obj(p, &new_dir, &new_start, &min_dist);
// 	if (*id == -1)
// 		return (-1);
// 	*intersect = new_intersect(intersect, &new_dir, min_dist);
// 	*norm = calculate_vector_norm(p, *id, intersect);
// 	color = ft_calculate_lighting(p, intersect, norm, *id);
// 	return (color);
// }

// int		ft_calculate_reflection(t_rtv *p, t_vector *intersect, t_vector *norm)
// {
// 	t_vector	new_dir;
// 	t_vector	new_start;
// 	double		min_dist;
// 	int			color;
// 	int			id;

// 	new_dir = reflection_ray(intersect, norm);
// 	new_start = ft_multiply_vector_num(intersect, 0.999);
// 	id = ft_intersect_obj(p, &new_dir, &new_start, &min_dist);
// 	if (id == -1)
// 		return (-1);
// 	*intersect = new_intersect(intersect, &new_dir, min_dist);
// 	*norm = calculate_vector_norm(p, id, intersect);
// 	color = ft_calculate_lighting(p, intersect, norm, id);
// 	// while (depth > 0 && p->object[id]->reflection > 0)
// 	// {
// 	// ref_color = ft_calculate_reflection(p, intersect, norm);
// 	// if (ref_color > 0 )
// 	// 	color = reflection_color(color, ref_color, p->object[id]->reflection);
// 	// depth -= 1;
// 	// }
// 	return (color);
// }
