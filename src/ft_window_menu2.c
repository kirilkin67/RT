#include "rt.h"

void	ft_window_menu(t_rtv *p)
{
	if (p->window_menu == CLOSED)
	{
		p->menu_ptr = mlx_new_window(p->mlx_ptr, W_MENU, p->height, "MENU");
		ft_drawing_menu(p);
		p->window_menu = OPEN;
		mlx_hook(p->menu_ptr, 2, (1L << 0), key_press, p);
		mlx_hook(p->menu_ptr, 17, (1L << 0), close_window, p);
	}
	else if (p->window_menu == OPEN)
	{
		p->window_menu = CLOSED;
		mlx_destroy_window(p->mlx_ptr, p->menu_ptr);
	}
}

void	ft_init_configuration(t_rtv *p)
{
	p->width = WIDHT;
	p->height = HIGHT;
	p->x0 = (p->width - 1) / 2.0;
	p->y0 = (p->height - 1) / 2.0;
	p->fov = (double)p->width;
	p->mouse_key = 0;
	p->mouse_x = 0;
	p->mouse_y = 0;
	p->window_menu = CLOSED;
	p->samples = MIN_SAMPLE;
	p->depth_mirror = DEPTH_REFL;
	p->depth_refract = DEPTH_REFR;
	p->camera->dir.z = p->fov;
	p->selected_obj = NO_INTERSECT;
	ft_mlx_init(p);
}
