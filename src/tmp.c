#include "rtv1.h"

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

size_t	ft_len_wordtab(char **tab)
{
	size_t len;

	len = 0;
	while (tab[len] != NULL)
		len += 1;
	return (len);
}
