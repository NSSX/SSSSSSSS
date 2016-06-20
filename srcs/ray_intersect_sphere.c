/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 13:07:43 by igomez            #+#    #+#             */
/*   Updated: 2016/06/20 19:23:04 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

static int		ray_solution_sphere(t_ray *ray, t_obj *obj)
{
	int sign;

	ray->obj = obj;
	ray->intersection = M_POINT(
		M_IJ(&(ray->start), 0, 0) + ray->dist * M_IJ(&(ray->dir), 0, 0),
		M_IJ(&(ray->start), 1, 0) + ray->dist * M_IJ(&(ray->dir), 1, 0),
		M_IJ(&(ray->start), 2, 0) + ray->dist * M_IJ(&(ray->dir), 2, 0));
	if (mat_norm(&(ray->start)) > 1)
		sign = 1;
	else
		sign = -1;
	ray->normal = M_DIR(
		sign * M_IJ(&(ray->intersection), 0, 0),
		sign * M_IJ(&(ray->intersection), 1, 0),
		sign * M_IJ(&(ray->intersection), 2, 0));
	return (0);
}

double		solved(double a, double b, double c, t_ray *ray)
{
	double		tmp;
	double		res;

	ray->front = 10000;
	ray->back = 10000;
	if (fabs(a) < ERROR)
	{
		if (fabs(b) < ERROR)
			return (-1);
		res = -c / b;
	}
	else
	{
		tmp = b * b - 4 * a * c;
		if (tmp < 0)
			return (-1);
		tmp = sqrt(tmp);
		ray->front = (-b - tmp) / (2 * a);
		ray->back = (-b + tmp) / (2 * a);
		res = (-b - tmp) / (2 * a);
		if (res < 0)
			res = (-b + tmp) / (2 * a);
	}
	return (res);
}

int				ray_intersect_sphere(t_ray *ray, t_obj *obj)
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
//	ray->dist = solved(a,b,c,ray);
	ray->dist = solve_2_degree_neg(a, b, c,ray);
	if (ray->dist > 0)
		ray_solution_sphere(ray, obj);
	return (0);
}
