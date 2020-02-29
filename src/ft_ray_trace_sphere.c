#include "rtv1.h"
#include <stdbool.h> /* Needed for boolean datatype */


// t_vector	ft_vector_intersect(t_vector *d , float dir, float dist)
// {
// 	float		dot_interset;
// 	float		unit_v;
// 	t_vector	interset;

// 	dot_interset = dir - sqrt(dist);
// 	unit_v = dot_interset / ft_vector_modul(d);
// 	interset = ft_multiply_vector_num(d, unit_v);
// 	return (interset);
// }

// int		ft_intersect_ray_sphere(t_camera *r, t_sphere *s, t_light *l)
// {
// 	float		len_dist;
// 	float		len_dir;
// 	int			point_color;
// 	t_vector	interset;
// 	t_vector	normal;

// 	len_dir = ft_vector_projection_on_ray(&s->pos, &r->dir);
// 	len_dist = s->radius - (s->len_pos - pow(len_dir, 2));
// 	if (len_dist < 0.001f)
// 		return (-1);
// 	else
// 	{
// 		interset = ft_vector_intersect(&r->dir, len_dir, len_dist);
// 		normal = ft_subtraction_vectors(&interset, &s->pos);
// 		point_color = ft_illumination_point(l, s, &interset, &normal);
// 	}
// 	return (point_color);
// }

// void	ft_paint_sphere(t_rtv *p, t_camera *r, t_sphere *s, t_light *l)
// {
// 	int	x;
// 	int	y;
// 	int	color;
// 	t_camera tmp;

// 	p->x0 = WIDHT / 2;
// 	p->y0 = HIGHT / 2;
// 	tmp.dir = ft_subtraction_vectors(&r->dir, &r->start);
// 	s->pos = ft_subtraction_vectors(&s->pos, &r->start);
// 	s->len_pos = pow(s->pos.x, 2) + pow(s->pos.y, 2) + pow(s->pos.z, 2);
// 	s->radius = pow(s->radius, 2);
// 	y = 0;
// 	while (y < HIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDHT)
// 		{
// 			tmp.dir.x = x - p->x0;
// 			tmp.dir.y = p->y0 - y;
// 			if ((color = ft_intersect_ray_sphere(&tmp, s, l)) >= 0)
// 				p->draw[x + y * WIDHT] = color;
// 			x += 1;
// 		}
// 		y += 1;
// 	}
// 	// mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
// }

// /* Check if the ray and sphere intersect */
// bool intersectRaySphere(ray *r, sphere *s){
	
// 	/* A = d.d, the vector dot product of the direction */
// 	float A = vectorDot(&r->dir, &r->dir); 
	
// 	/* We need a vector representing the distance between the start of 
// 	 * the ray and the position of the circle.
// 	 * This is the term (p0 - c) 
// 	 */
// 	vector dist = vectorSub(&r->start, &s->pos);
	
// 	/* 2d.(p0 - c) */  
// 	float B = 2 * vectorDot(&r->dir, &dist);
	
// 	/* (p0 - c).(p0 - c) - r^2 */
// 	float C = vectorDot(&dist, &dist) - (s->radius * s->radius);
	
// 	/* Solving the discriminant */
// 	float discr = B * B - 4 * A * C;
	
// 	/* If the discriminant is negative, there are no real roots.
// 	 * Return false in that case as the ray misses the sphere.
// 	 * Return true in all other cases (can be one or two intersections)
// 	 */
// 	if(discr < 0)
// 		return false;
// 	else
// 		return true;
// }
