#ifndef OBJECT_H
# define OBJECT_H

/*
**The vector structure
*/

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

/*
**The ray
*/

typedef struct	s_camera
{
	t_vector	start;
	t_vector	dir;
	float		pos_cam;
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
	float		len_light;

}				t_light;

typedef struct	s_discr
{
	t_vector	v2;
	float		a;
	float		b;
	float		c;
	float		k_tan;
	float		pos_n_p;
	float		discr;
	float		sqrt_discr;
	float		d_1;
	float		d_2;
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
	float		len_pos;
	float		pos_cam;
	int			color;
	float		reflection;
	int			specular;
	float		shade;
}				t_object;

typedef struct	s_dot
{
	float		x;
	float		y;
	float		z;
}				t_dot;

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
