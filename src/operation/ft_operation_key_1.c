#include "rt.h"

void	look(int key, t_rtv *p)
{
	t_vector	start;

	start.x = 0;
	start.y = 0;
	start.z = 0;
	if (key == KEY_S || key == 5)
		start.z -= K_ZOOM;
	else if (key == KEY_W || key == 4)
		start.z += K_ZOOM;
	else if (key == KEY_Q || key == KEY_DOWN)
		start.y -= K_ZOOM;
	else if (key == KEY_E || key == KEY_UP)
		start.y += K_ZOOM;
	else if (key == KEY_A || key == KEY_LEFT)
		start.x -= K_ZOOM;
	else if (key == KEY_D || key == KEY_RIGHT)
		start.x += K_ZOOM;
	ft_rotate_vector(&p->camera->angle, &start);
	p->camera->start.x += start.x;
	p->camera->start.y += start.y;
	p->camera->start.z += start.z;
	calculate_constant(p, &start);
	ft_paint_scene(p);
}

void	zoom(int key, t_rtv *p)
{
	int	width;

	width = p->width;
	if (key == NUM_KEY_PLUS)
		p->fov += K_FOV;
	else if (key == NUM_KEY_MINUS)
		p->fov -= K_FOV;
	if (p->fov <= 0)
		p->fov = K_FOV;
	p->camera->dir.z = p->fov;
	ft_paint_scene(p);
}

void	camera_start(t_rtv *p)
{
	t_vector	start;
	t_vector	tmp;

	start = p->camera->pos;
	p->camera->angle.x = 0;
	p->camera->angle.y = 0;
	p->camera->angle.z = 0;
	tmp = start;
	start = ft_sub_vectors(&start, &p->camera->start);
	p->camera->start = tmp;
	calculate_constant(p, &start);
	p->fov = (double)p->width;
	p->depth_mirror = DEPTH_REFL;
	p->samples = MIN_SAMPLE;
	p->filter = e_no_effect;
	ft_paint_scene(p);
}

void	reflect(t_rtv *p)
{
	p->depth_mirror += 1;
	if (p->depth_mirror == DEPTH)
		p->depth_mirror = 1;
	ft_paint_scene(p);
}

void	aliasing_effects(t_rtv *p)
{
	if (p->samples < MAX_SAMPLE)
		p->samples += 1;
	else
		p->samples = MIN_SAMPLE;
	ft_paint_scene(p);
}

void	key_press1(int key, t_rtv *p)
{
	if (key == KEY_M)
		reflect(p);
	if (key == KEY_N || key == KEY_C)
		aliasing_effects(p);
	if (key == KEY_O || key == KEY_I || key == KEY_U || key == KEY_Y ||
	key == KEY_T)
		effects(key, p);
	if (key == KEY_P)
		save_bmp_file(p);
	if (key == KEY_SPACE)
		camera_start(p);
}
