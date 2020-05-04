/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 00:28:17 by mikhail           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/04/22 22:47:01 by mikhail          ###   ########.fr       */
=======
/*   Updated: 2020/04/21 16:59:42 by wrhett           ###   ########.fr       */
>>>>>>> c00d384e4d2b6823a766b6d45aa64a8f08e75a85
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
# include "object.h"
# include "manual.h"
# include "key.h"
# include "error.h"
# include "../minilibx_macos/mlx.h"
# include "../minilibx/mlx.h"
# include "libft.h"
# define ABS(Value) (Value > 0 ? Value : -Value)
# define WIDHT		1000
# define HIGHT		700
# define AMBIENT	0.2
# define K_FOV		20.0
# define K_ZOOM		1.0
# define PI			3.14159265
# define K_DIR		0.087267
# define NUM_THREAD	8
# define COLOR_BG	0xFF
# define COLOR_STR	0xFFFFFF

int			close_endian(void *param);
int			key_press(int key, t_rtv *p);
// int			mouse_press(int button, int x, int y, t_rtv *p);
// int			mouse_release(int button, int x, int y, t_fractol *p);
// int			mouse_movement(int x, int y, t_fractol *p);
void		ft_exit(void *param);
// void		ft_operation(t_rtv *p);
int			ft_pixel_color(t_color *color, float percent);
t_vector	ft_add_vector(t_vector *v1, t_vector *v2); // сложение векторов(вектор)
t_vector	ft_subtraction_vector(t_vector *v1, t_vector *v2); // вычитание векторов(вектор)
t_vector	ft_multiply_vector_num(t_vector *vector, double num); // умножение вектора на число
t_vector	ft_rotation_vector(t_vector *angle, t_vector *ray);
void		ft_rotat_vector(t_vector *angle, t_vector *ray);
void		ft_unit_vector(t_vector *vector);
double		ft_vector_scalar(t_vector *v1, t_vector *v2); // скалярное умножение векторов(число)
double		ft_vector_modul(t_vector *v); // модуль(длина) вектора(число)
double		ft_vector_projection_on_ray(t_vector *v1, t_vector *v2); // проекция вектора V1 на векторV2(ось)
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

//Dobavila
int			ft_lentab(char **tab);
int			ft_freetab(char **tab);
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
// int			ft_ahextocolor(char *ahex);
// char		*ft_convert_base(char *nbr, char *base_from, char *base_to);
// int		ft_illuminat_point_1(t_rtv *p, t_vector *v, t_vector *nor, int n);

#endif
