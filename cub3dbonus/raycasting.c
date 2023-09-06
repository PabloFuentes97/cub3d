/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuentes <pfuentes@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:27:59 by pserrano          #+#    #+#             */
/*   Updated: 2023/09/06 12:08:37 by pfuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_ray_line(t_raycaster *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = rc->ray_len.x - rc->step_incr.x;
	else
		rc->perp_wall_dist = rc->ray_len.y - rc->step_incr.y;
	rc->line_height = (int)(WINDOW_Y / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + WINDOW_Y / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + WINDOW_Y / 2;
	if (rc->draw_end >= WINDOW_Y)
		rc->draw_end = WINDOW_Y - 1;
	//draw_line_dda(cub3d, x, rc->draw_start, x, rc->draw_end);
}

static int	ray_inside_door(t_cub3d *cub3d, t_raycaster *rc)
{
	t_door		*door;

	door = find_door(cub3d->doors, rc->map_pos.x, rc->map_pos.y);
	calculate_ray_line(rc);
	calculate_wall_x(rc);
	if (rc->wall_x < door->border)
	{
		//if (rc->ray_dir.x < 0 || rc->ray_dir.y < 0)
		rc->wall_x += 1 - door->border;
		if (door->view == 0)
			door->view = 1;
		return (1);
	}
	rc->impact_type = '0';
	return (0);
}

static int	ray_inside_cell(t_cub3d *cub3d, t_raycaster *rc, char **map)
{
	char	c;

	if ((rc->map_pos.x >= 0 && rc->map_pos.x < rc->map_len.x)
		&& (rc->map_pos.y >= 0 && rc->map_pos.y < rc->map_len.y))
	{
		c = map[rc->map_pos.y][rc->map_pos.x];
		rc->impact_type = c;
		if (c == '1')
			return (1);
		else if (c == 'D')
			return (ray_inside_door(cub3d, rc));
	}
	return (0);
}

static int	calculate_ray(t_cub3d *cub3d, t_raycaster *rc, char **map)
{
	double	distance;

	distance = 0;
	while (distance < RAY_MAX_DISTANCE)
	{
		if (rc->ray_len.x < rc->ray_len.y)
		{
			rc->map_pos.x += rc->step_dir.x;
			distance = rc->ray_len.x;
			rc->ray_len.x += rc->step_incr.x;
			rc->side = 0;
		}
		else
		{
			rc->map_pos.y += rc->step_dir.y;
			distance = rc->ray_len.y;
			rc->ray_len.y += rc->step_incr.y;
			rc->side = 1;
		}
		if (ray_inside_cell(cub3d, rc, map))
			return (1);
	}
	return (0);
}

void	cast_ray(t_cub3d *cub3d, int x)
{
	t_raycaster	ray;

	ray = init_ray(cub3d, x);
	if (!calculate_ray(cub3d, &ray, cub3d->map))
		return ;
	if (ray.impact_type != 'D')
		calculate_ray_line(&ray);
	//draw_line_dda(cub3d, x, ray.draw_start, x, ray.draw_end);
	calculate_texture_pixel(cub3d, &ray, x);
}

void	raycaster(t_cub3d *cub3d)
{
	int			x;

	x = 0;
	while (x < WINDOW_X)
	{
		cast_ray(cub3d, x);
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win,
		cub3d->buffer.img_ptr, 0, 0);
}
