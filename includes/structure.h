/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:27:26 by wrhett            #+#    #+#             */
/*   Updated: 2020/07/30 21:12:48 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum
{
	e_pull,
	e_push
}	t_key;

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
	double			radius;
	double			angle;
	double			len_pos;
	double			pos_cam;
	float			reflection;
	int				specular;
	t_color			color;
}					t_object;

typedef struct		s_rtv
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	void			*str_ptr;
	int				*draw;
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
	int				mouse_key;
	int				mouse_x;
	int				mouse_y;
	int				window_menu;
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
}					t_data;

#endif
