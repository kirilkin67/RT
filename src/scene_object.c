#include "rtv1.h"

void	object_data(t_object *object, t_camera *cam, t_light *light)
{
	if (object->id == 'S')
	{
		object->pos = ft_subtraction_vector(&object->pos, &cam->start);
		object->len_pos = pow(object->pos.x, 2) + pow(object->pos.y, 2) + pow(object->pos.z, 2);
		object->radius = pow(object->radius, 2);
	}
	if (object->id == 'P')
	{
		ft_rotat_vector(object->angle_x, object->angle_y, object->angle_z, &object->norm);
		ft_unit_vector(&object->norm);
		object->pos_cam = ft_vector_scalar(&object->norm, &object->pos) - ft_vector_scalar(&object->norm, &cam->start);
		object->pos = ft_subtraction_vector(&object->pos, &cam->start);
	}
	if (object->id == 'C')
	{
		object->pos = ft_subtraction_vector(&object->pos, &cam->start);
		object->radius = pow(object->radius, 2);
		ft_rotat_vector(object->angle_x, object->angle_y, object->angle_z, &object->norm_p);
		ft_unit_vector(&object->norm_p);
		object->discr.v2 = ft_multiply_vector_num(&object->norm_p, ft_vector_scalar(&object->pos, &object->norm_p));
		object->discr.v2 = ft_subtraction_vector(&object->discr.v2, &object->pos);
		object->discr.c = ft_vector_scalar( &object->discr.v2, &object->discr.v2) - object->radius;
		// printf("X- %f Y- %f Z- %f\n",object->norm_p.x, object->norm_p.y, object->norm_p.z);
		// printf("LEN_NORM %f\n",object->discr.c);
	}
	if (object->id == 'K')
	{
		object->pos = ft_subtraction_vector(&object->pos, &cam->start);
		ft_rotat_vector(object->angle_x, object->angle_y, object->angle_z, &object->norm_p);
		ft_unit_vector(&object->norm_p);
		object->discr.k_tan = 1 + pow(tan(object->angle / 2), 2);
		printf("TAN %f\n", object->discr.k_tan);
		object->discr.pos_n_p = ft_vector_scalar(&object->pos, &object->norm_p);
		printf("N_P- %f\n", object->discr.pos_n_p);
		object->discr.c = ft_vector_scalar(&object->pos, &object->pos) -\
			object->discr.k_tan * pow(object->discr.pos_n_p, 2);
		printf("C- %f\n", object->discr.c);
	}
}

void	scene_object(t_rtv *p, t_camera *camera, t_object **object, t_light *light)
{
	camera->start.x = p->cam_x;
	camera->start.y = p->cam_y;
	camera->start.z = p->cam_z;

	camera->dir.x = 0;
	camera->dir.y = 0;
	camera->dir.z = p->width;

	light->pos.x = -200;
	light->pos.y = 1000;
	light->pos.z = 500;
	light->intensity = 0.6;
	light->color =0xFFFFFF;
	light->pos = ft_subtraction_vector(&light->pos, &camera->start);

	object[0] = (t_object *)malloc(sizeof(t_object));
	object[0]->id = 'S';
	object[0]->pos.x = 200;
	object[0]->pos.y = 500;
	object[0]->pos.z = 1000;
	object[0]->radius = 200;
	object[0]->color = 0xFF00FF; // GOLD 0xFFD700
	object[0]->specular = 500;
	object_data(object[0], camera,light);

	object[1] = (t_object *)malloc(sizeof(t_object));
	object[1]->id = 'S';
	object[1]->pos.x = -200;
	object[1]->pos.y = 500;
	object[1]->pos.z = 1000;
	object[1]->radius = 200;
	object[1]->color = 0xFF00; // GREEN
	object[1]->specular = 200;
	object_data(object[1], camera,light);

	object[2] = (t_object *)malloc(sizeof(t_object));
	object[2]->id = 'S';
	object[2]->pos.x = 0;
	object[2]->pos.y = -1200;
	object[2]->pos.z = 1200;
	object[2]->radius = 1000;
	object[2]->color = 0xFFD700; // FUCHSIA 0xFF00FF
	object[2]->specular = 50;
	object_data(object[2], camera, light);

	object[3] = (t_object *)malloc(sizeof(t_object));
	object[3]->id = 'P';
	object[3]->norm.x = 0;
	object[3]->norm.y = 10;
	object[3]->norm.z = 0;
	object[3]->pos.x = 0;
	object[3]->pos.y = -400;
	object[3]->pos.z = 0;
	object[3]->angle_x = 0;
	object[3]->angle_y = 0;
	object[3]->angle_z = 0.174533;
	object[3]->color = 0xFFA07A;
	object[3]->specular = 100;
	object_data(object[3],camera,light);

	object[4] = (t_object *)malloc(sizeof(t_object));
	object[4]->id = 'C';
	object[4]->norm_p.x = 0;
	object[4]->norm_p.y = 1;
	object[4]->norm_p.z = 0;
	object[4]->pos.x = 0;
	object[4]->pos.y = 100;
	object[4]->pos.z = 1000;
	object[4]->radius = 200;
	object[4]->angle_x = 0;
	object[4]->angle_y = 0;
	object[4]->angle_z = 0;
	object[4]->color = 0x836FFF;
	object[4]->specular = 100;
	object_data(object[4],camera,light);

	object[5] = (t_object *)malloc(sizeof(t_object));
	object[5]->id = 'C';
	object[5]->norm_p.x = 0;
	object[5]->norm_p.y = 1;
	object[5]->norm_p.z = 0;
	object[5]->pos.x = 0;
	object[5]->pos.y = 100;
	object[5]->pos.z = 1000;
	object[5]->radius = 200;
	object[5]->angle_x = 0;
	object[5]->angle_y = 0;
	object[5]->angle_z = 1.570796;
	object[5]->color = 0x836FFF;
	object[5]->specular = 100;
	object_data(object[5],camera,light);

	object[6] = (t_object *)malloc(sizeof(t_object));
	object[6]->id = 'K';
	object[6]->norm_p.x = 0;
	object[6]->norm_p.y = -1;
	object[6]->norm_p.z = 0;
	object[6]->angle = 0.523599;
	object[6]->pos.x = 0;
	object[6]->pos.y = 0;
	object[6]->pos.z = 1000;
	object[6]->angle_x = 0;
	object[6]->angle_y = 0;
	object[6]->angle_z = 0;
	object[6]->color = 0xFF0000;
	object[6]->specular = 100;
	object_data(object[6],camera,light);

}
// 90- 1.570796 45- 0.785398 30- 0.523599 10- 0.174533 5- 0.0872665
