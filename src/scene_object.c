#include "rtv1.h"

void	data_plane(t_object *object, t_vector *start)
{
	ft_unit_vector(&object->norm_p);
	object->pos_cam = ft_vector_scalar(&object->norm_p, &object->pos)\
							- ft_vector_scalar(&object->norm_p, start);
	// object->pos = ft_subtraction_vector(&object->pos, start);
}

void	object_data(t_object *object, t_vector *start)
{
	if (object->id == 'P')
		data_plane(object, start);
	object->pos = ft_subtraction_vector(&object->pos, start);
	if (object->id == 'S')
	{
		// object->pos = ft_subtraction_vector(&object->pos, start);
		object->len_pos = pow(object->pos.x, 2) + pow(object->pos.y, 2) + pow(object->pos.z, 2);
	}
	if (object->id == 'C')
	{
		// object->pos = ft_subtraction_vector(&object->pos, start);
		ft_unit_vector(&object->norm_p);
		object->discr.v2 = ft_multiply_vector_num(&object->norm_p, ft_vector_scalar(&object->pos, &object->norm_p));
		object->discr.v2 = ft_subtraction_vector(&object->discr.v2, &object->pos);
		object->discr.c = ft_vector_scalar( &object->discr.v2, &object->discr.v2) - pow(object->radius, 2);
	}
	if (object->id == 'K')
	{
		// object->pos = ft_subtraction_vector(&object->pos, start);
		ft_unit_vector(&object->norm_p);
		object->discr.k_tan = 1 + pow(tan(object->angle / 2), 2);
		object->discr.pos_n_p = ft_vector_scalar(&object->pos, &object->norm_p);
		object->discr.c = ft_vector_scalar(&object->pos, &object->pos) -\
						object->discr.k_tan * pow(object->discr.pos_n_p, 2);
	}
}

void	calculate_constant(t_rtv *p, t_vector *start)
{
	t_light *tmp;
	int n;

	// printf("Camera    %p\n", p->camera);
	tmp = p->light;
	while (tmp != NULL)
	{
		// printf("Tmp light %p\n", tmp);
		tmp->pos = ft_subtraction_vector(&tmp->pos, start);
		tmp = tmp->next;
	}
	n = 0;
	while (p->object[n] != NULL)
	{
		object_data(p->object[n], start);
		// printf("Object[%d] %p \n",n, p->object[n]);
		n += 1;
	}
}

void	add_obj_to_tab(t_rtv *paint, char **tab, int *i)
{
	if (ft_strcmp(tab[0], "Sphere") == 0)
		init_sphere(paint, tab, i);
	else if (ft_strcmp(tab[0], "Plane") == 0)
		init_plane(paint, tab, i);
	else if (ft_strcmp(tab[0], "Cylind") == 0)
		init_cylind(paint, tab, i);
	else if (ft_strcmp(tab[0], "Cone") == 0)
		init_konys(paint, tab, i);
}

void	init_tab_object(t_rtv *paint, char *src)
{
	int		i;
	int		fd;
	char	*line;
	char	**tab;

	line = NULL;
	i = 0;
	if ((fd = open(src, O_RDONLY)) <= 0)
		ft_exit(ERR_FILE_OPEN);
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		if (ft_strcmp(tab[0], "Light") == 0)
			paint->light = init_light(paint->light, tab);
		if (ft_strcmp(tab[0], "Camera") == 0)
			init_camera(paint, tab);
		else
			add_obj_to_tab(paint, tab, &i);
		ft_freetab(tab);
		free(line);
	}
	paint->object[i] = NULL;
	if (paint->camera == NULL)
		ft_exit("No camera. Exit");
	if (paint->light == NULL)
		ft_exit("No light. Exit");
	close(fd);
}
