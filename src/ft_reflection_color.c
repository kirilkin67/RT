#include "rtv1.h"

t_vector	reflection_ray(t_vector *dir, t_vector *norm)
{
	t_vector ray;

	ray = *dir;
	ft_unit_vector(&ray);
	ray = ft_multiply_vector_num(norm, 2 * ft_vector_scalar(norm, dir));
	ray = ft_subtraction_vector(dir, &ray);
	return (ray);
}

static int	get_light(int color1, int color2, float reflection)
{
	return ((int)(color1 * (1 - reflection) + color2 * reflection));
}

int		reflection_color(int color1, int color2, float reflection)
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

int		ft_calculate_reflection(t_rtv *p, t_vector *intersect, t_vector *norm)
{
	t_object	tmp;
	t_vector	new_dir;
	t_vector	new_start;
	t_vector	new_intersect;
	t_vector	new_norm;
	double		min_dist;
	double		len_dist;
	int			color;
	int			id;
	int			n;

	id = -1;
	min_dist = INT_MAX;
	new_dir = reflection_ray(intersect, norm);
	ft_unit_vector(&new_dir);
	new_start = ft_multiply_vector_num(intersect, 0.999);
	n = 0;
	while (n < p->num)
	{
		tmp = *p->object[n];
		object_data(&tmp, &new_start);
		len_dist = ft_ray_trace_object(&new_dir, &tmp);
		if (len_dist != -1 && len_dist > 0.001f && len_dist < min_dist)
		{
			min_dist = len_dist;
			id = n;
		}
		n += 1;
	}
	if (id == -1)
		return (-1);
	new_intersect = ft_multiply_vector_num(&new_dir, min_dist);
	new_intersect = ft_add_vector(intersect, &new_intersect);//положурие light
	new_norm = calculate_vector_norm(p, id, &new_intersect);
	color = ft_calculate_lighting(p, &new_intersect, &new_norm, id);
	return (color);
}