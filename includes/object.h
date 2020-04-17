/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhail <mikhail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 00:25:55 by mikhail           #+#    #+#             */
/*   Updated: 2020/04/18 00:27:57 by mikhail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

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
	double		x;
	double				y;
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
	float			intensity;
	t_color			color;
	struct s_light	*next;
}					t_light;

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
**The structure OBJECT
*/

typedef struct		s_object
{
	int				id;
	t_vector		pos;
	t_vector		pos_start;
	t_vector		norm_p;
	t_vector		angle_n;
	t_discr			discr;
	float			radius;
	double			angle;
	double			len_pos;
	float			pos_cam;
	float			reflection;
	int				specular;
	t_color			color;
}					t_object;

typedef struct		s_rtv
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*draw;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	t_object		**object;
	t_camera		*camera;
	t_light			*light;
	double			len_ray;
	double			x0;
	double			y0;
}					t_rtv;

typedef struct		s_data
{
	t_rtv			*all;
	t_camera		camera;
	t_vector		ray;
	int				y_start;
	int				y_end;
	int				x;
	double			x0;
	double			y0;
}					t_data;

#endif
