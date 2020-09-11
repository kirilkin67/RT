/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:27:26 by wrhett            #+#    #+#             */
/*   Updated: 2020/09/11 20:46:05 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

// typedef enum
// {
// 	e_pull,
// 	e_push
// }	t_key;

typedef enum
{
	e_pull,
	e_push,
	e_sphere,
	e_plane,
	e_cylindr,
	e_cone,
	e_ambient,
	e_point,
	e_direct
}	t_name;

typedef struct		s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;

/*
**The vector structure
*/

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

/*
**The ray
*/

typedef struct		s_camera
{
	t_vector		start;
	t_vector		dir;
	t_vector		angle;
	double			pos_cam;
	t_vector		pos;
}					t_camera;

/*
**The light structure
*/

typedef struct		s_light
{
	int				tip;
	t_vector		pos;
	double			intensity;
	t_color			color;
	struct s_light	*next;
}					t_light;

/*
**The structure for solve quadratic equation
*/

typedef struct		s_discr
{
	t_vector		v2;
	double			a;
	double			b;
	double			c;
	double			k_tan;
	double			pos_n_p;
	double			discr;
	double			sqrt_discr;
	double			d_1;
	double			d_2;
}					t_discr;

/*
**The structure material object
*/

typedef struct		s_material
{
	int				tip;
	t_color			color;
	double			k_ambient;
	double			k_diffuse;
	double			k_specular;
	int				specular;
	double			reflection;
	double			refraction;
	// struct s_light	*next;
}					t_material;

/*
**The structure OBJECT
*/

typedef struct		s_object
{
	int				id;
	t_vector		pos;
	// t_vector		pos_start;
	t_vector		norm_p;
	t_vector		angle_n;
	t_discr			discr;
	double			radius;
	double			angle;
	double			len_pos;
	double			pos_cam;
	double			reflection;
	double			refraction;
	int				specular;
	t_color			color;
	t_material		material;
}					t_object;

typedef struct		s_rtv
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*draw;
	void			*menu_ptr;
	void			*menu_img;
	int				*menu;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
	int				num;
	t_object		**object;
	t_camera		*camera;
	t_light			*light;
	int				x0;
	int				y0;
	double			fov;
	int				mouse_key;
	int				mouse_x;
	int				mouse_y;
	int				window_menu;
	int				depth_mirror;
	int				depth_refract;
}					t_rtv;

typedef struct		s_data
{
	t_rtv			*all;
	t_camera		camera;
	t_vector		ray;
	int				width;
	// int				height;
	int				y_start;
	int				y_end;
	int				x;
	double			x0;
	double			y0;
	struct s_dara	*reflec;
	struct s_dara	*refrac;
	struct s_dara	*prev;
}					t_data;

typedef struct		s_array
{
	int				reflect;
	int				refract;
}					t_array;

#endif
