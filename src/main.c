#include "rtv1.h"

void		ft_exit(void *param)
{
	char *str;

	str = (char *)param;
	if (errno == 0)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	exit(1);
}

int		close_endian(void *param)
{
	(void)param;
	exit(0);
}

void	ft_navigation(t_rtv *p, t_camera *camera)
{
	char	*str;
	char	*coord;

	coord = ft_itoa(camera->dir.z);
	str = ft_strjoin(STR2, coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 20, 0xFFFFFF, str);
	free(coord);
	free(str);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 40, 0xFFFFFF, STR1);
	coord = ft_itoa(camera->start.x);
	str = ft_strjoin("X = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 60, 0xFFFFFF, str);
	free(coord);
	free(str);
	coord = ft_itoa(camera->start.y);
	str = ft_strjoin("Y = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 80, 0xFFFFFF, str);
	free(coord);
	free(str);
	coord = ft_itoa(camera->start.z);
	str = ft_strjoin("Z = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 100, 0xFFFFFF, str);
	free(coord);
	free(str);
}

void	ft_operation(t_rtv *p)
{
	mlx_hook(p->win_ptr, 2, 0, key_press, p);
	mlx_hook(p->win_ptr, 17, 0, close_endian, p);
	// mlx_hook(p->win_ptr, 4, 0, mouse_press, p);
	// mlx_hook(p->win_ptr, 5, 0, mouse_release, p);
	// mlx_hook(p->win_ptr, 6, 0, mouse_movement, p);
	mlx_loop(p->mlx_ptr);
}

void		ft_mlx_init(t_rtv *p, char *str)
{
	p->width = WIDHT;
	p->cam_x = 0;
	p->cam_y = 0;
	p->cam_z = -500;
	p->angle_x = 0;
	p->angle_y = 0;
	p->angle_z = 0;
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, WIDHT, HIGHT, str);
	p->img_ptr = mlx_new_image(p->mlx_ptr, WIDHT, HIGHT);
	p->draw = (int *)mlx_get_data_addr(p->img_ptr, &p->bpp, \
				&p->size_line, &p->endian);
}

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
		object->pos_cam = ft_vector_scalar(&object->norm, &object->pos) - ft_vector_scalar(&object->norm, &cam->start);
		ft_unit_vector(&object->norm);
		object->len_norm = ft_vector_modul(&object->norm);
		// printf("LEN_NORM %f\n",object->len_norm);
		object->pos = ft_subtraction_vector(&object->pos, &cam->start);
	}
	if (object->id == 'C')
	{
		object->pos = ft_subtraction_vector(&object->pos, &cam->start);
		object->len_pos = pow(object->pos.x, 2) + pow(object->pos.y, 2) + pow(object->pos.z, 2);
		object->radius = pow(object->radius, 2);
		ft_unit_vector(&object->norm_p);
		object->len_norm = ft_vector_modul(&object->norm_p);
		// printf("LEN_NORM %f\n",object->len_norm);
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
	// printf("LIGHT_Z- %f", light->pos.z);
	object[0] = (t_object *)malloc(sizeof(t_object));
	object[0]->id = 'S';
	object[0]->pos.x = 200;
	object[0]->pos.y = 300;
	object[0]->pos.z = 1000;
	object[0]->radius = 200;
	object[0]->color = 0xFF00FF; // GOLD 0xFFD700
	object[0]->specular = 500;
	object_data(object[0], camera,light);

	object[1] = (t_object *)malloc(sizeof(t_object));
	object[1]->id = 'S';
	object[1]->pos.x = -200;
	object[1]->pos.y = 300;
	object[1]->pos.z = 1000;
	object[1]->radius = 200;
	object[1]->color = 0xFF00; // GREEN
	object[1]->specular = 200;
	object_data(object[1], camera,light);

	object[2] = (t_object *)malloc(sizeof(t_object));
	object[2]->id = 'S';
	object[2]->pos.x = 0;
	object[2]->pos.y = -900;
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
	object[3]->pos.y = -200;
	object[3]->pos.z = 0;
	object[3]->color = 0xFFA07A;
	object[3]->specular = 100;
	object_data(object[3],camera,light);

	object[4] = (t_object *)malloc(sizeof(t_object));
	object[4]->id = 'C';
	object[4]->norm_p.x = 0;
	object[4]->norm_p.y = 1;
	object[4]->norm_p.z = 0;
	object[4]->pos.x = 0;
	object[4]->pos.y = 0;
	object[4]->pos.z = 1000;
	object[4]->radius = 200;
	object[4]->color = 0x836FFF;
	object[4]->specular = 100;
	object_data(object[4],camera,light);

}

void	ft_paint_scene(t_rtv *p)
{
	t_object	**object;
	t_light		light;
	t_camera	camera;

	if (!(object = (t_object **)malloc(sizeof(t_object *) * 5)))
		ft_exit(ERR_CREAT_TO_ARR);
	scene_object(p, &camera, object, &light);
	ft_paint_object(p, &camera, object, &light);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	ft_navigation(p, &camera);

}

int		main(int argc, char **argv)
{
	t_rtv		paint;
	void		*mlx_ptr;

	ft_mlx_init(&paint, argv[1]);;
	ft_paint_scene(&paint);

	ft_operation(&paint);

	return (0);
}
// 180- 3.1415926535898
// 90 - 1.5707963267949
// 5  - 0.0872664625997