#include "rt.h"

t_color	parsing_color(char *str, int *index)
{
	t_color	res;
	int		i;

	i = 0;
	i = *index + 2;
	if (ft_atoi(&str[i]) >= 0 && ft_atoi(&str[i]) <= 255)
		res.red = ft_atoi(&str[i]);
	else
		file_contents_error();
	i = go_to_coma(str, i);
	if (ft_atoi(&str[i]) >= 0 && ft_atoi(&str[i]) <= 255)
		res.green = ft_atoi(&str[i]);
	else
		file_contents_error();
	i = go_to_coma(str, i);
	if (ft_atoi(&str[i]) >= 0 && ft_atoi(&str[i]) <= 255)
		res.blue = ft_atoi(&str[i]);
	else
		file_contents_error();
	i = go_to_coma(str, i);
	*index = i;
	return (res);
}

int		parsing_object_type(char *str, int *index)
{
	int	rez;
	int	i;

	rez = 0;
	i = *index + 1;
	*index = *index + 1;
	if ((find_quotes(str, index, "\"sphere\"\0")))
		return (rez = e_sphere);
	*index = i;
	if ((find_quotes(str, index, "\"plane\"\0")))
		return (rez = e_plane);
	*index = i;
	if ((find_quotes(str, index, "\"cylinder\"\0")))
		return (rez = e_cylindr);
	*index = i;
	if ((find_quotes(str, index, "\"cone\"\0")))
		return (rez = e_cone);
	*index = i;
	if ((find_quotes(str, index, "\"paraboloid\"\0")))
		return (rez = e_paraboloid);
	*index = i;
	if ((find_quotes(str, index, "\"tube\"\0")))
		return (rez = e_tube);
	*index = i;
	if ((find_quotes(str, index, "\"hemisphere\"\0")))
		return (rez = e_hemisphere);
	*index = i;
	if ((find_quotes(str, index, "\"ring\"\0")))
		return (rez = e_ring);
	*index = i;
	return (rez);
}
