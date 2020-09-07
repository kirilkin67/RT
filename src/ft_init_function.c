#include "rtv1.h"

void	init_coordinates(t_vector *vector, char *tab)
{
	char	**coord;

	coord = ft_strsplit(tab, ',');
	if (NULL == coord || ft_len_wordtab(coord) != 3)
		ft_exit("Check the Coordinates parameters. Exit");
	vector->x = ft_atof(coord[0]);
	vector->y = ft_atof(coord[1]);
	vector->z = ft_atof(coord[2]);
	ft_free_wordtab(coord);
}

void	init_angle_norm(t_vector *angle, char *tab)
{
	char	**coord;
	double	pi_radian;

	coord = ft_strsplit(tab, ',');
	if (NULL == coord || ft_len_wordtab(coord) != 3)
		ft_exit("Check the Angle parameters. Exit");
	pi_radian = PI / 180;
	angle->x = ft_atof(coord[0]) * pi_radian;
	angle->y = ft_atof(coord[1]) * pi_radian;
	angle->z = ft_atof(coord[2]) * pi_radian;
	ft_free_wordtab(coord);
}

void	init_color(t_color *color, char *str)
{
	char	**color_tab;

	color_tab = ft_strsplit(str, ',');
	if (NULL == color_tab || ft_len_wordtab(color_tab) != 3)
		ft_exit("Check the Color parameters. Exit");
	color->red = ft_atoi(color_tab[0]);
	color->green = ft_atoi(color_tab[1]);
	color->blue = ft_atoi(color_tab[2]);
	ft_free_wordtab(color_tab);
	if ((color->red < 0 || 255 < color->red) || \
		(color->green < 0 || 255 < color->green) || \
		(color->blue < 0 || 255 < color->blue))
		ft_exit("Check the Color parameters. Exit");
}

void	init_window(t_rtv *p, char **tab)
{
	if (tab == NULL || ft_len_wordtab(tab) != 3)
		ft_exit("Check the Window parameters. Exit");
	p->width = ft_atoi(tab[1]);
	p->height = ft_atoi(tab[2]);
}

// int		ft_free_wordtab(char **tab)
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

// size_t	ft_len_wordtab(char **tab)
// {
// 	size_t len;

// 	len = 0;
// 	while (tab[len] != NULL)
// 		len += 1;
// 	return (len);
// }
