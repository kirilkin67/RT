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

int		ft_illuminat_point_1(t_rtv *p, t_vector *intersect, t_vector *norm, int n)
{
	t_vector	new_ray;
	t_vector	median;
	float		shade;
	float		shine;

	shine =  0.0;
	new_ray = ft_subtraction_vector(&p->light->pos, intersect);
	median = ft_subtraction_vector(&new_ray, intersect);
	if (is_point_shadow(p, intersect, &new_ray) == 1)
		return (ft_pixel_color(p->object[n]->color, AMBIENT));
	else	
		// ft_unit_vector(&new_ray);
		shade = ft_vector_scalar(norm, &new_ray);
	if (shade < 0)
		shade = 0;
	if (shade != 0)
		shine = ft_vector_scalar(norm, &median) / ft_vector_modul(&median);
	if (shine < 0)
		shine = 0;
	shade = AMBIENT + p->light->intensity * (shade + powf(shine, p->object[n]->specular));	
	return (ft_pixel_color(p->object[n]->color, shade)); 
}

float		ft_illuminat_point(t_rtv *p, t_light *light, t_vector *intersect, t_vector *norm, int n)
{
	t_vector	new_ray;
	t_vector	median;
	float		shade;
	float		shine;

	shine =  0.0;
	new_ray = ft_subtraction_vector(&light->pos, intersect);
	median = ft_subtraction_vector(&new_ray, intersect);
	if (is_point_shadow(p, intersect, &new_ray) == 1)
		return (AMBIENT);
	else	
		shade = ft_vector_scalar(norm, &new_ray);
	if (shade < 0)
		shade = 0;
	if (shade != 0)
		shine = ft_vector_scalar(norm, &median) / ft_vector_modul(&median);
	if (shine < 0)
		shine = 0;
	shade = AMBIENT + light->intensity * (shade + powf(shine, p->object[n]->specular));	
	return (shade); 
}

int		ft_calculate_lighting(t_rtv *p, t_vector *intersect, t_vector *norm, int n)
{
	t_light	*cursor;
	float	shade;

	shade = 0.0;
	cursor = p->light;
	while (cursor != NULL)
	{
		shade += ft_illuminat_point(p, cursor, intersect, norm, n);
		cursor = cursor->next;
	}
	return (ft_pixel_color(p->object[n]->color, shade));
}
