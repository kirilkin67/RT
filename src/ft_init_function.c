#include "rtv1.h"

void	init_coordinates(t_vector *vector, char *tab)
{
	char	**coord;

	coord = ft_strsplit(tab, ',');
	if (ft_len_wordtab(coord) != 3)
		ft_exit("Check the Coordinates parameters. Exit");
	vector->x = (double)ft_atoi(coord[0]);
	vector->y = (double)ft_atoi(coord[1]);
	vector->z = (double)ft_atoi(coord[2]);
	ft_free_wordtab(coord);
}

void	init_angle_norm(t_vector *angle, char *tab)
{
	char	**coord;

	coord = ft_strsplit(tab, ',');
	if (ft_len_wordtab(coord) != 3)
		ft_exit("Check the Angle parameters. Exit");
	angle->x = (double)ft_atoi(coord[0]) * PI / 180;
	angle->y = (double)ft_atoi(coord[1]) * PI / 180;
	angle->z = (double)ft_atoi(coord[2]) * PI / 180;
	ft_free_wordtab(coord);
}

void	init_color(t_color *color, char *str)
{
	char	**tab;

	tab = ft_strsplit(str, ',');
	if (ft_len_wordtab(tab) != 3)
		ft_exit("Check the Color parameters. Exit");
	color->red = ft_atoi(tab[0]);
	color->green = ft_atoi(tab[1]);
	color->blue = ft_atoi(tab[2]);
	ft_free_wordtab(tab);
	if ((color->red < 0 || 255 < color->red) || \
		(color->green < 0 || 255 < color->green) || \
		(color->blue < 0 || 255 < color->blue))
		ft_exit("Check the Color parameters. Exit");
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
