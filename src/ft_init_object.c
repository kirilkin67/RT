#include "rtv1.h"

void	init_konys(t_rtv *p, char **tab, int *i)
{
	if (tab == NULL || ft_lentab(tab) != 7)
		ft_exit("Check the Cone parameters. Exit");
	p->object[*i]->id = 'K';
	init_coordinates(&p->object[*i]->pos, tab[1]);
	init_coordinates(&p->object[*i]->norm_p, tab[2]);
	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
	p->object[*i]->angle = ft_atoi(tab[4]) * PI / 180;
	p->object[*i]->color = ft_ahextocolor(tab[5]);
	p->object[*i]->specular = ft_atoi(tab[6]);
	ft_rotat_vector(&p->object[*i]->angle_n, &p->object[*i]->norm_p);
	*i += 1;
}

void	init_cylind(t_rtv *p, char **tab, int *i)
{
	if (tab == NULL || ft_lentab(tab) != 7)
		ft_exit("Check the Cylindr parameters. Exit");
	p->object[*i]->id = 'C';
	init_coordinates(&p->object[*i]->pos, tab[1]);
	init_coordinates(&p->object[*i]->norm_p, tab[2]);
	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
	p->object[*i]->radius = ft_atoi(tab[4]);
	p->object[*i]->color = ft_ahextocolor(tab[5]);
	p->object[*i]->specular = ft_atoi(tab[6]);
	ft_rotat_vector(&p->object[*i]->angle_n, &p->object[*i]->norm_p);
	*i += 1;
}

void	init_plane(t_rtv *p, char **tab, int *i)
{
	if (tab == NULL || ft_lentab(tab) != 6)
		ft_exit("Check the Plane parameters. Exit");
	p->object[*i]->id = 'P';
	init_coordinates(&p->object[*i]->pos, tab[1]);
	init_coordinates(&p->object[*i]->norm_p, tab[2]);
	init_angle_norm(&p->object[*i]->angle_n, tab[3]);
	p->object[*i]->color = ft_ahextocolor(tab[4]);
	p->object[*i]->specular = ft_atoi(tab[5]);
	ft_rotat_vector(&p->object[*i]->angle_n, &p->object[*i]->norm_p);
	*i += 1;
}

void	init_sphere(t_rtv *p, char **tab, int *i)
{
	if (tab == NULL || ft_lentab(tab) != 5)
		ft_exit("Check the Sphere parameters. Exit");
	p->object[*i]->id = 'S';
	init_coordinates(&p->object[*i]->pos, tab[1]);
	p->object[*i]->radius = ft_atoi(tab[2]);
	p->object[*i]->color = ft_ahextocolor(tab[3]);
	p->object[*i]->specular = ft_atoi(tab[4]);
	*i += 1;
}

void	init_camera(t_rtv *p, char **tab)
{
	if (tab == NULL || ft_lentab(tab) != 4)
		ft_exit("Check the Camera parameters. Exit");
	p->camera = (t_camera *)malloc(sizeof(t_camera));
	if (p->camera == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	init_coordinates(&p->camera->start, tab[1]);
	init_coordinates(&p->camera->dir, tab[2]);
	init_angle_norm(&p->camera->angle, tab[3]);
	p->camera->dir.z = p->width;
}
