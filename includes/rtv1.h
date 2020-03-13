#ifndef RTV1_H
# define RTV1_H
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdbool.h>
# include "object.h"
# include "manual.h"
# include "key.h"
# include "error.h"
// # include <OpenCL/opencl.h>
# include "../../libft/libft.h"
# define ABS(Value) (Value > 0 ? Value : -Value)
# define WIDHT		1200
# define HIGHT		1000
# define AMBIENT	0.2
# define K_FOV		20.0
# define K_ZOOM		1.0
# define K_DIR		0.087267
# define NUM_THREAD	8
# define COLOR1		0xFF00
# define COLOR2		0x800080

typedef struct	s_rtv
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*draw;
	int			bpp;
	int			size_line;
	int			endian;
	// int			y_start;
	// int			y_end;
	// int			x;
	int			width;
	// int			hight;
	t_object	**object;
	t_camera	*camera;
	t_light		*light;
	t_vector	angle;
	// t_vector	interset;
	float		min_dist;
	int			id;
	float		len_ray;
	float		shade;
	float		len_light;
	float		len;
	// int			mouse_key;
	// int			mouse_x;
	// int			mouse_y;
	// int			num;
	// float		k_look;
	int			color;
	int			x0;
	int			y0;
	// float		z0;
	// int			flag;
	// int			n;
}				t_rtv;

typedef struct	s_data
{
	t_rtv		*all;
	t_camera	camera;
	t_vector	ray;
	// t_vector	norm;
	int			y_start;
	int			y_end;
	int			x;
	int			color;
}				t_data;

int				close_endian(void *param);
int				key_press(int key, t_rtv *p);
int				mouse_press(int button, int x, int y, t_rtv *p);
// int				mouse_release(int button, int x, int y, t_fractol *p);
// int				mouse_movement(int x, int y, t_fractol *p);
void			ft_exit(void *param);
void			ft_operation(t_rtv *p);
int				ft_pixel_color(int color, float percent);
// void			ft_operation_key(t_fractol *p);
// void			ft_parametr(t_rtv *p);
// void			ft_multi_thread(t_rtv *paint);
t_vector		ft_add_vector(t_vector *v1, t_vector *v2); // сложение векторов(вектор)
t_vector		ft_subtraction_vector(t_vector *v1, t_vector *v2); // вычитание векторов(вектор)
t_vector		ft_multiply_vector_num(t_vector *vector, float num); // умножение вектора на число
t_vector		ft_rotation_vector(t_vector *angle, t_vector *ray);
void			ft_rotat_vector(t_vector *angle, t_vector *ray);
void			ft_unit_vector(t_vector *vector);
float			ft_vector_scalar(t_vector *v1, t_vector *v2); // скалярное умножение векторов(число)
float			ft_vector_modul(t_vector *v); // модуль(длина) вектора(число)
float			ft_vector_projection_on_ray(t_vector *v1, t_vector *v2); // проекция вектора V1 на векторV2(ось)
void			ft_solve_discriminant(t_discr *discr);
float			ft_solve_quadratic_equation(t_discr *discr);
float			ft_intersect_ray_sphere(t_vector *ray, t_object *s);
float			ft_intersect_ray_plane(t_vector *r, t_object *p);
float			ft_intersect_ray_cilinder(t_vector *ray, t_object *cil);
float			ft_intersect_ray_cone(t_vector *ray, t_object *cone);
float			ft_ray_trace_object(t_vector *ray, t_object *obj);
void			ft_paint_scene(t_rtv *p);
int				illuminat_point(t_rtv *p, t_vector *v, t_vector *norm, int n);
void			ft_paint_object(t_rtv *p);
void			ft_scene_object(t_rtv *p);
void			object_data(t_object *object, t_vector *cam);
void			ft_multi_thread_paint(t_rtv *paint);

#endif
