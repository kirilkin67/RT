#include "rtv1.h"

void		ft_exit(void *param)
{
	char *str;

	str = (char *)param;
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(1);
}

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
	p->camera.x = 0;
	p->camera.y = 1;
	p->camera.z = -12;
	p->angle.x = 0;
	p->angle.y = 0;
	p->angle.z = 0;
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIDHT, HIGHT, str);
	p->img_ptr = mlx_new_image(p->mlx_ptr, WIDHT, HIGHT);
	p->draw = (int *)mlx_get_data_addr(p->img_ptr, &p->bpp, \
				&p->size_line, &p->endian);
}

void	ft_paint_scene(t_rtv *p)
{
	t_object	**object;
	t_light		light;
	t_camera	camera;

	if (!(object = (t_object **)malloc(sizeof(t_object *) * 10)))
		ft_exit(ERR_CREAT_TO_ARR);
	scene_object(p, &camera, object, &light);
	paint_object(p, &camera, object, &light);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	ft_navigation(p, &camera);

}

int		main(int argc, char **argv)
{
	t_rtv		paint;
	// void		*mlx_ptr;

	if (argc == 1)
		ft_exit(ERR_USAGE);
	ft_mlx_init(&paint, argv[1]);;
	ft_paint_scene(&paint);

	ft_operation(&paint);

	return (0);
}
// 180- 3.1415926535898
// 90 - 1.5707963267949
// 5  - 0.0872664625997