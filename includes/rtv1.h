/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 00:28:17 by mikhail           #+#    #+#             */
/*   Updated: 2020/07/09 18:57:32 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include "structure.h"
# include "menu.h"
# include "error.h"
# include "../minilibx_macos/mlx.h"
# include "../minilibx/mlx.h"
# include "libft.h"
# ifdef __linux__
#  include "key_linux.h"
# else
#  include "key_macos.h"
# endif
# define ABS(Value) ((Value) > 0 ? (Value) : -(Value))
# define WIDHT		1200
# define HIGHT		1200
# define AMBIENT	0.2
# define K_FOV		20.0
# define K_ZOOM		1.0
# define PI			3.14159265
# define K_DIR		0.087267
# define NUM_THREAD	8
# define COLOR_BG	0xFF
# define COLOR_BG1	0x0
# define COLOR_STR	0xFFFFFF
# define DEPTH		3

int			close_endian(void *param);
int			key_press(int key, t_rtv *p);
int			expose_hook(t_rtv *p);
// void		ft_operation(t_rtv *p);
void		ft_exit(void *param);
void		print_navigation(t_rtv *p, t_camera *camera);
void		print_instructions(t_rtv *p);
int			local_color(t_color *color, float percent);
int			reflection_color(int color1, int color2, float reflection);
t_vector	ft_add_vector(t_vector *v1, t_vector *v2); // сложение векторов(вектор)
t_vector	ft_subtraction_vector(t_vector *v1, t_vector *v2); // вычитание векторов(вектор)
t_vector	ft_multiply_vector_num(t_vector *vector, double num); // умножение вектора на число
t_vector	ft_rotation_vector(t_vector *angle, t_vector *ray);
void		ft_rotat_vector(t_vector *angle, t_vector *ray);
void		ft_unit_vector(t_vector *vector);
double		ft_vector_scalar(t_vector *v1, t_vector *v2); // скалярное умножение векторов(число)
double		ft_vector_modul(t_vector *v); // модуль(длина) вектора(число)
double		ft_vector_projection_on_ray(t_vector *v1, t_vector *v2); // проекция вектора V1 на вектор V2(ось)
void		ft_solve_discriminant(t_discr *discr);
double		ft_solve_quadratic_equation(t_discr *discr);
double		ft_intersect_ray_sphere(t_vector *ray, t_object *s);
double		ft_intersect_ray_plane(t_vector *r, t_object *p);
double		ft_intersect_ray_cilinder(t_vector *ray, t_object *cil);
double		ft_intersect_ray_cone(t_vector *ray, t_object *cone);
double		ft_ray_trace_object(t_vector *ray, t_object *obj);
void		ft_paint_scene(t_rtv *p);
float		ft_illumination(int s, t_vector *ray, t_vector *med, t_vector *nor);
void		ft_paint_object(t_rtv *p);
void		ft_scene_object(t_rtv *p);
void		object_data(t_object *object, t_vector *cam);
void		calculate_constant(t_rtv *p, t_vector *start);
void		ft_multi_thread_paint(t_rtv *paint);
int			ft_calculate_lighting(t_rtv *p, t_vector *cr, t_vector *nr, int n);
int			ft_calculate_reflection(t_rtv *p, t_vector *r, t_vector *n, int *i);
t_vector	ft_calculate_vector_norm(t_rtv *p, int id, t_vector *interset);
int			ft_intersect_obj(t_rtv *p, t_vector *ray, t_vector *s, double *min);

//Dobavila
// size_t		ft_len_wordtab(char **tab);
// int			ft_free_wordtab(char **tab);
void		init_coordinates(t_vector *vector, char *tab);
void		init_angle_norm(t_vector *angle, char *tab);
void		init_color(t_color *color, char *str);
void		init_tab_object(t_rtv *paint, char *src);
void		init_konys(t_rtv *p, char **tab, int *i);
void		init_cylindr(t_rtv *p, char **tab, int *i);
void		init_plane(t_rtv *p, char **tab, int *i);
void		init_sphere(t_rtv *p, char **tab, int *i);
void		init_camera(t_rtv *p, char **tab);
t_light		*init_light(t_light *light, char **tab);
void		add_obj_to_tab(t_rtv *paint, char **tab, int *i);
double		ft_atof(const char *str);
int			how_many_object(char *src);
// int		ft_illuminat_point_1(t_rtv *p, t_vector *v, t_vector *nor, int n);
int			mouse_press(int button, int x, int y, t_rtv *p);
// int		mouse_release(int button, int x, int y, t_rtv *p);
int		mouse_movement(int x, int y, t_rtv *p);
void	look(int key, t_rtv *p);
#endif
