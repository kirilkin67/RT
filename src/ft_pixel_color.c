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

int		ft_illumination_point(t_light *l, t_sphere *s, t_vector *v, t_vector *n)
{
	t_vector	light;
	// t_vector	normal;
	t_vector	median;
	float		shade;
	float		shine;
	// int			point_color;

	// normal = ft_subtraction_vectors(v, &s->pos);
	light = ft_subtraction_vectors(&l->pos, v);
	median = ft_subtraction_vectors(&light, v);
	shade = ft_vector_scalar(n, &light) / ft_vector_modul(n) / ft_vector_modul(&light);
	if (shade < 0)
		shade = 0;
	shine = ft_vector_scalar(n, &median) / ft_vector_modul(n) / ft_vector_modul(&median);
	if (shine < 0)
		shine = 0;
	shade = AMBIENT + l->intensity * shade + l->intensity * pow(shine, s->specular);
	// point_color = ft_pixel_color(s->color, shade);
	return (ft_pixel_color(s->color, shade));
}
