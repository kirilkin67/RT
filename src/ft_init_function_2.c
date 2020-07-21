#include "rtv1.h"

void	init_window(t_rtv *p, char **tab)
{
	if (tab == NULL || ft_len_wordtab(tab) != 3)
		ft_exit("Check the Window parameters. Exit");
	p->width = ft_atoi(tab[1]);
	p->height = ft_atoi(tab[2]);
}

// int		ft_len_untill(const char *str, char c)
// {
// 	int	len;

// 	len = 0;
// 	if (!str)
// 		return (0);
// 	while (str[len] != c && str[len] != '\0')
// 		len += 1;
// 	return (len);
// }

// static size_t	ft_power(size_t nb, int power)
// {
// 	if (power == 0)
// 		return (1);
// 	if (power < 0)
// 		return (0);
// 	return (nb * ft_power(nb, power - 1));
// }

// double			ft_atof(const char *str)
// {
// 	double	result;
// 	char *ptr;

// 	result = (double)ft_atoi(str);
// 	ptr = ft_strchr(str, '.');
// 	if (ptr)
// 	{
// 		if (result >= 0 && str[0] != '-')
// 			result += (double)ft_atoi(ptr + 1) / ft_power(10, ft_strlen(ptr + 1));
// 		else
// 			result -= (double)ft_atoi(ptr + 1) / ft_power(10, ft_strlen(ptr + 1));
// 	}
// 	printf("len -%zu\n", ft_strlen(ptr + 1));
// 	printf("light -%f\n", result);
// 	return (result);
// }

// char	*ft_strrev(char *s)
// {
// 	size_t	len;
// 	size_t	i;
// 	char	swap;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	len = ft_strlen(s);
// 	while (i != len / 2)
// 	{
// 		swap = s[i];
// 		s[i] = s[len - i - 1];
// 		s[len - i - 1] = swap;
// 		++i;
// 	}
// 	return (s);
// }
