/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 13:07:43 by igomez            #+#    #+#             */
/*   Updated: 2016/06/20 19:24:33 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>
#include <stdio.h>

static int		ray_solution_cylinder(t_ray *ray, t_obj *obj)
{
	int		sign;

	ray->obj = obj;
	ray->intersection = M_POINT(
		M_IJ(&(ray->start), 0, 0) + ray->dist * M_IJ(&(ray->dir), 0, 0),
		M_IJ(&(ray->start), 1, 0) + ray->dist * M_IJ(&(ray->dir), 1, 0),
		M_IJ(&(ray->start), 2, 0) + ray->dist * M_IJ(&(ray->dir), 2, 0));
	if ((M_IJ(&(ray->start), 0, 0) * M_IJ(&(ray->start), 0, 0)
		+ M_IJ(&(ray->start), 1, 0) * M_IJ(&(ray->start), 1, 0))
		> 1)
		sign = 1;
	else
		sign = -1;
	ray->normal = M_DIR(
		sign * M_IJ(&(ray->intersection), 0, 0),
		sign * M_IJ(&(ray->intersection), 1, 0),
		0);
	return (0);
}

double		solve_2_degree_neg(double a, double b, double c, t_ray *ray)
{
	double		tmp;
	double		res;

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
		double front = (-b - tmp) / (2 * a);
		double back = (-b + tmp) / (2 * a);

			t_neg *neg;

			neg = ray->neg;
			while(neg)
			{
				ray->front = neg->front;
				ray->back = neg->back;
			if(front >= ray->front && front <= ray->back)
				{
					if(back >= ray->front && back <= ray->back)
						return(-1);
					return(back);
				}
				if(front < 0)
				{
					if(back >= ray->front && back < ray->back)
						return(-1);
				}
				neg = neg->next;
			}
		res = (-b - tmp) / (2 * a);
		if (res < 0)
			res = (-b + tmp) / (2 * a);
	}
	return (res);
}

int				ray_intersect_cylinder(t_ray *ray, t_obj *obj)
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
	ray->dist = solve_2_degree_neg(a, b, c,ray);
	if (ray->dist > 0)
		ray_solution_cylinder(ray, obj);
	return (0);
}
