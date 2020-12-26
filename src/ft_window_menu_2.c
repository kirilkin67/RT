/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_menu2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:32:21 by msole             #+#    #+#             */
/*   Updated: 2020/12/26 19:43:21 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_window_menu(t_rtv *p)
{
	if (p->window_menu == CLOSED)
	{
		p->menu_ptr = mlx_new_window(p->mlx_ptr, W_MENU, p->height, "MENU");
		ft_drawing_menu(p);
		p->window_menu = OPEN;
		mlx_hook(p->menu_ptr, 2, (1L << 0), key_press, p);
		mlx_hook(p->menu_ptr, 17, (1L << 0), close_window, p);
	}
	else if (p->window_menu == OPEN)
	{
		p->window_menu = CLOSED;
		mlx_destroy_window(p->mlx_ptr, p->menu_ptr);
	}
}

void	print_instructions_for_obj(t_rtv *p)
{
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 470, COLOR_STR, "Press right key-mouse");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 490, COLOR_STR, "to choose the figure");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 510, COLOR_STR, "Move figure (use side key boarg):");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 530, COLOR_STR, "Up/Down - 7/1");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 550, COLOR_STR, "Left/Right - 4/6");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 570, COLOR_STR, "Backward/Forward - 8/2");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 230, COLOR_STR, "Whitespace - ");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 250, COLOR_STR, "Go back to the original version");
	mlx_string_put(p->mlx_ptr, p->menu_ptr,\
	20, 610, COLOR_STR, "Printscreen - P");
}

void	print_navigation(t_rtv *p)
{
	char	*str;
	char	*coord;

	coord = ft_itoa(p->fov);
	str = ft_strjoin(STR2, coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 50, COLOR_STR, str);
	free(coord);
	free(str);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 70, COLOR_STR, STR1);
	coord = ft_itoa(p->camera->start.x);
	str = ft_strjoin("X = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 90, COLOR_STR, str);
	free(coord);
	free(str);
	coord = ft_itoa(p->camera->start.y);
	str = ft_strjoin("Y = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 110, COLOR_STR, str);
	free(coord);
	free(str);
	coord = ft_itoa(p->camera->start.z);
	str = ft_strjoin("Z = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 130, COLOR_STR, str);
	free(coord);
	free(str);
}
