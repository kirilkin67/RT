#include "rtv1.h"

int			ft_pixel_color(int color, float percent)
{
	int		red;
	int		green;
	int		blue;		

	if (percent > 1)
		percent = 1.0;
	red = ((color >> 16) & 0xFF) * percent;
	green = ((color >> 8) & 0xFF) * percent;
	blue = (color & 0xFF) * percent;
	return (((int)red << 16) | ((int)green << 8) | (int)blue);
}

int		ft_illumination_point(t_light *l, t_object **obj, t_vector *v, int n)
{
	t_vector	light;
	t_vector	median;
	t_object	tmp;
	float		shade;
	float		shine;
	float		len_light;
	float		len;
	int			i;

	light = ft_subtraction_vector(&l->pos, v);
	median = ft_subtraction_vector(&light, v);
	len_light = ft_vector_modul(&light);
	ft_unit_vector(&light);
	i = 0;
	while (obj[i] != NULL)
	{
		tmp = *obj[i];
		object_data(&tmp, v);
		len = ft_ray_trace_object(&light, &tmp);
		if (len == -1 || len < 0.1 || len > len_light)
			i += 1;
		else
			return (ft_pixel_color(obj[n]->color, AMBIENT));
	}
	// median = ft_subtraction_vector(&light, v);
	ft_unit_vector(&obj[n]->norm);
	// ft_unit_vector(&light);
	shade = ft_vector_scalar(&obj[n]->norm, &light);
	if (shade < 0)
		shade = 0;
	shine = ft_vector_scalar(&obj[n]->norm, &median) / ft_vector_modul(&median);
	if (shine < 0)
		shine = 0;
	shade = AMBIENT + l->intensity * shade + l->intensity * pow(shine, obj[n]->specular);

	return (ft_pixel_color(obj[n]->color, shade));
}
