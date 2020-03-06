#include "rtv1.h"

int			ft_pixel_color(int color, double percent)
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

int		ft_illumination_point(t_light *l, t_object *obj, t_vector *v)
{
	t_vector	light;
	t_vector	median;
	double		shade;
	double		shine;

	light = ft_subtraction_vector(&l->pos, v);
	median = ft_subtraction_vector(&light, v);
	shade = ft_vector_scalar(&obj->norm, &light) /\
			ft_vector_modul(&obj->norm) / ft_vector_modul(&light);
	if (shade < 0)
		shade = 0;
	shine = ft_vector_scalar(&obj->norm, &median) /\
			ft_vector_modul(&obj->norm) / ft_vector_modul(&median);
	if (shine < 0)
		shine = 0;
	shade = AMBIENT + l->intensity * shade + l->intensity * pow(shine, obj->specular);

	return (ft_pixel_color(obj->color, shade));
}
