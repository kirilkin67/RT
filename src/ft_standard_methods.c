#include "rtv1.h"

void	free_memory(t_rtv *paint)
{
	t_light	*tmp;
	int		n;

	free(paint->camera);
	paint->camera = NULL;
	n = 0;
	while (n < paint->num)
	{
		free(paint->object[n]);
		paint->object[n] = NULL;
		n += 1;
	}
	free(paint->object);
	paint->object = NULL;
	if (paint->light != NULL)
	{
		while (paint->light != NULL)
		{
			tmp = paint->light->next;
			free(paint->light);
			paint->light = tmp;
		}
	}
}

int		close_endian(void *param)
{
	// t_rtv	*paint;

	// paint = (t_rtv *)param;
	// free_memory(paint);
	(void)param;
	exit(0);
}

void	ft_exit(void *param)
{
	char *str;

	str = (char *)param;
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(1);
}

int		expose_hook(t_rtv *p)
{
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	print_navigation(p, p->camera);
	// print_instructions(p);
	return (1);
}

void	ft_hook_operation(t_rtv *paint)
{
	mlx_hook(paint->win_ptr, 2, (1L << 0), key_press, paint);
	mlx_hook(paint->win_ptr, 4, (1L << 2), mouse_press, paint);
	mlx_hook(paint->win_ptr, 5, (1L << 3), mouse_release, paint);
	mlx_hook(paint->win_ptr, 6, (1L << 6), mouse_movement, paint);
	mlx_hook(paint->win_ptr, 17, (1L << 17), close_endian, paint);
	mlx_hook(paint->win_ptr, 12, (1L << 15), expose_hook, paint);
	mlx_loop(paint->mlx_ptr);
}
