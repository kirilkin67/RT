#include "rt.h"

void	calculate_constant(t_rtv *p, t_vector *start)
{
	int	n;

	n = 0;
	while (n < p->n_lights)
	{
		if (p->lights[n]->type == e_point)
			p->lights[n]->pos = ft_sub_vectors(&p->lights[n]->pos, start);
		n += 1;
	}
	n = 0;
	while (n < p->n_objects)
	{
		object_data(p->object[n], start);
		n += 1;
	}
}
