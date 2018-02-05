/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:35:14 by hdelanoe          #+#    #+#             */
/*   Updated: 2018/02/05 15:59:07 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	inputs2(int keycode, t_env *e)
{
	if (keycode == KEY_PAD_0)
		e->filter_flag = 0;
	else if (keycode == KEY_PAD_1)
		e->filter_flag = 1;
	else if (keycode == KEY_PAD_2)
		e->filter_flag = 2;
	else if (keycode == KEY_PAD_3)
		e->filter_flag = 3;
	else if (keycode == KEY_PAD_4)
		e->filter_flag = 4;
	else if (keycode == KEY_PAD_5)
		e->filter_flag = 5;
	else if (keycode == KEY_PAD_6)
		e->filter_flag = 6;
}

void	inputs_conditions(int keycode, t_env *e)
{
	if (keycode == KEY_D && (e->pixelize || e->edit_flag))
		e->move_x = 25;
	else if (keycode == KEY_E && (e->pixelize || e->edit_flag))
		e->move_y = -25;
	else if (keycode == KEY_W && (e->pixelize || e->edit_flag))
		e->move_z = 25;
	else if (keycode == KEY_S && (e->pixelize || e->edit_flag))
		e->move_z = -25;
	else if (keycode == KEY_UP && (e->pixelize || e->edit_flag))
		e->rotate_x = 1.5;
	else if (keycode == KEY_DOWN && (e->pixelize || e->edit_flag))
		e->rotate_x = -1.5;
	else if (keycode == KEY_LEFT && (e->pixelize || e->edit_flag))
		e->rotate_y = 1.5;
	else if (keycode == KEY_A && (e->pixelize || e->edit_flag))
		e->move_x = -25;
	else if (keycode == KEY_Q && (e->pixelize || e->edit_flag))
		e->move_y = 25;
	else if (keycode == KEY_RIGHT && (e->pixelize || e->edit_flag))
		e->rotate_y = -1.5;
	else if (keycode == KEY_Z && (e->pixelize || e->edit_flag))
		e->rotate_z = 1.5;
	else if (keycode == KEY_X && (e->pixelize || e->edit_flag))
		e->rotate_z = -1.5;
}

int		inputs(int keycode, t_env *e)
{
	inputs_conditions(keycode, e);
	if ((keycode == KEY_D || keycode == KEY_A || keycode == KEY_Q ||
	keycode == KEY_E || keycode == KEY_W || keycode == KEY_S ||
	keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT ||
	keycode == KEY_RIGHT || keycode == KEY_Z || keycode == KEY_X) &&
	!(e->pixelize || e->edit_flag))
	{
		mlx_string_put(e->mlx.mlx_ptr, e->mlx.win_ptr, 500, 50,
		0xFF0000, "Mouvement disable in render mode");
		return (0);
	}
	return (1);
}
