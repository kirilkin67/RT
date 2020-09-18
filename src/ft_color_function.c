#include "rtv1.h"

int		color(t_color *color, float percent)
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

int		get_light(int color1, int color2, float coefficient)
{
	if (coefficient > 1.0)
		coefficient = 1.0;
	return ((int)(color1 * (1.0 - coefficient) + color2 * coefficient));
}

int		result_color(int color1, int color2, float coefficient)
{
	float	red;
	float	green;
	float	blue;

	if (color1 == color2 || color2 < 0 || coefficient == 0)
		return (color1);
	red = get_light((color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF, coefficient);
	green = get_light((color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF, coefficient);
	blue = get_light(color1 & 0xFF, color2 & 0xFF, coefficient);
	return (((int)red << 16) | ((int)green << 8) | (int)blue);
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
