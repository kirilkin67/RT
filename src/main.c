/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhail <mikhail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 00:06:33 by mikhail           #+#    #+#             */
/*   Updated: 2020/04/21 00:43:38 by mikhail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		close_endian(void *param)
{
	t_rtv *p;

	// (void)param;
	p = (t_rtv *)param;
	mlx_destroy_window(p->mlx_ptr, p->img_ptr);
	exit(0);
}

void	ft_navigation(t_rtv *p, t_camera *camera)
{
	char	*str;
	char	*coord;

	str = ft_strjoin(STR2, (coord = ft_itoa(camera->dir.z)));
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 20, COLOR_STR, str);
	free(coord);
	free(str);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 40, COLOR_STR, STR1);
	str = ft_strjoin("X = ", (coord = ft_itoa(camera->start.x)));
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 60, COLOR_STR, str);
	free(coord);
	free(str);
	str = ft_strjoin("Y = ", (coord = ft_itoa(camera->start.y)));
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 80, COLOR_STR, str);
	free(coord);
	free(str);
	str = ft_strjoin("Z = ", (coord = ft_itoa(camera->start.z)));
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 100, COLOR_STR, str);
	free(coord);
	free(str);
}

// void	ft_operation(t_rtv *p)
// {
// 	mlx_hook(p->win_ptr, 2, (1L << 0), key_press, p);
// 	mlx_hook(p->win_ptr, 17, (1L << 17), close_endian, p);
// 	// mlx_hook(p->win_ptr, 4, 0, mouse_press, p);
// 	// mlx_hook(p->win_ptr, 5, 0, mouse_release, p);
// 	// mlx_hook(p->win_ptr, 6, 0, mouse_movement, p);
// 	mlx_loop(p->mlx_ptr);
// }

void		ft_mlx_init(t_rtv *p, char *str)
{
	p->x0 = (double)WIDHT / 2.0;
	p->y0 = (double)HIGHT / 2.0;
	p->width = (double)WIDHT;
	p->camera->dir.z = p->width;
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
	ft_navigation(p, p->camera);
}

int		expose_hook(t_rtv *p)
{
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	ft_navigation(p, p->camera);
	return (1);
}

int		main(int argc, char **argv)
{
	t_rtv	paint;
	// int 	num;

	if (argc != 2)
		ft_exit(ERR_USAGE);
	paint.num = how_many_object(argv[1]);
	paint.object = (t_object **)malloc(sizeof(t_object *) * paint.num);
	if (paint.object == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	paint.light = NULL;
	paint.camera = NULL;
	init_tab_object(&paint, argv[1]);
	ft_mlx_init(&paint, argv[1]);;
	calculate_constant(&paint, &paint.camera->start);
	ft_paint_scene(&paint);
	mlx_hook(paint.win_ptr, 2, (1L << 0), key_press, &paint);
	// mlx_hook(paint.win_ptr, 17, (1L << 19), &close_endian, &paint);
	mlx_hook(paint.win_ptr, 17, (1L << 17), close_endian, &paint);
	mlx_hook(paint.win_ptr, 12, (1L << 15), expose_hook, &paint);
	mlx_loop(paint.mlx_ptr);
	// ft_operation(&paint);
	return (0);
}
// 180- 3.1415926535898
// 90 - 1.5707963267949
// 5  - 0.0872664625997
