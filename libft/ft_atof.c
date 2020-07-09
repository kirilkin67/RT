/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:30:07 by wrhett            #+#    #+#             */
/*   Updated: 2020/07/09 21:32:10 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_power(size_t nb, int power)
{
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	return (nb * ft_power(nb, power - 1));
}

double			ft_atof(const char *str)
{
	double	result;
	char	*ptr;

	result = (double)ft_atoi(str);
	ptr = ft_strchr(str, '.');
	if (ptr)
	{
		if (result >= 0 && str[0] != '-')
			result += \
			(double)ft_atoi(ptr + 1) / ft_power(10, ft_strlen(ptr + 1));
		else
			result -= \
			(double)ft_atoi(ptr + 1) / ft_power(10, ft_strlen(ptr + 1));
	}
	return (result);
}
