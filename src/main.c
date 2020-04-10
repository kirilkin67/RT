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

	// coord = ft_itoa(camera->dir.z);
	str = ft_strjoin(STR2, (coord = ft_itoa(camera->dir.z)));
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 20, 0xFFFFFF, str);
	free(coord);
	free(str);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 40, 0xFFFFFF, STR1);
	// coord = ft_itoa(camera->start.x);
	str = ft_strjoin("X = ", (coord = ft_itoa(camera->start.x)));
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 60, 0xFFFFFF, str);
	free(coord);
	free(str);
	// coord = ft_itoa(camera->start.y);
	str = ft_strjoin("Y = ", (coord = ft_itoa(camera->start.y)));
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 80, 0xFFFFFF, str);
	free(coord);
	free(str);
	// coord = ft_itoa(camera->start.z);
	str = ft_strjoin("Z = ", (coord = ft_itoa(camera->start.z)));
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 100, 0xFFFFFF, str);
	free(coord);
	free(str);
}

void	ft_operation(t_rtv *p)
{
	mlx_hook(p->win_ptr, 2, (1L << 0), key_press, p);
	mlx_hook(p->win_ptr, 17, (1L << 17), close_endian, p);
	// mlx_hook(p->win_ptr, 4, 0, mouse_press, p);
	// mlx_hook(p->win_ptr, 5, 0, mouse_release, p);
	// mlx_hook(p->win_ptr, 6, 0, mouse_movement, p);
	mlx_loop(p->mlx_ptr);
}

void		ft_mlx_init(t_rtv *p, char *str)
{
	// p->object = (t_object **)malloc(sizeof(t_object *) * 20);
	// p->light = NULL;
	// if (p->object == NULL)
	// 	ft_exit(ERR_CREAT_TO_ARR);
	p->x0 = (double)WIDHT / 2.0;
	p->y0 = (double)HIGHT / 2.0;
	p->width = (double)WIDHT;
	// init_tab_object(p, str);
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIDHT, HIGHT, str);
	p->img_ptr = mlx_new_image(p->mlx_ptr, WIDHT, HIGHT);
	p->draw = (int *)mlx_get_data_addr(p->img_ptr, &p->bpp, \
				&p->size_line, &p->endian);
}

void	ft_paint_scene(t_rtv *p)
{
	ft_multi_thread_paint(p);
	// ft_paint_object(p);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	// ft_navigation(p, p->camera);
}

int		main(int argc, char **argv)
{
	t_rtv		paint;

	if (argc != 2)
		ft_exit(ERR_USAGE);
	paint.object = (t_object **)malloc(sizeof(t_object *) * 30);
	paint.light = NULL;
	printf("%p\n", paint.light);
	paint.camera = NULL;
	if (paint.object == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	ft_mlx_init(&paint, argv[1]);;
	init_tab_object(&paint, argv[1]);
	calculate_constant(&paint, &paint.camera->start);
	ft_paint_scene(&paint);
	// printf("%f\n",paint.light->pos.z);
	// printf("%f\n",paint.light->next->pos.z);
	ft_operation(&paint);
	return (0);
}
// 180- 3.1415926535898
// 90 - 1.5707963267949
// 5  - 0.0872664625997
