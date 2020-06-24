/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 00:19:06 by mikhail           #+#    #+#             */
/*   Updated: 2020/06/24 13:40:51 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		how_many_object(char *src)
{
	int		number;
	int		fd;
	char	*line;
	char	*object;

	line = NULL;
	if ((fd = open(src, O_RDONLY)) <= 0)
		ft_exit(ERR_FILE_OPEN);
	number = 0;
	while (get_next_line(fd, &line) > 0)
	{
		while (*line == ' ')
			line += 1;
		object = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
		if ((ft_strcmp(object, "Sphere") == 0) || \
			(ft_strcmp(object, "Plane") == 0) || \
			(ft_strcmp(object, "Cylindr") == 0) || \
			(ft_strcmp(object, "Cone") == 0))
			number += 1;
		free(line);
		free(object);
	}
	close(fd);
	return (number);
}

void	add_obj_to_tab(t_rtv *paint, char **tab, int *i)
{
	if (ft_strcmp(tab[0], "Sphere") == 0)
		init_sphere(paint, tab, i);
	else if (ft_strcmp(tab[0], "Plane") == 0)
		init_plane(paint, tab, i);
	else if (ft_strcmp(tab[0], "Cylindr") == 0)
		init_cylindr(paint, tab, i);
	else if (ft_strcmp(tab[0], "Cone") == 0)
		init_konys(paint, tab, i);
}

void	init_tab_object(t_rtv *paint, char *src)
{
	int		i;
	int		fd;
	char	*line;
	char	**tab;

	line = NULL;
	i = 0;
	if ((fd = open(src, O_RDONLY)) <= 0)
		ft_exit(ERR_FILE_OPEN);
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		if (ft_strcmp(tab[0], "Light") == 0)
			paint->light = init_light(paint->light, tab);
		if (ft_strcmp(tab[0], "Camera") == 0)
			init_camera(paint, tab);
		else
			add_obj_to_tab(paint, tab, &i);
		ft_free_wordtab(tab);
		free(line);
	}
	if (paint->camera == NULL)
		ft_exit("No camera. Exit");
	if (paint->light == NULL)
		ft_exit("No light. Exit");
	close(fd);
}
