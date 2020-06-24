#include "rtv1.h"

int			local_color(t_color *color, float percent)
{
	float	red;
	float	green;
	float	blue;

	if (percent > 1)
		percent = 1.0;
	red = (float)color->red * percent;
	green = (float)color->green * percent;
	blue = (float)color->blue * percent;
	return (((int)red << 16) | ((int)green << 8) | (int)blue);
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

t_vector	ft_calculate_vector_norm(t_rtv *p, int id, t_vector *intersect)
{
	t_vector	norm;
	t_vector	v_norm;
	double		len_ray;

	if (p->object[id]->id == 'P')
		norm = p->object[id]->norm_p;
	if (p->object[id]->id == 'S' || p->object[id]->id == 'C' ||
			p->object[id]->id == 'K')
	{
		norm = ft_subtraction_vector(intersect, &p->object[id]->pos);
		if (p->object[id]->id == 'C' || p->object[id]->id == 'K')
		{
			len_ray =
			ft_vector_projection_on_ray(&norm, &p->object[id]->norm_p);
			if (p->object[id]->id == 'K')
				len_ray = len_ray / pow(cos(0.5 * p->object[id]->angle), 2);
			v_norm = ft_multiply_vector_num(&p->object[id]->norm_p, len_ray);
			norm = ft_subtraction_vector(&norm, &v_norm);
		}
		ft_unit_vector(&norm);
	}
	return (norm);
}

// t_color	local_color(t_color *color, float percent)
// {
// 	t_color	new_color;

// 	if (percent > 1)
// 		percent = 1.0;
// 	new_color.red = (int) (color->red * percent);
// 	new_color.green = (int) (color->green * percent);
// 	new_color.blue = (int) (color->blue * percent);
// 	return (new_color);
// }
