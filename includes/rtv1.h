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
// # include <OpenCL/opencl.h>
// # include "../../minilibx_macos/mlx.h"
# include "../../minilibx/mlx.h"
# include "../../libft/libft.h"
# define ABS(Value) (Value > 0 ? Value : -Value)
# define WIDHT		1000
# define HIGHT		700
# define AMBIENT	0.2
# define K_FOV		20.0
# define K_ZOOM		1.0
# define PI			3.14159265
# define K_DIR		0.087267
# define NUM_THREAD	4
# define COLOR1		0xFF00
# define COLOR2		0x800080

int				close_endian(void *param);
int				key_press(int key, t_rtv *p);
int				mouse_press(int button, int x, int y, t_rtv *p);
// int				mouse_release(int button, int x, int y, t_fractol *p);
// int				mouse_movement(int x, int y, t_fractol *p);
void			ft_exit(void *param);
void			ft_operation(t_rtv *p);
int				ft_pixel_color(int color, float percent);
// void			ft_operation_key(t_fractol *p);
// void			ft_multi_thread(t_rtv *paint);
t_vector		ft_add_vector(t_vector *v1, t_vector *v2); // сложение векторов(вектор)
t_vector		ft_subtraction_vector(t_vector *v1, t_vector *v2); // вычитание векторов(вектор)
t_vector		ft_multiply_vector_num(t_vector *vector, double num); // умножение вектора на число
t_vector		ft_rotation_vector(t_vector *angle, t_vector *ray);
void			ft_rotat_vector(t_vector *angle, t_vector *ray);
void			ft_unit_vector(t_vector *vector);
double			ft_vector_scalar(t_vector *v1, t_vector *v2); // скалярное умножение векторов(число)
double			ft_vector_modul(t_vector *v); // модуль(длина) вектора(число)
double			ft_vector_projection_on_ray(t_vector *v1, t_vector *v2); // проекция вектора V1 на векторV2(ось)
void			ft_solve_discriminant(t_discr *discr);
double			ft_solve_quadratic_equation(t_discr *discr);
double			ft_intersect_ray_sphere(t_vector *ray, t_object *s);
double			ft_intersect_ray_plane(t_vector *r, t_object *p);
double			ft_intersect_ray_cilinder(t_vector *ray, t_object *cil);
double			ft_intersect_ray_cone(t_vector *ray, t_object *cone);
double			ft_ray_trace_object(t_vector *ray, t_object *obj);
void			ft_paint_scene(t_rtv *p);
int				ft_illuminat_point(t_rtv *p, t_vector *v, t_vector *nor, int n);
void			calculate_constant(t_rtv *p, t_vector *start);
void			ft_paint_object(t_rtv *p);
void			ft_scene_object(t_rtv *p);
void			object_data(t_object *object, t_vector *cam);
void			ft_multi_thread_paint(t_rtv *paint);

//Dobavila
int				ft_lentab(char **tab);
int				ft_freetab(char **tab);
void			init_coordinates(t_vector *vector, char *tab);
void			init_angle_norm(t_vector *angle, char *tab);
void			init_tab_object(t_rtv *paint, char *src);
//void			add_obj_to_tab(t_rtv *paint, char **tab, int i);
//void			init_light(t_rtv *p, char **tab, int i);
//void			init_sphere(t_rtv *p, char **tab, int i);
//void			init_plane(t_rtv *p, char **tab, int i);
//void			init_cylind(t_rtv *p, char **tab, int i);
//void			init_konys(t_rtv *p, char **tab, int i);
char			*ft_convert_base(char *nbr, char *base_from, char *base_to);
double			ft_atof(const char *str);
int				ft_ahextocolor(char *ahex);

#endif
