#include "rtv1.h"

int		ft_freetab(char **tab)
{
	int		i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i += 1;
	}
	free(tab);
	return (0);
}

int		ft_lentab(char **tab)
{
	int len;

	len = 0;
	while (tab[len] != NULL)
		len += 1;
	return (len);
}

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

void	calculate_constant(t_rtv *p, t_vector *start)
{
	t_light *tmp;
	int n;

	// printf("Camera    %p\n", p->camera);
	tmp = p->light;
	while (tmp != NULL)
	{
		// printf("Tmp light %p\n", tmp);
		tmp->pos = ft_subtraction_vector(&tmp->pos, start);
		tmp = tmp->next;
	}
	n = 0;
	while (p->object[n] != NULL)
	{
		object_data(p->object[n], start);
		// printf("Object[%d] %p \n",n, p->object[n]);
		n += 1;
	}
}
