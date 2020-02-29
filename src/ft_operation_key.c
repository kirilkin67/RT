#include "rtv1.h"

void	look(int key, t_rtv *p)
{
	if (key == NUM_KEY_8)
		p->cam_z -= K_ZOOM;
	else if (key == NUM_KEY_2)
		p->cam_z += K_ZOOM;
	else if (key == NUM_KEY_1)
		p->cam_y -= K_ZOOM;
	else if (key == NUM_KEY_7)
		p->cam_y += K_ZOOM;
	else if (key == NUM_KEY_4)
		p->cam_x += K_ZOOM;
	else if (key == NUM_KEY_6)
		p->cam_x -= K_ZOOM;
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
	ft_bzero(p->draw, WIDHT * HIGHT * 4);
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
		key == NUM_KEY_6 || key == NUM_KEY_1 || key == NUM_KEY_7)
		look(key, p); 
	return (0);
}
