#include "rtv1.h"

int		ft_illuminat_point_plane(t_light *l, t_plane *p, t_vector *v)
{
	t_vector	light;
	t_vector	median;
	float		shade;
	float		shine;

	light = ft_subtraction_vectors(&l->pos, v);
	median = ft_subtraction_vectors(&light, v);
	shade = ft_vector_scalar(&p->norm, &light) / ft_vector_modul(&p->norm) / ft_vector_modul(&light);
	if (shade < 0)
		shade = 0;
	shine = ft_vector_scalar(&p->norm, &median) / ft_vector_modul(&p->norm) / ft_vector_modul(&median);
	if (shine < 0)
		shine = 0;
	shade = AMBIENT + l->intensity * shade + l->intensity * pow(shine, p->specular);
	return (ft_pixel_color(p->color, shade));
}

int		ft_intersect_ray_plane(t_camera *r, t_plane *plane, t_light *l)
{
	float		k_dir;
	float		angele;
	float		pos_v;
	int			point_color;
	t_vector	interset;

	pos_v = ft_vector_scalar(&plane->norm, &plane->pos) - ft_vector_scalar(&plane->norm, &r->start);
	angele = -ft_vector_scalar(&plane->norm, &r->dir) / ft_vector_modul(&plane->norm) / ft_vector_modul(&r->dir);
	if (angele <= 0.001f || pos_v >= 0)
		return (-1);
	else
	{
		k_dir = ft_vector_scalar(&plane->pos, &plane->norm) / ft_vector_scalar(&plane->norm, &r->dir);
		if (k_dir != 0)
		{
			interset = ft_multiply_vector_num(&r->dir, k_dir);
			point_color = ft_illuminat_point_plane(l, plane, &interset);
			// point_color = ft_illumination_point(l, plane, &interset, &plane->norm);
			return (point_color);
		}
	}
	return (-1);
}

void	ft_paint_plane(t_rtv *p, t_camera *r, t_plane *plane, t_light *l)
{
	int	x;
	int	y;
	int	color;
	t_camera tmp;

	p->x0 = WIDHT / 2;
	p->y0 = HIGHT / 2;
	tmp.dir = ft_subtraction_vectors(&r->dir, &r->start);
	plane->pos = ft_subtraction_vectors(&plane->pos, &r->start);
	y = 0;
	while (y < HIGHT)
	{
		x = 0;
		while (x < WIDHT)
		{
			tmp.dir.x = x - p->x0;
			tmp.dir.y = p->y0 - y;
			if ((color = ft_intersect_ray_plane(&tmp, plane, l)) >= 0)
				p->draw[x + y * WIDHT] = color;
			x += 1;
		}
		y += 1;
	}
	// mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
}