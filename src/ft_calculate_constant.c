#include "rtv1.h"

/*
** If the camera position is beyond the plane(если камера за плоскостью),
** normal_p = -normal_p.
*/

void		data_plane(t_object *object, t_vector *start)
{
	ft_unit_vector(&object->norm_p);
	object->pos_cam = ft_vector_scalar(&object->norm_p, &object->pos) -
		ft_vector_scalar(&object->norm_p, start);
	if (object->pos_cam > 0.001f)
		object->norm_p = ft_multiply_vector_num(&object->norm_p, -1);
}

void		object_data(t_object *object, t_vector *start)
{
	if (object->id == e_plane)
		data_plane(object, start);
	object->pos = ft_sub_vectors(&object->pos, start);
	if (object->id == e_sphere)
		object->len_pos = pow(object->pos.x, 2) + pow(object->pos.y, 2) +\
						pow(object->pos.z, 2);
	if (object->id == e_cylindr)
	{
		ft_unit_vector(&object->norm_p);
		object->discr.v2 = ft_multiply_vector_num(&object->norm_p, \
						ft_vector_scalar(&object->pos, &object->norm_p));
		object->discr.v2 = ft_sub_vectors(&object->discr.v2, &object->pos);
		object->discr.c = ft_vector_scalar(&object->discr.v2, \
							&object->discr.v2) - pow(object->radius, 2);
	}
	if (object->id == e_cone)
	{
		ft_unit_vector(&object->norm_p);
		object->discr.k_tan = 1 + pow(tan(object->angle / 2), 2);
		object->discr.pos_n_p = ft_vector_scalar(&object->pos, &object->norm_p);
		object->discr.c = ft_vector_scalar(&object->pos, &object->pos) -\
						object->discr.k_tan * pow(object->discr.pos_n_p, 2);
	}
}

void		calculate_constant(t_rtv *p, t_vector *start)
{
	t_light		*tmp;
	int			n;

	tmp = p->light;
	while (tmp != NULL)
	{
		if (tmp->tip == e_point)
			tmp->pos = ft_sub_vectors(&tmp->pos, start);
		tmp = tmp->next;
	}
	n = 0;
	while (n < p->num)
	{
		object_data(p->object[n], start);
		n += 1;
	}
}
