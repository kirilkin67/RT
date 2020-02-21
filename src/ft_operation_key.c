#include "rtv1.h"

// void	look(int key, t_rtv *p, t_camera *r, t_sphere *s)
// {
// 	if (key == NUM_KEY_8)
// 		r->start.z += K_ZOOM;
// 	else if (key == NUM_KEY_2)
// 		r->start.z -= K_ZOOM;
// 	else if (key == NUM_KEY_7)
// 		r->start.y += K_ZOOM;
// 	else if (key == NUM_KEY_1)
// 		r->start.y -= K_ZOOM;
// 	else if (key == NUM_KEY_4)
// 		r->start.x += K_ZOOM;
// 	else if (key == NUM_KEY_6)
// 		r->start.x -= K_ZOOM;
// 	ft_paint_intersect(p, r, s);
	// mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	// ft_paint_scene(p, r, s);
// }

int		key_press(int key, t_rtv *p)
{
	if (key == 53)
		exit(0);
	// if (key ==  NUM_KEY_8 || key ==  NUM_KEY_2 || key == NUM_KEY_4 || \
	// 	key == NUM_KEY_6 || key == 83 || key == 85)
	// 	look(key, p); 
	return (0);
}
