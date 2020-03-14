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

void	ft_scene_object(t_rtv *p)
{
	p->camera->dir.x = 0;
	p->camera->dir.y = 0;
	p->camera->dir.z = p->width;

	p->light->pos.x = -5;
	p->light->pos.y = 10;
	p->light->pos.z = 0;
	p->light->intensity = 0.6;
	p->light->color =0xFFFFFF;
	p->light->pos = ft_subtraction_vector(&p->light->pos, &p->camera->start);

	p->object[0] = (t_object *)malloc(sizeof(t_object));
	if (p->object[0] == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	p->object[0]->id = 'S';
	p->object[0]->pos.x = 7;
	p->object[0]->pos.y = 1;
	p->object[0]->pos.z = 10;
	p->object[0]->radius = 3;
	p->object[0]->color = 0xFF00FF; // GOLD 0xFFD700 FUCHSIA 0xFF00FF
	p->object[0]->specular = 500;
	object_data(p->object[0], &p->camera->start);

	p->object[1] = (t_object *)malloc(sizeof(t_object));
	p->object[1]->id = 'S';
	p->object[1]->pos.x = 0;
	p->object[1]->pos.y = 5;
	p->object[1]->pos.z = 10;
	p->object[1]->radius = 2;
	p->object[1]->color = 0xFF00; // GREEN
	p->object[1]->specular = 200;
	object_data(p->object[1], &p->camera->start);

	p->object[2] = (t_object *)malloc(sizeof(t_object));
	p->object[2]->id = 'S';
	p->object[2]->pos.x = 0;
	p->object[2]->pos.y = -12;
	p->object[2]->pos.z = 12;
	p->object[2]->radius = 10;
	p->object[2]->color = 0xFFD700;
	p->object[2]->specular = 50;
	object_data(p->object[2], &p->camera->start);

	p->object[3] = (t_object *)malloc(sizeof(t_object));
	p->object[3]->id = 'P';
	p->object[3]->norm_p.x = 0;
	p->object[3]->norm_p.y = 1;
	p->object[3]->norm_p.z = 0;
	p->object[3]->pos.x = 0;
	p->object[3]->pos.y = 0;
	p->object[3]->pos.z = 15;
	p->object[3]->angle_n.x = 1.570796;
	p->object[3]->angle_n.y = 0;
	p->object[3]->angle_n.z = 0;
	p->object[3]->color = 0xFFA07A;
	p->object[3]->specular = 100;
	p->object[3]->norm_p = ft_rotation_vector(&p->object[3]->angle_n, &p->object[3]->norm_p);
	object_data(p->object[3], &p->camera->start);

	p->object[4] = (t_object *)malloc(sizeof(t_object));
	p->object[4]->id = 'C';
	p->object[4]->norm_p.x = 0;
	p->object[4]->norm_p.y = 1;
	p->object[4]->norm_p.z = 0;
	p->object[4]->pos.x = 0;
	p->object[4]->pos.y = 1;
	p->object[4]->pos.z = 10;
	p->object[4]->radius = 1;
	p->object[4]->angle_n.x = 0;
	p->object[4]->angle_n.y = 0;
	p->object[4]->angle_n.z = 0;
	p->object[4]->color = 0x836FFF;
	p->object[4]->specular = 100;
	ft_rotat_vector(&p->object[4]->angle_n, &p->object[4]->norm_p);
	object_data(p->object[4], &p->camera->start);

	p->object[5] = (t_object *)malloc(sizeof(t_object));
	p->object[5]->id = 'C';
	p->object[5]->norm_p.x = 0;
	p->object[5]->norm_p.y = 1;
	p->object[5]->norm_p.z = 0;
	p->object[5]->pos.x = 0;
	p->object[5]->pos.y = 1;
	p->object[5]->pos.z = 10;
	p->object[5]->radius = 1;
	p->object[5]->angle_n.x = 0;
	p->object[5]->angle_n.y = 0;
	p->object[5]->angle_n.z = 1.570796;
	p->object[5]->color = 0x836FFF;
	p->object[5]->specular = 100;
	ft_rotat_vector(&p->object[5]->angle_n, &p->object[5]->norm_p);
	object_data(p->object[5], &p->camera->start);

	p->object[6] = (t_object *)malloc(sizeof(t_object));
	p->object[6]->id = 'K';
	p->object[6]->norm_p.x = 0;
	p->object[6]->norm_p.y = 1;
	p->object[6]->norm_p.z = 0;
	p->object[6]->angle = 0.523599;
	p->object[6]->pos.x = 0;
	p->object[6]->pos.y = 1;
	p->object[6]->pos.z = 10;
	p->object[6]->angle_n.x = 0;
	p->object[6]->angle_n.y = 0;
	p->object[6]->angle_n.z = 1.570796;
	p->object[6]->color = 0xFF0000;
	p->object[6]->specular = 100;
	ft_rotat_vector(&p->object[6]->angle_n, &p->object[6]->norm_p);
	object_data(p->object[6], &p->camera->start);

	p->object[7] = NULL;

}
// 90- 1.570796 45- 0.7854 30- 0.523599 10- 0.174533 5- 0.0872665
