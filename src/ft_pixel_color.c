#include "rtv1.h"

int		ft_pixel_color(int color, float percent)
{
	float	red;
	float	green;
	float	blue;

	if (percent > 1)
		percent = 1.0;
	red = ((color >> 16) & 0xFF) * percent;
	green = ((color >> 8) & 0xFF) * percent;
	blue = (color & 0xFF) * percent;
	return (((int)red << 16) | ((int)green << 8) | (int)blue);
}

int		is_point_shadow(t_rtv *p, t_vector *intersect, t_vector *ray)
{
	t_object	tmp;
	float		len_light;
	float		len;
	int			n;

	len_light = ft_vector_modul(ray);
	ft_unit_vector(ray);
	*intersect = ft_multiply_vector_num(intersect, 0.999);
	n = 0;
	while (p->object[n] != NULL)
	{
		tmp = *p->object[n];
		object_data(&tmp, intersect);
		len = ft_ray_trace_object(ray, &tmp);
		if (len == -1 || len < 0.001 || len > len_light)
			n += 1;
		else
			return (1);
	}
	return (-1);
}

int		ft_illuminat_point(t_rtv *p, t_vector *intersect, t_vector *norm, int n)
{
	t_vector	new_ray;
	t_vector	median;
	float		shade;
	float		shine;

	new_ray = ft_subtraction_vector(&p->light->pos, intersect);
	median = ft_subtraction_vector(&new_ray, intersect);
	if (is_point_shadow(p, intersect, &new_ray) == 1)
		return (ft_pixel_color(p->object[n]->color, AMBIENT));
	else
	{
		// ft_unit_vector(&new_ray);
		shade = ft_vector_scalar(norm, &new_ray);
		if (shade < 0)
			shade = 0;
		if (shade != 0)
			shine = ft_vector_scalar(norm, &median) / ft_vector_modul(&median);
		if (shine < 0)
			shine = 0;
		shade = AMBIENT + p->light->intensity * (shade + powf(shine, p->object[n]->specular));
	}
	return (ft_pixel_color(p->object[n]->color, shade)); 
}

// float	ft_shade_point(t_light *l, t_object *obj, t_vector *light, t_vector *m, t_vector *norm)
// {
// 	float		shade;
// 	float		shine;

// 	shade = ft_vector_scalar(norm, light);
// 	if (shade < 0)
// 		shade = 0;
// 	if (shade != 0)
// 		shine = ft_vector_scalar(norm, m) / ft_vector_modul(m);
// 	if (shine < 0)
// 		shine = 0;
// 	shade = AMBIENT + l->intensity * (shade + powf(shine, obj->specular));
// 	return (shade);
// }

// int		illuminat_point(t_rtv *p, t_vector *intersect, t_vector *norm, int n)
// {
// 	t_vector	new_ray;
// 	t_vector	median;
// 	t_object	tmp;
// 	float		len_light;
// 	int			i;

// 	new_ray = ft_subtraction_vector(&p->light->pos, intersect);
// 	median = ft_subtraction_vector(&new_ray, intersect);
// 	*intersect = ft_multiply_vector_num(intersect, 0.999);
// 	len_light = ft_vector_modul(&new_ray);
// 	ft_unit_vector(&new_ray);
// 	i = 0;
// 	while (p->object[i] != NULL)
// 	{
// 		tmp = *p->object[i];
// 		object_data(&tmp, intersect);
// 		p->len = ft_ray_trace_object(&new_ray, &tmp);
// 		if (p->len == -1 || p->len < 0.001 || p->len > len_light)
// 			i += 1;
// 		else
// 			return (ft_pixel_color(p->object[n]->color, AMBIENT));
// 	}
// 	p->shade = ft_shade_point(p->light, p->object[n], &new_ray, &median, norm);
// 	return (ft_pixel_color(p->object[n]->color, p->shade));
// }
