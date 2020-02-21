#include "rtv1.h"

int		close_endian(void *param)
{
	(void)param;
	exit(0);
}

void	ft_operation(t_rtv *p)
{
	mlx_hook(p->win_ptr, 2, 0, key_press, p);
	mlx_hook(p->win_ptr, 17, 0, close_endian, p);
	// mlx_hook(p->win_ptr, 4, 0, mouse_press, p);
	// mlx_hook(p->win_ptr, 5, 0, mouse_release, p);
	// mlx_hook(p->win_ptr, 6, 0, mouse_movement, p);
	mlx_loop(p->mlx_ptr);
}

void		ft_mlx_init(t_rtv *p, char *str)
{
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIDHT, HIGHT, str);
	p->img_ptr = mlx_new_image(p->mlx_ptr, WIDHT, HIGHT);
	p->draw = (int *)mlx_get_data_addr(p->img_ptr, &p->bpp, \
				&p->size_line, &p->endian);
}

void	ft_paint_scene(t_rtv *p, t_camera *r, t_sphere **s, t_light *l)
{
	ft_paint_intersect(p, r, s[0], l);
	ft_paint_intersect(p, r, s[1], l);
	ft_paint_intersect(p, r, s[2], l);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	ft_operation(p);
}

void	scene(t_camera *camera, t_sphere **sphere, t_light *light)
{
	sphere[0] = (t_sphere *)malloc(sizeof(t_sphere));
	sphere[0]->pos.x = 200;
	sphere[0]->pos.y = 0;
	sphere[0]->pos.z = 1000;
	sphere[0]->radius = 100;
	sphere[0]->color = 0xFF0000;
	sphere[0]->specular = 500;

	sphere[1] = (t_sphere *)malloc(sizeof(t_sphere));
	sphere[1]->pos.x = -100;
	sphere[1]->pos.y = 0;
	sphere[1]->pos.z = 500;
	sphere[1]->radius = 100;
	sphere[1]->color = 0xFF00;
	sphere[1]->specular = 200;

	sphere[2] = (t_sphere *)malloc(sizeof(t_sphere));
	sphere[2]->pos.x = 0;
	sphere[2]->pos.y = 200;
	sphere[2]->pos.z = 200;
	sphere[2]->radius = 100;
	sphere[2]->color = 0xFF;
	sphere[2]->specular = 50;

	light->pos.x = -500;
	light->pos.y = 500;
	light->pos.z = 100;
	light->intensity = 0.6;
	light->color =0xFFFFFF;

	camera->start.x = 0;
	camera->start.y = 100;
	camera->start.z = -1000;

	camera->dir.z = WIDHT;
}

int		main(int argc, char **argv)
{
	t_rtv		paint;
	void		*mlx_ptr;
	t_sphere	**sphere;
	t_light		light;
	t_camera	camera;

	sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 3);
	scene(&camera, sphere, &light);
	ft_mlx_init(&paint, argv[1]);
	ft_paint_scene(&paint, &camera, sphere, &light);
	// ft_paint_intersect(&paint, &camera, &sphere[0]);
	// ft_paint_intersect(&paint, &camera, &sphere[1]);
	// mlx_put_image_to_window(paint.mlx_ptr, paint.win_ptr, paint.img_ptr, 0, 0);
	ft_operation(&paint);

	return (0);
}

// t_sphere **sphere;
	// sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 2);
	// sphere[0] = (t_sphere *)malloc(sizeof(t_sphere));
	// sphere[0]->pos.x = 100;
	// sphere[0]->pos.y = 0;
	// sphere[0]->pos.z = 500;
	// sphere[0]->radius = 100;
	// sphere[0]->color = 0xFF0000;
	// sphere[1] = (t_sphere *)malloc(sizeof(t_sphere));
	// sphere[1]->pos.x = -100;
	// sphere[1]->pos.y = 200;
	// sphere[1]->pos.z = 800;
	// sphere[1]->radius = 100;
	// sphere[1]->color = 0xFF00;

	// t_vector	light;
	// light.x = 500;
	// light.y = 1000;
	// light.z = 100;

	// t_camera camera;
	// camera.start.x = 0;
	// camera.start.y = 0;
	// camera.start.z = 0;

	// camera.dir.z = WIDHT;
