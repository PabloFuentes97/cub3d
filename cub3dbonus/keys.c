/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:11:41 by pfuentes          #+#    #+#             */
/*   Updated: 2023/09/06 09:46:02 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_funcs(t_cub3d *cub3d)
{
	if (cub3d->keys[0] == 1)
		move_player_pos_aux(cub3d->player, 1, cub3d->player->dir, cub3d);
	else if (cub3d->keys[1] == 1)
		move_player_pos_aux(cub3d->player, -1, cub3d->player->dir, cub3d);
	else if (cub3d->keys[2] == 1)
		move_player_pos_aux(cub3d->player, -1, cub3d->player->plane, cub3d);
	else if (cub3d->keys[3] == 1)
		move_player_pos_aux(cub3d->player, 1, cub3d->player->plane, cub3d);
	if (cub3d->keys[4] == 1)
		move_player_angle(cub3d->player, -1);
	else if (cub3d->keys[5] == 1)
		move_player_angle(cub3d->player, 1);
	render_frame(cub3d);
}

int	press_key(int key, t_cub3d *cub3d)
{
	printf("Key: %d\n", key);
	if (key == MOVE_UP)
		cub3d->keys[0] = 1;
	else if (key == MOVE_DOWN)
		cub3d->keys[1] = 1;
	else if (key == MOVE_LEFT)
		cub3d->keys[2] = 1;
	else if (key == MOVE_RIGHT)
		cub3d->keys[3] = 1;
	if (key == ROT_LEFT)
		cub3d->keys[4] = 1;
	else if (key == ROT_RIGHT)
		cub3d->keys[5] = 1;
	if (key == ESC)
		close_window(cub3d);
	return (0);
}

int	release_key(int key, t_cub3d *cub3d)
{
	if (key == MOVE_UP)
		cub3d->keys[0] = 0;
	else if (key == MOVE_DOWN)
		cub3d->keys[1] = 0;
	else if (key == MOVE_LEFT)
		cub3d->keys[2] = 0;
	else if (key == MOVE_RIGHT)
		cub3d->keys[3] = 0;
	if (key == ROT_LEFT)
		cub3d->keys[4] = 0;
	else if (key == ROT_RIGHT)
		cub3d->keys[5] = 0;
	if (key == ESC)
		close_window(cub3d);
	return (0);
}

int	close_window(t_cub3d *cub3d)
{
	free_cub3d(cub3d, 0, 4);
	exit(0);
	return (0);
}

void	waiting_events(t_cub3d *cub3d)
{
	mlx_hook(cub3d->win, 2, 1L << 0, &press_key, cub3d);
	mlx_hook(cub3d->win, 3, 1L << 1, &release_key, cub3d);
	mlx_hook(cub3d->win, 17, 0, close_window, cub3d);
}
