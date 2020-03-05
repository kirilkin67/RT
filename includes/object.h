#ifndef OBJECT_H
# define OBJECT_H

/* The vector structure */

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

/* The ray */

typedef struct	s_camera
{
	t_vector	start;
	t_vector	dir;
	double		pos_cam;
}				t_camera;

/* The light structure */

typedef struct	s_light
{
	t_vector	pos;
	double		intensity;
	int			color;
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

/* The structure OBJECT*/

typedef struct	s_object
{
	int			id;
	t_vector	pos;
	t_vector	norm_p;
	t_vector	norm;
	t_discr		discr;
	double		radius;
	double		angle;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	double		len_pos;
	double		pos_cam;
	// double		scalar_p_n;
	double		len_norm;
	double		dist;
	int			color;
	double		reflection;
	int			specular;
}				t_object;

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

typedef struct	s_dot
{
	double		x;
	double		y;
	double		z;
	int			color;
}				t_dot;

#endif

// /* The sphere structure */

// typedef struct	s_sphere
// {
// 	t_vector	pos;
// 	double		radius;
// 	double		len_pos;
// 	int			color;
// 	double		reflection;
// 	int			specular;
// }				t_sphere;

// /* The plane structure */

// typedef struct	s_plane
// {
// 	t_vector	norm;
// 	t_vector	pos;
// 	int			color;
// 	double		reflection;
// 	int			specular;
// }				t_plane;