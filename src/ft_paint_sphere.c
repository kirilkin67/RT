#include "rtv1.h"

t_dot		ft_parametr_sphere(int x, int y, int radius, int color)
{
	t_dot sphere;

	sphere.x = x;
	sphere.y = y;
	sphere.radius = radius;
	sphere.color = color;
	return (sphere);
}

void			ft_paint_sphere_dot(t_rtv *p, t_dot *s)
{
	int	x;
	int	y;
	int radius;
	int	dot;

	ft_paint_circle(p, s);
	radius = s->radius * s->radius;
	y = s->y - s->radius;
	while (y <= (s->y + s->radius))
	{
		x = s->x - s->radius;
		while (x <= (s->x + s->radius))
		{
			dot = (x - s->x) * (x - s->x) + (y - s->y) * (y - s->y);
			if (dot <= radius && (x >= 0 && x < WIDHT && y >= 0 && y < HIGHT))
				p->draw[x + y * WIDHT] = s->color;
			x += 1;
		}
		y += 1;
	}
}

void	ft_paint_circle(t_rtv *p, t_dot *s)
{
	int	x;
	int	y;
	int radius;
	int	error;

	radius = s->radius;
	x = -radius;
	error = 2 - 2 * radius;
	y = 0;
	while (x <= 0)
	{
		if ((s->x - x) >= 0 && (s->x - x) < WIDHT && (s->y + y) >= 0 && (s->y + y) < HIGHT)
			p->draw[(s->x - x) + (s->y + y) * WIDHT] = s->color;
		if ((s->x - y) >= 0 && (s->x - y) < WIDHT && (s->y - x) >= 0 && (s->y - x) < HIGHT)
			p->draw[(s->x - y) + (s->y - x) * WIDHT] = s->color;
		if ((s->x + x) >= 0 && (s->x + x) < WIDHT && (s->y - y) >= 0 && (s->y - y) < HIGHT)
			p->draw[(s->x + x) + (s->y - y) * WIDHT] = s->color;
		if ((s->x + y) >= 0 && (s->x + y) < WIDHT && (s->y + x) >= 0 && (s->y + x) < HIGHT)
			p->draw[(s->x + y) + (s->y + x) * WIDHT] = s->color;
		radius = error;
		if (radius <= y)
			error += ++y * 2 + 1;		/* e_xy+e_y < 0 */
		if (radius > x || error > y)	/* e_xy+e_x > 0 or no 2nd y-step */
			error += ++x * 2 + 1;		/* -> x-step now */
	}
}

void	ft_paint_circle_alfa(t_rtv *p, int x0, int y0, int radius, int color)
{
	int	x;
	int	y;
	int	error;

	x = -radius;
	error = 2 - 2*radius;
	y = 0;
	while (x <= 0)
	{
		if ((x0 - x) >= 0 && (x0 - x) < WIDHT && (y0 + y) >= 0 && (y0 + y) < HIGHT)
			p->draw[(x0 - x) + (y0 + y) * WIDHT] = color;
		if ((x0 - y) >= 0 && (x0 - y) < WIDHT && (y0 - x) >= 0 && (y0 - x) < HIGHT)
			p->draw[(x0 - y) + (y0 - x) * WIDHT] = color;
		if ((x0 + x) >= 0 && (x0 + x) < WIDHT && (y0 - y) >= 0 && (y0 - y) < HIGHT)
			p->draw[(x0 + x) + (y0 - y) * WIDHT] = color;
		if ((x0 + y) >= 0 && (x0 + y) < WIDHT && (y0 + x) >= 0 && (y0 + x) < HIGHT)
			p->draw[(x0 + y) + (y0 + x) * WIDHT] = color;
		radius = error;
		if (radius <= y)
			error += ++y * 2 + 1;		/* e_xy+e_y < 0 */
		if (radius > x || error > y)	/* e_xy+e_x > 0 or no 2nd y-step */
			error += ++x * 2 + 1;		/* -> x-step now */
	}
}
