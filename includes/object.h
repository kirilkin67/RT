#ifndef OBJECT_H
# define OBJECT_H

/* The vector structure */

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

/* The ray */

typedef struct	s_camera
{
	t_vector start;
	t_vector dir;
}				t_camera;

/* The light structure */

typedef struct	s_light
{
	t_vector	pos;
	float		intensity;
	int			color;
}				t_light;

/* The sphere structure */

typedef struct	s_sphere
{
	t_vector	pos;
	float		radius;
	float		len_pos;
	int			color;
	float		reflection;
	int			specular;
}				t_sphere;

/* The plane structure */

typedef struct	s_plane
{
	t_vector	norm;
	t_vector	dot;
	int			color;
	float		reflection;
	int			specular;
}				t_plane;
#endif