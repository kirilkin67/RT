/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_wordtab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:39:02 by wrhett            #+#    #+#             */
/*   Updated: 2020/06/09 23:27:46 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free_wordtab(char **tab)
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
