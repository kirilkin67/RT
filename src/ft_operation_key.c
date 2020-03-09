#include "rtv1.h"

void	look(int key, t_rtv *p)
{
	if (key == NUM_KEY_8)
		p->camera.z -= K_ZOOM;
	else if (key == NUM_KEY_2)
		p->camera.z += K_ZOOM;
	else if (key == NUM_KEY_1)
		p->camera.y -= K_ZOOM;
	else if (key == NUM_KEY_7)
		p->camera.y += K_ZOOM;
	else if (key == NUM_KEY_4)
		p->camera.x += K_ZOOM;
	else if (key == NUM_KEY_6)
		p->camera.x -= K_ZOOM;
	else if (key == KEY_S)
		p->angle_x -= K_DIR;
	else if (key == KEY_W)
		p->angle_x += K_DIR;
	else if (key == KEY_A)
		p->angle_y -= K_DIR;
	else if (key == KEY_D)
		p->angle_y += K_DIR;
	// printf("ANGLE_X %f, ANGLE_Y %f\n", p->angle_x, p->angle_y);
	// ft_bzero(p->draw, WIDHT * HIGHT * 4);
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
	if (key ==  NUM_KEY_8 || key ==  NUM_KEY_2 || key == NUM_KEY_4 || \
		key == NUM_KEY_6 || key == NUM_KEY_1 || key == NUM_KEY_7 || \
		key == KEY_D || key == KEY_W || key == KEY_A || key == KEY_S)
		look(key, p);
	if (key == KEY_SPACE)
	{
		p->camera.x = 0;
		p->camera.y = 0;
		p->camera.z = -1500;
		p->angle_x = 0;
		p->angle_y = 0;
		p->angle_z = 0;
		ft_paint_scene(p);
	}
	return (0);
}
