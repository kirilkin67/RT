#include "rtv1.h"

int		mouse_press(int button, int x, int y, t_rtv *p)
{
	if (y >= 0 && y <= (HIGHT - 1) && x >= 0 && x <= (WIDHT - 1))
	{
		if (button == 1)
		{
			p->camera->angle.y += asin((double)(x - p->x0) / (double)p->width);
			p->camera->angle.x += asin((double)(p->y0 - y) / (double)p->width);
			ft_paint_scene(p);
		}
		if (button == 4 || button == 5)
			look(button, p);
	}
	// ft_paint_scene(p);
	return (0);
}

int		mouse_movement(int x, int y, t_rtv *p)
{
	// int		x1;
	// int		y1;

	// x1 = p->mouse_x;
	// y1 = p->mouse_y;
	// p->mouse_x = x;
	// p->mouse_y = y;

	if (y >= 0 && y <= (HIGHT - 1) && x >= 0 && x <= (WIDHT - 1))
	{
		p->camera->angle.y += asin((double)(x - p->x0) / (double)p->width);
		p->camera->angle.x += asin((double)(p->y0 - y) / (double)p->width);
	}
	ft_paint_scene(p);
	return (0);
}