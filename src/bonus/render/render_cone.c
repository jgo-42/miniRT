/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:14:58 by sanghwal          #+#    #+#             */
/*   Updated: 2023/06/22 20:14:54 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "defs.h"
#include "render.h"

static inline void	get_cone_coeff(t_cone *cone, t_ray *ray, double *coeff)
{
	// Vector CH represents the axis of the cone
	const t_vec3 CH = vec3_minus(cone->center_point, cone->normal_vec3);
	// Compute m = (r^2) / (CH^2)
	const double m = (cone->radius * cone->radius) / vec3_square_length(CH);
	// Compute vector w = L0 - H
	const t_vec3 w = vec3_minus(ray->origin, cone->center_point);

	coeff[A] = vec3_inner_product(ray->direction, ray->direction) - (m + 1) * pow(vec3_inner_product(ray->direction, cone->normal_vec3), 2);
	coeff[B] = 2 * (vec3_inner_product(ray->direction, w) - (m + 1) * vec3_inner_product(ray->direction, cone->normal_vec3) * vec3_inner_product(w, cone->normal_vec3));
	coeff[C] = vec3_inner_product(w, w) - (m + 1) * pow(vec3_inner_product(w, cone->normal_vec3), 2);
}

static double	get_infinite_cone(t_cone *cone, t_ray *ray)
{
	double			coeff[3];
	double			root[2];

	get_cone_coeff(cone, ray, coeff);
	// Compute the roots of the quadratic equation
	if (!root_formula(coeff[A], coeff[B], coeff[C], root))
		return (0);
	// Return the smallest positive root if it lies on the cone
	for (int i = 0; i < 2; i++) {
		if (root[i] > 0) {
			t_vec3 intersection_point = vec3_plus(ray->origin, vec3_scalar_multi(ray->direction, root[i]));
			double projection = vec3_inner_product(vec3_minus(intersection_point, cone->center_point), cone->normal_vec3);
			if (0 <= projection && projection <= vec3_length(vec3_minus(cone->center_point, cone->normal_vec3)))
				return (root[i]);
		}
	}
	return (0);
}

static bool	is_valid_bottom(double t, t_cone *cone, t_ray *ray)
{
	t_vec3	cap_center;
	t_vec3	t_to_q;
	double	dot;
	double	len;

	cap_center = (cone->center_point);
	t_to_q = vec3_minus(ray_at(ray, t), cap_center);
	dot = vec3_inner_product(t_to_q, cone->normal_vec3);
	len = vec3_length(vec3_minus(cap_center, ray_at(ray, t)));
	if (fabs(dot) < EPSILON && len >= 0 && len <= cone->radius)
		return (true);
	return (false);
}

static double get_bottom_cone(t_cone *cone, t_ray *ray)
{
	t_vec3 cone_top = vec3_plus(cone->center_point, vec3_scalar_multi(cone->normal_vec3, cone->height));
	
	double bottom_t;
	
	bottom_t = vec3_inner_product(
		vec3_minus(cone_top, ray->origin),
		vec3_scalar_multi(cone->normal_vec3, -1)
	) / vec3_inner_product(ray->direction, vec3_scalar_multi(cone->normal_vec3, -1));
	
	if (!is_valid_bottom(bottom_t, cone, ray))
		return (0);
	
	return (bottom_t);
}




double	get_cone_dist(t_obj *obj, const t_ray *ray)
{
	t_cone	cone;
	double	infi_t;
	double	bottom_t;

	cone = obj->content.cone;
	infi_t = get_infinite_cone(&cone, (t_ray *)ray);
	bottom_t = get_bottom_cone(&cone, (t_ray *)ray);

	if ((infi_t > 0 && bottom_t <= 0)
		|| (infi_t > 0 && bottom_t > 0 && infi_t <= bottom_t))
		return (infi_t);
	else if (bottom_t > 0)
	{
		printf("retturn bottom\n");
		return (bottom_t);
	}
	return (0);
}


void	_get_side_normal_vec3(t_cone cone, t_record *record)
{
	t_vec3 PC = vec3_minus(record->point, cone.center_point);
	double cos_a = cone.radius / sqrt(cone.radius*cone.radius + cone.height*cone.height);
	t_vec3 n = vec3_minus(PC, vec3_scalar_multi(cone.normal_vec3, cos_a * vec3_inner_product(PC, cone.normal_vec3) + sqrt(1 - cos_a*cos_a) * sqrt(vec3_inner_product(PC, PC) - vec3_inner_product(PC, cone.normal_vec3) * vec3_inner_product(PC, cone.normal_vec3))));
	double length = sqrt(vec3_inner_product(n, n));
	record->normal_vec3 = vec3_scalar_multi(n, 1 / length); // normalize the vector
}

t_object_type	get_cone_record(t_obj *obj, t_ray *ray, t_record *record)
{
	const t_cone	cone = obj->content.cone;

	record->obj = obj;
	record->point = ray_at(ray, record->t);
	if (cone.co_type == SIDE)
		_get_side_normal_vec3(cone, record);
	if (cone.co_type == BASE)
		record->normal_vec3 = vec3_scalar_multi(cone.normal_vec3, -1);
	set_face_normal(ray, record);
	record->rgba = cone.rgba;
	return (obj->type);
}
