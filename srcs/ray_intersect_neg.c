#include "rtv1.h"
#include <math.h>
#include <stdio.h>

int				sphere_neg(t_ray *ray)
{
	double a;
	double b;
	double c;

	a =   M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->dir), 0, 0)
		+ M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->dir), 1, 0)
		+ M_IJ(&(ray->dir), 2, 0) * M_IJ(&(ray->dir), 2, 0);
	b =   2 * M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ 2 * M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->start), 1, 0)
		+ 2 * M_IJ(&(ray->dir), 2, 0) * M_IJ(&(ray->start), 2, 0);
	c =   M_IJ(&(ray->start), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ M_IJ(&(ray->start), 1, 0) * M_IJ(&(ray->start), 1, 0)
		+ M_IJ(&(ray->start), 2, 0) * M_IJ(&(ray->start), 2, 0)
		- 1;
	ray->dist = solved(a,b,c,ray);
    return(0);
}

int				plane_neg(t_ray *ray)
{
	double		a;
	double		b;
	double		c;

	a = 0;
	b = M_IJ(&(ray->dir), 2, 0);
	c = M_IJ(&(ray->start), 2, 0);
	ray->dist = solved(a, b, c,ray);
    return(0);
}

int				cylinder_neg(t_ray *ray)
{
	double		a;
	double		b;
	double		c;

	a = M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->dir), 0, 0)
		+ M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->dir), 1, 0);
	b = 2 * M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ 2 * M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->start), 1, 0);
	c = M_IJ(&(ray->start), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ M_IJ(&(ray->start), 1, 0) * M_IJ(&(ray->start), 1, 0)
		- 1;
	ray->dist = solved(a, b, c,ray);
    return(0);
}

int				cone_neg(t_ray *ray)
{
	double		a;
	double		b;
	double		c;

	a = M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->dir), 0, 0)
		+ M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->dir), 1, 0)
		- M_IJ(&(ray->dir), 2, 0) * M_IJ(&(ray->dir), 2, 0);
	b = 2 * M_IJ(&(ray->dir), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ 2 * M_IJ(&(ray->dir), 1, 0) * M_IJ(&(ray->start), 1, 0)
		- 2 * M_IJ(&(ray->dir), 2, 0) * M_IJ(&(ray->start), 2, 0);
	c = M_IJ(&(ray->start), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ M_IJ(&(ray->start), 1, 0) * M_IJ(&(ray->start), 1, 0)
		- M_IJ(&(ray->start), 2, 0) * M_IJ(&(ray->start), 2, 0);
	ray->dist = solve_2_degree(a, b, c);
    return(0);
}
