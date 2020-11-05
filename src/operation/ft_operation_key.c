#include "rt.h"

void effects(int key, t_rtv *p)
{
	if (key == KEY_O)
		p->filter = e_sepia;
	if (key == KEY_I)
		p->filter = e_cartoon;
	if (key == KEY_U)
		p->filter = e_motion_bler;
	if (key == KEY_Y)
		p->filter = e_anaglyph;
	if (key == KEY_T)
		p->filter = e_wave;
	ft_paint_scene(p);
}

void	ft_move_object(int key, t_rtv *p)
{
	int num;
	t_vector move;

	move = (t_vector){0, 0, 0};
	num = p->selected_obj;
	if (key == NUM_KEY_8)
		p->object[num]->pos.z += K_MOVE;
	else if (key == NUM_KEY_2)
		p->object[num]->pos.z -= K_MOVE;
	else if (key == NUM_KEY_6)
		p->object[num]->pos.x += K_MOVE;
	else if (key == NUM_KEY_4)
		p->object[num]->pos.x -= K_MOVE;
	else if (key == NUM_KEY_7)
		p->object[num]->pos.y += K_MOVE;
	else if (key == NUM_KEY_1)
		p->object[num]->pos.y -= K_MOVE;
	object_data(p->object[num], &move);
	ft_paint_scene(p);
	
}

void		keyboard_sdl_scancode_pageup(t_rtv *p)
{
	if (p->current_scene == 1)
		p->current_scene = p->scene_num;
	else
		p->current_scene--;
	// if (!construct_scene(sdl.scenes[scene->current_scene], scene, &sdl))
	// 	ft_draw(sdl, *scene);
}

void	scancode(int key, t_rtv *paint)
{
	if (key == PGUP)
	{
		if (paint->current_scene == 1)
			paint->current_scene = paint->scene_num;
		else
			paint->current_scene -= 1;
	}
	if (key == PGDN)
	{
		if (paint->current_scene == paint->scene_num)
			paint->current_scene = 1;
		else
			paint->current_scene += 1;
	}
	mlx_destroy_image(paint->mlx_ptr, paint->img_ptr);
	paint->name_file = paint->scenes[paint->current_scene];
	// ft_print_wordtab(paint->scenes);
	//printf("FILE scene: %s\n", paint->scenes[paint->current_scene]);
	free_memory(paint);
	read_file(paint, paint->name_file);
	ft_init_configuration(paint);
	ft_init_texture(paint);
	calculate_constant(paint, &paint->camera->start);
	ft_paint_scene(paint);
	ft_hook_operation(paint);
	// if (scene->current_scene == sdl.scene_num)
	// 	scene->current_scene = 1;
	// else
	// 	scene->current_scene++;
	// if (!construct_scene(sdl.scenes[scene->current_scene], scene, &sdl))
	// 	ft_draw(sdl, *scene);
}

int		key_press(int key, t_rtv *p)
{
	if (key == KEY_ESC)
		close_window(p);
	if (key == NUM_KEY_PLUS || key == NUM_KEY_MINUS)
		zoom(key, p);
	if (key == KEY_Q || key == KEY_W || key == KEY_E || key == KEY_A ||
	key == KEY_S || key == KEY_D || key == KEY_LEFT || key == KEY_RIGHT ||
	key == KEY_UP || key == KEY_DOWN)
		look(key, p);
	if (key == KEY_M)
		reflect(p);
	if (key == KEY_N || key == KEY_C)
		aliasing_effects(p);
	if (key == KEY_O || key == KEY_I || key == KEY_U || key == KEY_Y ||
	key == KEY_T)
		effects(key, p);
	if (key == KEY_P)
		save_bmp_file(p);
	if (key == KEY_SPACE)
		camera_start(p);
	if (key == KEY_H)
		ft_window_menu(p);
	if ((key == NUM_KEY_8 || key == NUM_KEY_2 || key == NUM_KEY_4 ||
	key == NUM_KEY_6 || key == NUM_KEY_1 || key == NUM_KEY_7) && 
		p->selected_obj != NO_INTERSECT)
		ft_move_object(key, p);
	if (key == PGUP || key == PGDN)
		scancode(key, p);

	return (0);
}
