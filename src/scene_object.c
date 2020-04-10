#include "rtv1.h"

void	object_data(t_object *object, t_vector *start)
{
	if (object->id == 'S')
	{
		object->pos = ft_subtraction_vector(&object->pos, start);
		object->len_pos = pow(object->pos.x, 2) + pow(object->pos.y, 2) + pow(object->pos.z, 2);
	}
	if (object->id == 'P')
	{
		ft_unit_vector(&object->norm_p);
		object->pos_cam = ft_vector_scalar(&object->norm_p, &object->pos)\
							- ft_vector_scalar(&object->norm_p, start);
		object->pos = ft_subtraction_vector(&object->pos, start);
	}
	if (object->id == 'C')
	{
		object->pos = ft_subtraction_vector(&object->pos, start);
		ft_unit_vector(&object->norm_p);
		object->discr.v2 = ft_multiply_vector_num(&object->norm_p, ft_vector_scalar(&object->pos, &object->norm_p));
		object->discr.v2 = ft_subtraction_vector(&object->discr.v2, &object->pos);
		object->discr.c = ft_vector_scalar( &object->discr.v2, &object->discr.v2) - pow(object->radius, 2);
	}
	if (object->id == 'K')
	{
		object->pos = ft_subtraction_vector(&object->pos, start);
		ft_unit_vector(&object->norm_p);
		object->discr.k_tan = 1 + pow(tan(object->angle / 2), 2);
		object->discr.pos_n_p = ft_vector_scalar(&object->pos, &object->norm_p);
		object->discr.c = ft_vector_scalar(&object->pos, &object->pos) -\
						object->discr.k_tan * pow(object->discr.pos_n_p, 2);
	}
}


static t_light	*list_create(t_light *light, char **tab)
{
	light = (t_light *)malloc(sizeof(t_light));
	if (light == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	if (ft_lentab(tab) != 5)
		ft_exit(ERR_OBJECT);
	init_coordinates(&light->pos, tab[1]);
	light->intensity = ft_atof(tab[2]);
	light->color = ft_ahextocolor(tab[3]);
	if (ft_strcmp(tab[0], "Point") == 0)
		light->tip = 'P';
	light->next = NULL;
	return (light);
}

// static t_light	*list_prepend(t_light *light, char **tab)
// {
// 	t_light *tmp;

// 	 tmp = light;
// 	if (!cursor || cursor->next == NULL)
// 		cursor->next = list_create(tab);
// 	return (light);
// }

static void	init_light(t_rtv *p, char **tab)
{
	t_light *tmp;

	tmp = NULL;
	if (p->light == NULL)
		p->light = list_create(p->light, tab);
	else
	{
		tmp = list_create(tmp, tab);
		tmp->next = p->light;
		p->light = tmp;
	}
	printf("%p\n", p->light);
	// init_coordinates(&p->light->pos, tab[1]);
	// p->light->intensity = ft_atof(tab[2]);
	// p->light->color = ft_ahextocolor(tab[3]);
	// p->light->next = NULL;
}

void	add_obj_to_tab(t_rtv *paint, char **tab, int *i)
{
	paint->object[*i] = (t_object *)malloc(sizeof(t_object));
	if (paint->object[*i] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
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
			init_light(paint, tab);
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
	// printf("%f\n",paint->light->pos.z);
	// printf("%f\n",paint->light->next->pos.z);
}

// 90- 1.570796 45- 0.7854 30- 0.523599 10- 0.174533 5- 0.0872665
