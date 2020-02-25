#include "rtv1.h"

void	ft_rotation_dot(t_rtv *p, t_dot *dot)
{
	int x;
	int y;

	y = dot->y;
	dot->y = y * cos(p->angle_x) + dot->z * sin(p->angle_x);
	dot->z = -y * sin(p->angle_x) + dot->z * cos(p->angle_x);
	x = dot->x;
	dot->x = x * cos(p->angle_y) + dot->z * sin(p->angle_y);
	dot->z = -x * sin(p->angle_y) + dot->z * cos(p->angle_y);
	x = dot->x;
	dot->x = x * cos(p->angle_z) - dot->y * sin(p->angle_z);
	dot->y = x * sin(p->angle_z) + dot->y * cos(p->angle_z);
	dot->x = p->x0 + dot->x;
	dot->y = p->y0 + dot->y;
}