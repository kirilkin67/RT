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
# define WIDHT	1200
# define HIGHT	1000
# define AMBIENT 0.2
// # define MAX_ZOOM	20000
# define K_FOV	20.0
# define K_ZOOM	50.0
# define K_DIR	0.087266462599716
# define COLOR	100000
# define COLOR1	0xFF00
# define COLOR2	0x800080
# define COLOR_FON	0x0

typedef struct	s_dot
{
	int			x;
	int			y;
	int			z;
	int			radius;
	int			color;
}				t_dot;

typedef struct s_paint
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*draw;
	int			bpp;
	int			size_line;
	int			endian;
}				t_paint;

typedef struct	s_rtv
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*draw;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			hight;
	// int			mouse_key;
	// int			mouse_x;
	// int			mouse_y;
	float		cam_x;
	float		cam_y;
	float		cam_z;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	// double		zoom;
	float		len_ray;
	float		min_dist;
	int			id;
	// int			y_start;
	// int			y_end;
	// int			num;
	// double		angle;
	// double		k_look;
	int			color;
	int			x0;
	int			y0;
	int			z0;
	// int			flag;
	// int			flag_color;
	int			n;
}				t_rtv;

int				close_endian(void *param);
int				key_press(int key, t_rtv *p);
int				mouse_press(int button, int x, int y, t_rtv *p);
// int				mouse_release(int button, int x, int y, t_fractol *p);
// int				mouse_movement(int x, int y, t_fractol *p);
void			ft_exit(void *param);
void			ft_operation(t_rtv *p);
int				ft_pixel_color(int color, float percent);
// void			ft_operation_key(t_fractol *p);
t_dot			ft_parametr_sphere(int x, int y, int radius, int color); // для рисования фигур
void			ft_paint_sphere_dot(t_rtv *p, t_dot *s);// функция для рисования фигур
void			ft_paint_circle(t_rtv *p, t_dot *s);// функция Брезенхема для рисования фигур
void			ft_paint_circle_alfa(t_rtv *p, int x0, int y0, int radius, int color);//функция Брезенхема для рисования фигур
// void			ft_parametr(t_rtv *p);
// void			ft_multi_thread(t_rtv *paint);
t_vector		ft_add_vector(t_vector *v1, t_vector *v2); // сложение векторов(вектор)
t_vector		ft_subtraction_vector(t_vector *v1, t_vector *v2); // вычитание векторов(вектор)
t_vector		ft_multiply_vector_num(t_vector *vector, float num); // умножение вектора на число
t_vector		ft_rotation_vector(t_rtv *p, t_vector *dot);
void			ft_unit_vector(t_vector *vector);
float			ft_vector_scalar(t_vector *v1, t_vector *v2); // скалярное умножение векторов(число)
float			ft_vector_modul(t_vector *v); // модуль(длина) вектора(число)
float			ft_vector_projection_on_ray(t_vector *v1, t_vector *v2); // проекция вектора V1 на векторV2(ось)
float			ft_intersect_ray_sphere(t_vector *ray, t_object *s);
float			ft_intersect_ray_plane(t_vector *r, t_object *p);
float			ft_intersect_ray_cilinder(t_vector *ray, t_object *cil);
void			ft_paint_scene(t_rtv *p);
void			scene(t_rtv *p, t_camera *camera, t_sphere **sphere, t_light *light, t_plane *plane);
int				ft_illumination_point(t_light *l, t_object *s, t_vector *v);
void			ft_paint_object(t_rtv *p, t_camera *cam, t_object **obj, t_light *l);

#endif