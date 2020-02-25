#include "rtv1.h"

int		close_endian(void *param)
{
	(void)param;
	exit(0);
}

void	ft_navigation(t_rtv *p, t_camera *camera)
{
	char	*str;
	char	*coord;

	coord = ft_itoa(camera->dir.z);
	str = ft_strjoin(STR2, coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 20, 0xFFFFFF, str);
	free(coord);
	free(str);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 40, 0xFFFFFF, STR1);
	coord = ft_itoa(camera->start.x);
	str = ft_strjoin("X = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 60, 0xFFFFFF, str);
	free(coord);
	free(str);
	coord = ft_itoa(camera->start.y);
	str = ft_strjoin("Y = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 80, 0xFFFFFF, str);
	free(coord);
	free(str);
	coord = ft_itoa(camera->start.z);
	str = ft_strjoin("Z = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 100, 0xFFFFFF, str);
	free(coord);
	free(str);
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
	p->width = WIDHT;
	p->cam_x = 0;
	p->cam_y = 0;
	p->cam_z = 0;
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIDHT, HIGHT, str);
	p->img_ptr = mlx_new_image(p->mlx_ptr, WIDHT, HIGHT);
	p->draw = (int *)mlx_get_data_addr(p->img_ptr, &p->bpp, \
				&p->size_line, &p->endian);
}

void	ft_paint_scene(t_rtv *p)
{
	t_sphere	**sphere;
	t_plane		plane;
	t_light		light;
	t_camera	camera;

	sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 3);
	scene(p, &camera, sphere, &light, &plane);
	ft_paint_plane(p, &camera, &plane, &light);
	ft_paint_sphere(p, &camera, sphere[0], &light);
	ft_paint_sphere(p, &camera, sphere[1], &light);
	ft_paint_sphere(p, &camera, sphere[2], &light);

	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	ft_navigation(p, &camera);
	free(sphere[2]);
	free(sphere[1]);
	free(sphere[0]);
	free(sphere);
}

void	scene(t_rtv *p, t_camera *camera, t_sphere **sphere, t_light *light, t_plane *plane)
{
	sphere[0] = (t_sphere *)malloc(sizeof(t_sphere));
	sphere[0]->pos.x = -300;
	sphere[0]->pos.y = 0;
	sphere[0]->pos.z = 1000;
	sphere[0]->radius = 100;
	sphere[0]->color = 0xFFD700; // GOLD
	sphere[0]->specular = 500;


	sphere[1] = (t_sphere *)malloc(sizeof(t_sphere));
	sphere[1]->pos.x = 300;
	sphere[1]->pos.y = 0;
	sphere[1]->pos.z = 1000;
	sphere[1]->radius = 100;
	sphere[1]->color = 0xFF00; // GREEN
	sphere[1]->specular = 200;

	sphere[2] = (t_sphere *)malloc(sizeof(t_sphere));
	sphere[2]->pos.x = 0;
	sphere[2]->pos.y = -100;
	sphere[2]->pos.z = 500;
	sphere[2]->radius = 100;
	sphere[2]->color = 0xFF00FF; // FUCHSIA
	sphere[2]->specular = 50;

	plane->norm.x = 0;
	plane->norm.y = 10;
	plane->norm.z = -1;

	plane->pos.x = 0;
	plane->pos.y = -100;
	plane->pos.z = 0;
	plane->color = 0xFFFFFF;
	plane->specular = 100;

	light->pos.x = -200;
	light->pos.y = 1000;
	light->pos.z = 500;
	light->intensity = 0.6;
	light->color =0xFFFFFF;

	camera->start.x = p->cam_x;
	camera->start.y = p->cam_y;
	camera->start.z = p->cam_z;

	camera->dir.x = 0;
	camera->dir.y = 0;
	camera->dir.z = p->width;
}

int		main(int argc, char **argv)
{
	t_rtv		paint;
	void		*mlx_ptr;
	// static t_sphere	**sphere;
	// static t_light		light;
	// static t_camera	camera;

	ft_mlx_init(&paint, argv[1]);;
	ft_paint_scene(&paint);

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
