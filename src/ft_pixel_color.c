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

float	ft_shade_point(t_light *l, t_object *obj, t_vector *light, t_vector *m)
{
	float		shade;
	float		shine;

	shade = ft_vector_scalar(&obj->norm, light);
	if (shade < 0)
		shade = 0;
	shine = ft_vector_scalar(&obj->norm, m) / ft_vector_modul(m);
	if (shine < 0)
		shine = 0;
	shade = AMBIENT + l->intensity * shade +\
			l->intensity * powf(shine, obj->specular);
	return (shade);
}

int		illuminat_point(t_light *l, t_object **obj, t_vector *v, int n)
{
	t_vector	light;
	t_vector	median;
	t_object	tmp;
	float		shade;
	float		len_light;
	float		len;
	int			i;

	light = ft_subtraction_vector(&l->pos, v);
	median = ft_subtraction_vector(&light, v);
	*v = ft_multiply_vector_num(v, 0.999);
	len_light = ft_vector_modul(&light);
	ft_unit_vector(&light);
	i = 0;
	while (obj[i] != NULL)
	{
		tmp = *obj[i];
		// tmp = (t_object *)malloc(sizeof(t_object));
		// ft_memcpy((void *)tmp, (void *)obj[i], sizeof(t_object));
		object_data(&tmp, v);
		len = ft_ray_trace_object(&light, &tmp);
		if (len == -1 || len < 0.001 || len > len_light)
			i += 1;
		else
			return (ft_pixel_color(obj[n]->color, AMBIENT));
	}
	shade = ft_shade_point(l, obj[n], &light, &median);
	return (ft_pixel_color(obj[n]->color, shade));
}
