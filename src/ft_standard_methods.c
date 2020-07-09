#include "rtv1.h"

int		close_endian(void *param)
{
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
	print_instructions(p);
	return (1);
}