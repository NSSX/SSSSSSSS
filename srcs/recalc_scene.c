/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalc_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez <igomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 17:48:56 by igomez            #+#    #+#             */
/*   Updated: 2016/06/20 14:26:55 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct                                          s_vec3d
{
        double x;
        double y;
        double z;
}                                                       t_vec3d;

double          dot_product(t_vec3d *a, t_vec3d *b)
{
        return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

void           normalize(t_vec3d *vec)
{
        double n;

        n = 1.0 / sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
        vec->x *= n;
        vec->y *= n;
        vec->z *= n;
}

t_vec3d  ft_reflex(t_vec3d *incident, t_vec3d *n)
{
  t_vec3d  v;

  v.x = incident->x - 2 * dot_product(n, incident) * n->x;
  v.y = incident->y - 2 * dot_product(n, incident) * n->y;
  v.z = incident->z - 2 * dot_product(n, incident) * n->z;
  return (v);
}

t_vec3d   refract(t_vec3d *ray_dir, t_vec3d *normal)//t_vec3d *ray, t_vec3d *normal)
{
  double  n;
  double  cosi;
  double  sint2;
  double  cost;
  t_vec3d   result;
  double n1 = 1;//no idea;
  double n2 = 1.05;//no idea;//1 = toute la sphere

  n = n1 / n2;
  cosi = -1 * dot_product(normal, ray_dir);
  sint2 = n * n * (1.0 - cosi * cosi);
   if (sint2 > 1.0)
     return(*ray_dir);
   cost = sqrt(1.0 - sint2);
   result.x = n * ray_dir->x + (n * cosi - cost) * normal->x;
   result.y = n * ray_dir->y + (n * cosi - cost) * normal->y;
   result.z = n * ray_dir->z + (n * cosi - cost) * normal->z;
   return(result);
}

int give_color(t_ray *ray, t_env *e)
{
	int color;

	ray_intersect(ray, e);
	color = ray_color(ray, e);

    /*if(ray->obj && ray->obj->param.type == SPHERE && e->in_refraction == 0)
    {
        t_vec3d ray_dir;
        t_vec3d normal;

        e->in_refraction = 1;
        normal = (t_vec3d){M_IJ(&(ray->normal), 0, 0),
            M_IJ(&(ray->normal), 1, 0),
        M_IJ(&(ray->normal), 2, 0)};
        ray_dir = (t_vec3d){M_IJ(&(ray->dir), 0, 0),
            M_IJ(&(ray->dir), 1, 0),
            M_IJ(&(ray->dir), 2, 0)};
        ray_dir = refract(&ray_dir, &normal);
        normalize(&ray_dir);
        M_IJ(&(ray->dir), 0, 0) = ray_dir.x;
        M_IJ(&(ray->dir), 1, 0) = ray_dir.y;
        M_IJ(&(ray->dir), 2, 0) = ray_dir.z;
        color = color_scale(color, 0.8);
        int color_tmp = give_color(ray,e);
        color_tmp = color_scale(color_tmp, 0.5);
        color = color_add(color, color_tmp);
    }*/
/*	if(e->nb_reflexion < 1 && ray->obj && ray->obj->param.type == PLANE)
	{

		e->nb_reflexion++;
		t_vec3d reflex;
		t_vec3d incident;
		t_vec3d normal;
		t_vec3d intersection;

//                Declaration
            intersection =  (t_vec3d){M_IJ(&(ray->intersection), 0, 0),
            M_IJ(&(ray->intersection), 1, 0),
            M_IJ(&(ray->intersection), 2, 0)};
			incident = (t_vec3d){M_IJ(&(ray->dir), 0, 0),
                M_IJ(&(ray->dir), 1, 0),
                M_IJ(&(ray->dir), 2, 0)};
            normal = (t_vec3d){M_IJ(&(ray->normal), 0, 0),
				M_IJ(&(ray->normal), 1, 0),
			M_IJ(&(ray->normal), 2, 0)};

            //Calcul reflex;
            reflex = ft_reflex(&incident, &normal);
			normalize(&reflex);

            normal.x *= 0.001;
			normal.y *= 0.001;
			normal.z *= 0.001;
			intersection.x += normal.x;
			intersection.y += normal.y;
			intersection.z += normal.z;

            M_IJ(&(ray->start), 0, 0) = intersection.x;
			M_IJ(&(ray->start), 1, 0) = intersection.y;
			M_IJ(&(ray->start), 2, 0) = intersection.z;
			M_IJ(&(ray->dir), 0, 0) = reflex.x;
			M_IJ(&(ray->dir), 1, 0) = reflex.y;
			M_IJ(&(ray->dir), 2, 0) = reflex.z;

            color = color_scale(color, 0.2);
            int color_tmp = give_color(ray,e);
            color_tmp = color_scale(color_tmp, 1 - 0.2);
            color = color_add(color, color_tmp);
        }*/
	return (color);
}

int		recalc_scene(t_env *e)
{
	int		x;
	int		y;
	t_ray	ray;

	e->c_old = clock();
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			e->nb_reflexion = 0;
            e->in_refraction = 0;
			ray.start = M_POINT(0, 0, 0);
			ray.dir = M_DIR(DIST_TO_PROJ,
							WIN_WIDTH / 2 - x,
							WIN_HEIGHT / 2 - y);
			mat_normalize(&(ray.dir));
			ray_setup_camera(&ray, &(e->scene->cam));
			ft_draw_pix(TPIX(x, y, give_color(&ray,e)), e->screen);
		}
	}
	e->c_new = clock();
	return (0);
}
