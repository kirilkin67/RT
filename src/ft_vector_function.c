#include "rtv1.h"

/* Subtract(вычитание векторов V1 из V2 ) two vectors
** and return the resulting vector
*/

t_vector	ft_subtraction_vectors(t_vector *v1, t_vector *v2)
{
	t_vector result;

	result.x = v1->x - v2->x;
	result.y = v1->y - v2->y;
	result.z = v1->z - v2->z;
	return (result);
}

/*
** Add(сложение векторов) two vectors and return the resulting vector
*/

t_vector	ft_addition_vector(t_vector *v1, t_vector *v2)
{
	t_vector result;

	result.x = v1->x - v2->x;
	result.y = v1->y - v2->y;
	result.z = v1->z - v2->z;
	return (result);
}


/*
** Multiply two vectors and return the resulting scalar (dot product)
*/

float		ft_vector_scalar(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

/*
** Проекция vector V1 on vector V2  and return the resulting vector;
** return (sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2)));
*/

float		ft_vector_modul(t_vector *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

float		ft_vector_projection_on_ray(t_vector *v1, t_vector *v2)
{
	float	scalar;
	float	projection;

	scalar = ft_vector_scalar(v1, v2);
	// printf("Scalar V1-V2- %f\n", scalar);
	projection = ft_vector_scalar(v1, v2) / ft_vector_modul(v2);
	// printf("Modul V2- %f\n", ft_vector_modul(v2));
	// printf("Projection V1-V2- %f\n", projection);
	// return (projection);
	return (ft_vector_scalar(v1, v2) / ft_vector_modul(v2));
}

/*
** Multiply vector by a number and return the resulting vector (vector product)
*/

t_vector	ft_multiply_vector_num(t_vector *vector, float num)
{
	t_vector result;

	result.x = num * vector->x;
	result.y = num * vector->y;
	result.z = num * vector->z;
	return (result);
}