#include "rtv1.h"

// int		ft_intersect_ray_plane(t_camera *r, t_plane *plane, t_light *l)
// {
// 	float		k_dir;
// 	float		angele;
// 	float		pos_cam;
// 	int			point_color;
// 	t_vector	interset;

// 	pos_cam = ft_vector_scalar(&plane->norm, &plane->pos) - ft_vector_scalar(&plane->norm, &r->start);
// 	angele = -ft_vector_scalar(&plane->norm, &r->dir) / ft_vector_modul(&plane->norm) / ft_vector_modul(&r->dir);
// 	if (angele <= 0.001f || pos_cam >= 0)
// 		return (-1);
// 	else
// 	{
// 		k_dir = ft_vector_scalar(&plane->pos, &plane->norm) / ft_vector_scalar(&plane->norm, &r->dir);
// 		if (k_dir != 0)
// 		{
// 			interset = ft_multiply_vector_num(&r->dir, k_dir);
// 			point_color = ft_illuminat_point_plane(l, plane, &interset);
// 			// point_color = ft_illumination_point(l, plane, &interset, &plane->norm);
// 			return (point_color);
// 		}
// 	}
// 	return (-1);
// }
