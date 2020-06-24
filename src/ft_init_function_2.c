#include "rtv1.h"

int		close_endian(void *param)
{
	(void)param;
	exit(0);
}

void	ft_exit(void *param)
{
	char *str;

	str = (char *)param;
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(1);
}

int		expose_hook(t_rtv *p)
{
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	print_navigation(p, p->camera);
	print_instructions(p);
	return (1);
}

int		ft_len_untill(const char *str, char c)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != c && str[len] != '\0')
		++len;
	return (len);
}

double	ft_atof(const char *str)
{
	double	result;
	int		i;

	result = (double)ft_atoi(str);
	i = ft_len_untill(str, '.');
	if (i && str[i])
	{
		if (result >= 0 && str[0] != '-')
			result += ((double)ft_atoi(str + i + 1))
				/ ((ft_strlen(str + i + 1) * 10));
		else
			result -= ((double)ft_atoi(str + i + 1))
				/ ((ft_strlen(str + i + 1) * 10));
	}
	return (result);
}

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

// static size_t	ft_power_s(size_t nb, int power)
// {
// 	if (power == 0)
// 		return (1);
// 	if (power < 0)
// 		return (0);
// 	return (nb * ft_power_s(nb, power - 1));
// }
