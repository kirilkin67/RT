/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 23:57:51 by mikhail           #+#    #+#             */
/*   Updated: 2020/05/08 16:40:40 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// int		ft_freetab(char **tab)
// {
// 	int		i;

// 	if (!tab)
// 		return (0);
// 	i = 0;
// 	while (tab[i] != NULL)
// 	{
// 		free(tab[i]);
// 		i += 1;
// 	}
// 	free(tab);
// 	return (0);
// }

// int		ft_lentab(char **tab)
// {
// 	int len;

// 	len = 0;
// 	while (tab[len] != NULL)
// 		len += 1;
// 	return (len);
// }

void	init_coordinates(t_vector *vector, char *tab)
{
	char	**coord;

	coord = ft_strsplit(tab, ',');
	if (ft_lentab(coord) != 3)
		ft_exit("Check the Coordinates parameters. Exit");
	vector->x = ft_atoi(coord[0]);
	vector->y = ft_atoi(coord[1]);
	vector->z = ft_atoi(coord[2]);
	ft_freetab(coord);
}

void	init_angle_norm(t_vector *angle, char *tab)
{
	char	**coord;

	coord = ft_strsplit(tab, ',');
	if (ft_lentab(coord) != 3)
		ft_exit("Check the Angle parameters. Exit");
	angle->x = ft_atoi(coord[0]) * PI / 180;
	angle->y = ft_atoi(coord[1]) * PI / 180;
	angle->z = ft_atoi(coord[2]) * PI / 180;
	ft_freetab(coord);
}

void	init_color(t_color *color, char *str)
{
	char	**tab;

	tab = ft_strsplit(str, ',');
	if (ft_lentab(tab) != 3)
		ft_exit("Check the Color parameters. Exit");
	color->red = ft_atoi(tab[0]);
	color->green = ft_atoi(tab[1]);
	color->blue = ft_atoi(tab[2]);
	ft_freetab(tab);
}
