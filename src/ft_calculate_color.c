#include "rtv1.h"

int	sepia(int color)
{
	int		rgb[3];
	int		rgb_start[3];
	rgb_start[0] = (color >> 16) & 0xFF;
	rgb_start[1] = (color >> 8) & 0xFF;
	rgb_start[2] = color & 0xFF;

	if ((rgb[0] = (rgb_start[0] * .393) + (rgb_start[1] * .769) + (rgb_start[2] * .189)) > 255)
		rgb[0]= 255;
	else
		rgb[0] = (rgb_start[0] * .393) + (rgb_start[1] * .769) + (rgb_start[2] * .189);

	if ((rgb[1] = (rgb_start[0] * .349) + (rgb_start[1] * .686) + (rgb_start[2] * .168)) > 255)
		rgb[1] = 255;
	else
		rgb[1] = (rgb_start[0] * .349) + (rgb_start[1] * .686) + (rgb_start[2] * .168);


	if ((rgb[2] = (rgb_start[0] * .272) + (rgb_start[1] * .354) + (rgb_start[2] * .131)) > 255)
		rgb[2] = 255;
	else
		rgb[2] = (rgb_start[0] * .272) + (rgb_start[1] * .354) + (rgb_start[2] * .131);

	color = ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
	return (color);
}

double		illumination(int specular,
					t_vector *ray, t_vector *reflect, t_vector *norm)
{
	double	shade;
	double	shine;

	shine = 0.0;
	shade = ft_vector_scalar(norm, ray);
	if (shade < 0)
		shade = 0;
	if (shade >= 0 && specular != 0)
		shine = ft_vector_scalar(ray, reflect);
	if (shine > 0)
		shade = shade + powf(shine, specular);
	return (shade);
}

double		is_point_shadow(t_object **object, t_vector *intersect, t_vector *ray, double *k_light)
{
	t_object	tmp_object;
	t_vector	new_start;
	double		len_light;
	t_cross		obj;
	int			n;

	len_light = ft_vector_modul(ray);
	ft_unit_vector(ray);
	new_start = ft_multiply_vector_num(intersect, 0.99);
	// new_start = new_start_vector(intersect, ray, 0.001);
	*k_light = 1.0;
	n = 0;
	while (NULL != object[n])
	{
		tmp_object = *object[n];
		object_data(&tmp_object, &new_start);
		obj = ft_raytrace_objects(&tmp_object, ray);
		if ((0.001 < obj.len && obj.len < len_light) && obj.id == INTERSECT)
		{
			*k_light *= tmp_object.refraction;
			if (tmp_object.refraction == 0)
				return (*k_light);
		}
		n += 1;
	}
	return (*k_light);
}

t_vector	ft_vector_light_cross(t_light *source, t_vector *intersect)
{
	t_vector light_cross;

	if (source->type == e_point)
		light_cross = ft_sub_vectors(&source->pos, intersect);
	if (source->type == e_direct)
		light_cross = source->direction;
	return (light_cross);
}

// double		ft_calculate_lighting_list(t_rtv *p, t_cross *cross, t_vector *norm)
// {
// 	t_vector	light_cross;
// 	t_vector	reflect;
// 	t_light		*source;
// 	double		k_light;
// 	double		shade;

// 	shade = 0.0;
// 	source = p->light;
// 	while (source != NULL)
// 	{
// 		if (source->type == e_ambient)
// 			shade += source->intensity;
// 		if (source->type == e_point || source->type == e_direct)
// 		{
// 			light_cross = ft_vector_light_cross(source, &cross->vec3);
// 			reflect = ft_reflection_ray(&cross->vec3, norm); // Model Fonga
// 			k_light = is_point_shadow(p->object, &cross->vec3, &light_cross, &k_light);
// 			shade += source->intensity * k_light *
// 	illumination(p->object[cross->id]->specular, &light_cross, &reflect, norm);
// 		}
// 		source = source->next;
// 	}
// 	return (shade);
// }

double		ft_calculate_lighting(t_rtv *p, t_cross *cross, t_vector *norm)
{
	t_vector	light_cross;
	t_vector	reflect;
	int num = 0;
	double		k_light;
	double		shade;

	shade = 0.0;
	while (num < p->n_lights)
	{
		if (p->lights[num]->type == e_ambient)
			shade += p->lights[num]->intensity;
		if (p->lights[num]->type == e_point || p->lights[num]->type == e_direct)
		{
			light_cross = ft_vector_light_cross(p->lights[num], &cross->vec3);
			reflect = ft_reflection_ray(&cross->vec3, norm); // Model Fonga
			k_light = is_point_shadow(p->object, &cross->vec3, &light_cross, &k_light);
			shade += p->lights[num]->intensity * k_light *
	illumination(p->object[cross->id]->specular, &light_cross, &reflect, norm);
		}
		num++;
	}
	return (shade);
}

int			ft_local_color(t_rtv *p, t_cross *intersect, t_vector *norm)
{
	double		shade;

	shade = ft_calculate_lighting(p, intersect, norm);
	return (color(&p->object[intersect->id]->color, shade));
}
