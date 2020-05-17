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
	return ((int)(color1 * (1.0 - reflection) + color2 * reflection));
}

int			reflection_color(int color1, int color2, float reflection)
{
	float	red;
	float	green;
	float	blue;

	if (color1 == color2)
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

// int		ft_calculate_reflection(t_rtv *p, t_vector *intersect, t_vector *norm)
// {
// 	t_vector	new_dir;
// 	t_vector	new_start;
// 	double		min_dist;
// 	int			color;
// 	int 		ref_color = 0;
// 	int			id;
// 	int n = 1;

// 	new_dir = reflection_ray(intersect, norm);
// 	new_start = ft_multiply_vector_num(intersect, 0.999);
// 	id = ft_intersect_obj(p, &new_dir, &new_start, &min_dist);
// 	if (id == -1)
// 		return (-1);
// 	*intersect = new_intersect(intersect, &new_dir, min_dist);
// 	*norm = calculate_vector_norm(p, id, intersect);
// 	color = ft_calculate_lighting(p, intersect, norm, id);
// 	while (n > 0)
// 	{
// 	if (p->object[id]->reflection > 0)
// 		ref_color = ft_calculate_reflection(p, intersect, norm);
// 	if (ref_color > 0 )
// 		color = reflection_color(color, ref_color, p->object[id]->reflection);
// 	n -= 1;
// 	}
// 	return (color);
// }

int		ft_calculate_reflection(t_rtv *p, t_vector *intersect, t_vector *norm)
{
	t_vector	new_dir;
	t_vector	new_start;
	// t_vector	new_intersect;
	// t_vector	new_norm;
	double		min_dist;
	int			color;
	int			id;

	new_dir = reflection_ray(intersect, norm);
	new_start = ft_multiply_vector_num(intersect, 0.999);
	id = ft_intersect_obj(p, &new_dir, &new_start, &min_dist);
	if (id == -1)
		return (-1);
	// new_intersect = ft_multiply_vector_num(&new_dir, min_dist);
	// new_intersect = ft_add_vector(intersect, &new_intersect);//положение light
	// new_norm = calculate_vector_norm(p, id, &new_intersect);
	// color = ft_calculate_lighting(p, &new_intersect, &new_norm, id);
	*intersect = new_intersect(intersect, &new_dir, min_dist);
	*norm = calculate_vector_norm(p, id, intersect);
	color = ft_calculate_lighting(p, intersect, norm, id);
	return (color);
}
