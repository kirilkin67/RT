#include "rtv1.h"

static void	ft_solve_discriminant(t_discr *discr)
{
	discr->discr = (double)(discr->b * discr->b - 4 * discr->a * discr->c);
}

double		ft_solve_quadratic_equation(t_discr *discr)
{
	ft_solve_discriminant(discr);
	if (discr->discr < 0)
		return (NO_INTERSECT);
	discr->sqrt_discr = sqrtf(discr->discr);
	discr->a = 2 * discr->a;
	discr->d_1 = (-discr->b - discr->sqrt_discr) / discr->a;
	discr->d_2 = (-discr->b + discr->sqrt_discr) / discr->a;
	if (discr->d_1 > 0.001f && discr->d_2 > 0.001f)
	{
		discr->d_1 = (discr->d_1 <= discr->d_2) ? discr->d_1 : discr->d_2;
		return (discr->d_1);
	}
	else if (discr->d_1 > 0.001f && discr->d_2 < 0)
		return (discr->d_1);
	else if (discr->d_1 < 0.001f && discr->d_2 > 0.001f)
		return (discr->d_2);
	return (NO_INTERSECT);
}
