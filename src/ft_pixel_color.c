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

// float	ft_shade_point(t_light *l, t_object *obj, t_vector *light, t_vector *m)
// {
// 	float		shade;
// 	float		shine;

// 	shade = ft_vector_scalar(&obj->norm, light);
// 	if (shade < 0)
// 		shade = 0;
// 	shine = ft_vector_scalar(&obj->norm, m) / ft_vector_modul(m);
// 	if (shine < 0)
// 		shine = 0;
// 	shade = AMBIENT + l->intensity * shade +\
// 			l->intensity * powf(shine, obj->specular);
// 	return (shade);
// }

float	ft_shade_point(t_light *l, t_object *obj, t_vector *light, t_vector *m, t_vector *norm)
{
	float		shade;
	float		shine;

	shade = ft_vector_scalar(norm, light);
	if (shade < 0)
		shade = 0;
	shine = ft_vector_scalar(norm, m) / ft_vector_modul(m);
	if (shine < 0)
		shine = 0;
	shade = AMBIENT + l->intensity * shade +\
			l->intensity * powf(shine, obj->specular);
	return (shade);
}

int		illuminat_point(t_rtv *p, t_vector *intersect, t_vector *norm, int n)
{
	t_vector	light;
	t_vector	median;
	t_object	tmp;
	float		len_light;
	int			i;

	light = ft_subtraction_vector(&p->light->pos, intersect);
	median = ft_subtraction_vector(&light, intersect);
	*intersect = ft_multiply_vector_num(intersect, 0.999);
	len_light = ft_vector_modul(&light);
	ft_unit_vector(&light);
	i = 0;
	while (p->object[i] != NULL)
	{
		tmp = *p->object[i];
		object_data(&tmp, intersect);
		p->len = ft_ray_trace_object(&light, &tmp);
		if (p->len == -1 || p->len < 0.001 || p->len > len_light)
			i += 1;
		else
			return (ft_pixel_color(p->object[n]->color, AMBIENT));
	}
	p->shade = ft_shade_point(p->light, p->object[n], &light, &median, norm);
	return (ft_pixel_color(p->object[n]->color, p->shade)); 
}
