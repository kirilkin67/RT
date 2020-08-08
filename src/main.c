/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:39:48 by wrhett            #+#    #+#             */
/*   Updated: 2020/08/08 17:09:18 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	print_navigation(t_rtv *p, t_camera *camera)
{
	char	*str;
	char	*coord;

	coord = ft_itoa(camera->dir.z);
	str = ft_strjoin(STR2, coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 20, COLOR_STR, str);
	free(coord);
	free(str);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 40, COLOR_STR, STR1);
	coord = ft_itoa(camera->start.x);
	str = ft_strjoin("X = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 60, COLOR_STR, str);
	free(coord);
	free(str);
	coord = ft_itoa(camera->start.y);
	str = ft_strjoin("Y = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 80, COLOR_STR, str);
	free(coord);
	free(str);
	coord = ft_itoa(camera->start.z);
	str = ft_strjoin("Z = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 100, COLOR_STR, str);
	free(coord);
	free(str);
}

// void	print_instructions(t_rtv *p)
// {
// 	mlx_string_put(p->mlx_ptr, p->win_ptr, 8, 170, 0xFFFFFF, \
// 					"Q,E - rotate Z");
// 	mlx_string_put(p->mlx_ptr, p->win_ptr, 8, 190, 0xFFFFFF,\
// 					"A,D  - rotate Y");
// 	mlx_string_put(p->mlx_ptr, p->win_ptr, 8, 210, 0xFFFFFF,\
// 					"W,S  - rotate X");
// 	mlx_string_put(p->mlx_ptr, p->win_ptr, 8, 240, 0xFFFFFF,\
// 					"Arrows - up, down, right, left");
// }

void	ft_mlx_init(t_rtv *p, char *str)
{
	p->x0 = (p->width - 1) / 2;
	p->y0 = (p->height - 1) / 2;
	p->width = (double)p->width;
	p->mouse_key = 0;
	p->mouse_x = 0;
	p->mouse_y = 0;
	p->window_menu = CLOSED;
	p->camera->dir.z = p->width;
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, p->width, p->height, str);
	p->img_ptr = mlx_new_image(p->mlx_ptr, p->width, p->height);
	p->draw = (int *)mlx_get_data_addr(p->img_ptr, &p->bpp, \
				&p->size_line, &p->endian);
}

void	ft_paint_scene(t_rtv *p)
{
	ft_multi_thread_paint(p);
	// ft_paint_object(p);

	// mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	// print_navigation(p, p->camera);
	// print_instructions(p);
	expose_hook(p);
}

int		main(int argc, char **argv)
{
	t_rtv	paint;

	if (argc != 2)
		ft_exit(ERR_USAGE);
	paint.num = how_many_object(argv[1]);
	if (paint.num == 0)
		ft_exit("No object for raytrasing. Exit");
	paint.object = (t_object **)malloc(sizeof(t_object *) * paint.num);
	if (paint.object == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	paint.light = NULL;
	paint.camera = NULL;
	paint.width = 0;
	paint.height = 0;
	init_tab_object(&paint, argv[1]);
	ft_mlx_init(&paint, argv[1]);
	calculate_constant(&paint, &paint.camera->start);
	ft_paint_scene(&paint);
	ft_hook_operation(&paint);
	return (0);
}

// void	ft_mlx_init(t_rtv *p, char *str)
// {
// 	p->x0 = (WIDHT - 1) / 2;
// 	p->y0 = (HIGHT - 1) / 2;
// 	p->width = (double)WIDHT;
// 	p->mouse_key = 0;
// 	p->mouse_x = 0;
// 	p->mouse_y = 0;
// 	p->camera->dir.z = p->width;
// 	p->mlx_ptr = mlx_init();
// 	p->win_ptr = mlx_new_window(p->mlx_ptr, WIDHT, HIGHT, str);
// 	p->img_ptr = mlx_new_image(p->mlx_ptr, WIDHT, HIGHT);
// 	p->draw = (int *)mlx_get_data_addr(p->img_ptr, &p->bpp, \
// 				&p->size_line, &p->endian);
// }

