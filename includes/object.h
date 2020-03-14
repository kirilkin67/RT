#ifndef OBJECT_H
# define OBJECT_H

/*
**The vector structure
*/

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

/*
**The ray
*/

typedef struct	s_camera
{
	t_vector	start;
	t_vector	dir;
	double		pos_cam;
}				t_camera;

/*
**The light structure
*/

typedef struct	s_light
{
	int			tip;
	t_vector	pos;
	float		intensity;
	int			color;
	double		len_light;

}				t_light;

typedef struct	s_discr
{
	t_vector	v2;
	double		a;
	double		b;
	double		c;
	double		k_tan;
	double		pos_n_p;
	double		discr;
	double		sqrt_discr;
	double		d_1;
	double		d_2;
}				t_discr;

/*
**The structure OBJECT
*/

typedef struct	s_object
{
	int			id;
	t_vector	pos;
	t_vector	norm_p;
	t_vector	angle_n;
	t_discr		discr;
	float		radius;
	double		angle;
	double		len_pos;
	float		pos_cam;
	float		reflection;
	int			specular;
	int			color;
}				t_object;

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
	// float		min_dist;
	double		len_ray;
	// float		len;
	// int			mouse_key;
	// int			mouse_x;
	// int			mouse_y;
	// int			num;
	// int			color;
	double		x0;
	double		y0;
	// float		z0;
	// int			flag;
	// int			n;
}				t_rtv;

typedef struct	s_data
{
	t_rtv		*all;
	t_camera	camera;
	t_vector	ray;
	int			y_start;
	int			y_end;
	int			x;
	double		x0;
	double		y0;
}				t_data;

#endif

// typedef struct	s_paint
// {
// 	void		*mlx_ptr;
// 	void		*win_ptr;
// 	void		*img_ptr;
// 	int			*draw;
// 	int			bpp;
// 	int			size_line;
// 	int			endian;
// }				t_paint;

// /* The sphere structure */

// typedef struct	s_sphere
// {
// 	t_vector	pos;
// 	float		radius;
// 	float		len_pos;
// 	int			color;
// 	float		reflection;
// 	int			specular;
// }				t_sphere;

// /* The plane structure */

// typedef struct	s_plane
// {
// 	t_vector	norm;
// 	t_vector	pos;
// 	int			color;
// 	float		reflection;
// 	int			specular;
// }				t_plane;
