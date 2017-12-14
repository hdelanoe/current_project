/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:59:31 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/11/28 11:59:34 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void debug_cylinder(t_object *tmp)
{
	printf("CYLINDER:\n");
	printf("center:  x->%f\n", tmp->center.x);
	printf("         y->%f\n", tmp->center.y);
	printf("         z->%f\n", tmp->center.z);
	printf("axis :   x->%f\n", tmp->axis.x);
	printf("         y->%f\n", tmp->axis.y);
	printf("         z->%f\n", tmp->axis.z);
	printf("radius ->%f\n", tmp->radius);
	printf("length ->%f\n", tmp->lenght_max);
	printf("colors : r->%f\n", tmp->color.r);
	printf("         g->%f\n", tmp->color.g);
	printf("         b->%f\n", tmp->color.b);
}

void		create_cylinder(t_env *e, t_json *json)
{
	t_object	*cylinder;

	while (json->member)
	{
		cylinder = (t_object*)ft_memalloc(sizeof(t_object));
		cylinder->id = ft_atoi(json->member->name);
		while (json->member->member)
		{
			if (ft_strcmp(json->member->member->name, "coord") == 0)
				cylinder->center = parse_point(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "normal") == 0)
				cylinder->axis = parse_normal(json->member->member->member);
			if (ft_strcmp(json->member->member->name, "radius") == 0)
				cylinder->radius = ft_atod(json->member->member->content);
			if (ft_strcmp(json->member->member->name, "length") == 0)
				cylinder->lenght_max = ft_atod(json->member->member->content);
			if (ft_strcmp(json->member->member->name, "colors") == 0)
				cylinder->color = parse_color(json->member->member->member);
			json->member->member = json->member->member->next;
		}
		debug_cylinder(cylinder);
		cylinder->type = ft_strdup("cylinder");
		add_new_object(&e->object, cylinder);
		json->member = json->member->next;
	}
}

int		cylinder_intersection(t_env *e, t_object *cylinder)
{
	t_poly	p;
	t_inter	i;

	i.object_rayon = v_v_subs(&e->current_origin, &cylinder->center);
	p.a = 1 - (dot_product(&e->current_rayon, &cylinder->axis) * dot_product(&e->current_rayon, &cylinder->axis));
	p.b = 2 * (dot_product(&i.object_rayon, &e->current_rayon) - (dot_product(&e->current_rayon, &cylinder->axis) * dot_product(&i.object_rayon, &cylinder->axis)));
	p.c = dot_product(&i.object_rayon, &i.object_rayon) - (dot_product(&i.object_rayon, &cylinder->axis) * dot_product(&i.object_rayon, &cylinder->axis)) - (cylinder->radius * cylinder->radius);
	p.discriminant = (p.b * p.b) - (4 * p.a * p.c);
//	poly_2nd_degree(d, &p, &i, cylinder);
	if (p.discriminant < 0)
		return (0);
	else
	{
		if (p.discriminant == 0)
			e->solution = - (p.b / (2 * p.a));
		else
		{
			p.discriminant = sqrt(p.discriminant);
			p.s1 = (- p.b + p.discriminant) / (2 * p.a);
			p.s2 = (- p.b - p.discriminant) / (2 * p.a);
			e->solution = (p.s1 < p.s2) ? p.s1 : p.s2;
		}
		i.tmp_node = v_double_mult(&e->current_rayon, e->solution);
		cylinder->node = v_v_add(&e->current_origin, &i.tmp_node);

		p.tmp1 = (dot_product(&e->current_rayon, &cylinder->axis) * e->solution) + dot_product(&i.object_rayon, &cylinder->axis);
		if (p.tmp1 > cylinder->lenght_max || p.tmp1 < 0)
			return (0);
		i.tmp_node_normal1 = v_v_subs(&cylinder->node, &cylinder->center);
		i.tmp_node_normal2 = v_double_mult(&cylinder->axis, p.tmp1);
		cylinder->node_normal = v_v_subs(&i.tmp_node_normal1, &i.tmp_node_normal2);
		cylinder->node_normal = normalize(&cylinder->node_normal);
	}
		return (1);
}

