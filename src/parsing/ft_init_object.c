/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 00:00:14 by mikhail           #+#    #+#             */
/*   Updated: 2020/09/25 18:00:31 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cone(t_rtv *p, char **tab, int *i)
{
	if (tab == NULL || ft_len_wordtab(tab) != 9)
		ft_exit("Check the Cone parameters. Exit");
	// p->object[*i] = (t_object *)malloc(sizeof(t_object));
	p->object[*i] = ft_memalloc(sizeof(t_object));
	if (p->object[*i] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	p->object[*i]->tip = e_cone;
	init_coordinates(&p->object[*i]->pos, tab[1]);
	init_coordinates(&p->object[*i]->norm_p, tab[2]);
	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
	p->object[*i]->angle = ft_atoi(tab[4]) * PI / 180;
	init_color(&p->object[*i]->color, tab[5]);
	p->object[*i]->specular = ft_atoi(tab[6]);
	p->object[*i]->reflection = ft_atof(tab[7]);
	p->object[*i]->refraction = ft_atof(tab[8]);
	ft_rotat_vector(&p->object[*i]->angle_n, &p->object[*i]->norm_p);
	*i += 1;
}

void	init_cylindr(t_rtv *p, char **tab, int *i)
{
	if (tab == NULL || ft_len_wordtab(tab) != 9)
		ft_exit("Check the Cylindr parameters. Exit");
	p->object[*i] = ft_memalloc(sizeof(t_object));
	if (p->object[*i] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	p->object[*i]->tip = e_cylindr;
	init_coordinates(&p->object[*i]->pos, tab[1]);
	init_coordinates(&p->object[*i]->norm_p, tab[2]);
	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
	p->object[*i]->radius = ft_atof(tab[4]);
	init_color(&p->object[*i]->color, tab[5]);
	p->object[*i]->specular = ft_atoi(tab[6]);
	p->object[*i]->reflection = ft_atof(tab[7]);
	p->object[*i]->refraction = ft_atof(tab[8]);
	ft_rotat_vector(&p->object[*i]->angle_n, &p->object[*i]->norm_p);
	*i += 1;
}

void	init_plane(t_rtv *p, char **tab, int *i)
{
	if (tab == NULL || ft_len_wordtab(tab) != 8)
		ft_exit("Check the Plane parameters. Exit");
	p->object[*i] = ft_memalloc(sizeof(t_object));
	if (p->object[*i] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	p->object[*i]->tip = e_plane;
	init_coordinates(&p->object[*i]->pos, tab[1]);
	init_coordinates(&p->object[*i]->norm_p, tab[2]);
	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
	init_color(&p->object[*i]->color, tab[4]);
	p->object[*i]->specular = ft_atoi(tab[5]);
	p->object[*i]->reflection = ft_atof(tab[6]);
	p->object[*i]->refraction = ft_atof(tab[7]);
	ft_rotat_vector(&p->object[*i]->angle_n, &p->object[*i]->norm_p);
	*i += 1;
}

void	init_sphere(t_rtv *p, char **tab, int *i)
{
	int	shift;
	int	len_tab;

	len_tab = ft_len_wordtab(tab);
	if (tab == NULL || (len_tab != 7 && len_tab != 9))
		ft_exit("Check the Sphere parameters. Exit");
	p->object[*i] = ft_memalloc(sizeof(t_object));
	if (p->object[*i] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	p->object[*i]->tip = (len_tab == 7) ? e_sphere : e_hemisphere;
	init_coordinates(&p->object[*i]->pos, tab[1]);
	shift = 0;
	if (len_tab == 9)
	{
		init_coordinates(&p->object[*i]->norm_p, tab[2]);
		init_angle_norm(&p->object[*i]->angle_n, tab[3]);
		ft_rotat_vector(&p->object[*i]->angle_n, &p->object[*i]->norm_p);
		shift = 2;
	}
	p->object[*i]->radius = ft_atof(tab[2 + shift]);
	init_color(&p->object[*i]->color, tab[3 + shift]);
	p->object[*i]->specular = ft_atoi(tab[4 + shift]);
	p->object[*i]->reflection = ft_atof(tab[5 + shift]);
	p->object[*i]->refraction = ft_atof(tab[6 + shift]);
	*i += 1;
}

void	init_camera(t_rtv *p, char **tab)
{
	if (tab == NULL || ft_len_wordtab(tab) != 4)
		ft_exit("Check the Camera parameters. Exit");
	p->camera = ft_memalloc(sizeof(t_camera));
	if (p->camera == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	init_coordinates(&p->camera->start, tab[1]);
	init_coordinates(&p->camera->dir, tab[2]);
	init_angle_norm(&p->camera->angle, tab[3]);
	p->camera->pos = p->camera->start;
}
