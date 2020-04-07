#include "rtv1.h"
#include <stdbool.h> /* Needed for boolean datatype */

char	*ft_strrev(char *s)
{
	size_t	len;
	size_t	i;
	char	swap;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	while (i != len / 2)
	{
		swap = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = swap;
		++i;
	}
	return (s);
}

static size_t	ft_power_s(size_t nb, int power)
{
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	return (nb * ft_power_s(nb, power - 1));
}

static size_t	ft_getval(char *nbr, char *base_from)
{
	size_t	val;
	int		i;
	int		j;
	size_t	len;

	len = ft_strlen(nbr);
	val = 0;
	i = -1;
	while (nbr[++i])
	{
		j = -1;
		while (nbr[i] != base_from[++j])
			;
		val += j * (len - i ? ft_power_s(10, len - i - 1) : 1);
	}
	return (val);
}

char			*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*res;
	size_t	val;
	size_t	len_base;
	int		i;

	val = ft_getval(nbr, base_from);
	len_base = ft_strlen(base_to);
	res = (char*)malloc(sizeof(char) * (32));
	i = 0;
	if (val)
		while (val > 0)
		{
			res[i] = base_to[val % len_base];
			val /= len_base;
			++i;
		}
	else
		res[i++] = base_to[0];
	res[i] = '\0';
	res = ft_strrev(res);
	return (res);
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

double		ft_atof(const char *str)
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

int		ft_ahextocolor(char *ahex)
{
	char	*str;
	char	*tmp;
	int		c;
	int		res;

	str = ft_strdup(ahex);
	str[2] = '\0';
	tmp = ft_convert_base(str, "0123456789ABCDEF", "0123456789");
	c = ft_atoi(tmp);
	res = c << 16;
	free(str);
	free(tmp);
	str = ft_strdup(ahex + 2);
	str[2] = '\0';
	tmp = ft_convert_base(str, "0123456789ABCDEF", "0123456789");
	c = ft_atoi(tmp);
	res |= c << 8;
	free(str);
	free(tmp);
	str = ft_strdup(ahex + 4);
	tmp = ft_convert_base(str, "0123456789ABCDEF", "0123456789");
	res |= ft_atoi(tmp);
	free(str);
	free(tmp);
	return (res);
}
