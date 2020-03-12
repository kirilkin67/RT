#include "rtv1.h"

void	look(int key, t_rtv *p)
{
	if (key == NUM_KEY_8)
		p->camera->start.z -= K_ZOOM;
	else if (key == NUM_KEY_2)
		p->camera->start.z += K_ZOOM;
	else if (key == NUM_KEY_1 || key ==  NUM_DOWN)
		p->camera->start.y -= K_ZOOM;
	else if (key == NUM_KEY_7 || key ==  NUM_UP)
		p->camera->start.y += K_ZOOM;
	else if (key == NUM_KEY_4 || key ==  NUM_LEFT)
		p->camera->start.x -= K_ZOOM;
	else if (key == NUM_KEY_6 || key ==  NUM_RIGHT)
		p->camera->start.x += K_ZOOM;
	else if (key == KEY_S)
		p->angle.x -= K_DIR;
	else if (key == KEY_W)
		p->angle.x += K_DIR;
	else if (key == KEY_A)
		p->angle.y -= K_DIR;
	else if (key == KEY_D)
		p->angle.y += K_DIR;
	ft_bzero(p->draw, WIDHT * HIGHT * 4);
	ft_paint_scene(p);
}

void	zoom(int key, t_rtv *p)
{
	if (key == NUM_KEY_PLUS)
		p->width += K_FOV;
	else if (key == NUM_KEY_MINUS)
		p->width -= K_FOV;
	if (p->width <= 0)
		p->width = K_FOV;
	// ft_bzero(p->draw, WIDHT * HIGHT * 4);
	ft_paint_scene(p);
}

int		key_press(int key, t_rtv *p)
{
	// printf("%d\n", key);
	if (key == 53)
		exit(0);
	if (key == NUM_KEY_PLUS || key == NUM_KEY_MINUS)
		zoom(key, p);
	if (key ==  NUM_KEY_8 || key ==  NUM_KEY_2 || key == NUM_KEY_4 ||\
		key == NUM_KEY_6 || key == NUM_KEY_1 || key == NUM_KEY_7 ||\
		key == KEY_D || key == KEY_W || key == KEY_A || key == KEY_S ||\
		key ==  NUM_LEFT || key ==  NUM_RIGHT || key ==  NUM_UP ||\
		key ==  NUM_DOWN)
		look(key, p);
	if (key == KEY_SPACE)
	{
		p->camera->start.x = 0;
		p->camera->start.y = 0;
		p->camera->start.z = -15;
		p->angle.x = 0;
		p->angle.y = 0;
		p->angle.z = 0;
		ft_paint_scene(p);
	}
	return (0);
}
