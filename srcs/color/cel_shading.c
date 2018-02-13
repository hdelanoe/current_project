/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cel_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 20:12:37 by dguy-caz          #+#    #+#             */
/*   Updated: 2018/02/05 15:25:38 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		cel_shading(t_vector *light, t_env *e, t_color *clr)
{
	t_color		new;
	double		intens;
	t_vector	nrm;

	new = set_color(0, 0, 0);
	nrm = normalize(&e->current_node_normal);
	if (e->intersect)
		intens = -(dot_product(light, &nrm));
	else
		return (set_color(0, 0, 0));
	if (intens < 0.2)
		intens = 0.1;
	else if (intens >= 0.2 && intens < 0.6)
		intens = 0.3;
	else if (intens >= 0.6)
		intens = 0.7;
	else
		return (set_color(0, 0, 0));
	new = set_color(intens, intens, intens);
	return (c_c_add(&new, clr));
}

t_color		cel_shade_color(t_env *e)
{
	t_color		c;
	t_color		c_light;
	t_rayon		ray;
	t_light		*tmp_light;

	ray.origin = e->current_origin;
	ray.rayon = e->current_rayon;
	ray.node = e->current_node;
	ray.normal = e->current_node_normal;
	tmp_light = e->light;
	c = e->current_color;
	while (tmp_light)
	{
		tmp_light->rayon = v_v_subs(&e->current_node, &tmp_light->origin);
		tmp_light->rayon = normalize(&tmp_light->rayon);
		e->current_origin = tmp_light->origin;
		e->current_rayon = tmp_light->rayon;
		c_light = light_intersection(e, tmp_light);
		c = cel_shading(&tmp_light->rayon, e, &c);
		tmp_light = tmp_light->next;
	}
	return (c);
}
