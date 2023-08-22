/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserrano <pserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:58:03 by pserrano          #+#    #+#             */
/*   Updated: 2023/08/22 14:25:30 by pserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	xpm_to_img(t_cub3d *cub3d, char *path)
{
	t_img	img;

	printf("Path: %s$\n", path);
	img.img_ptr = mlx_xpm_file_to_image(cub3d->mlx_ptr, path,
			&img.img_w, &img.img_h);
	if (!img.img_ptr)
	{
		printf("Mal img ptr\n");
		free(img.img_ptr);
		//exit(EXIT_FAILURE);
	}
	else
		img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp,
				&img.size_l, &img.endian);
	printf("Bien\n");
	return (img);
}

t_img	set_texture(t_cub3d *cub3d, char	*data)
{
	t_img	texture;
	int		space_start;
	char	*file;

	space_start = move_to_char(data, ' ', 0);
	file = ft_strtrim(&data[space_start], " ");
	texture = xpm_to_img(cub3d, file);
	free(file);
	return (texture);
}

static int	calculate_tex_x(t_img *texture, t_raycaster *rc)
{
	int		tex_x;
	double	wallx; //coordenada x o y exacta donde impactó el rayo

	tex_x = 0;
	if (rc->side == 0)
		wallx = rc->origin.y + rc->perp_wall_dist * rc->ray_dir.y;
	else
		wallx = rc->origin.x + rc->perp_wall_dist * rc->ray_dir.x;
	wallx -= floor((wallx));
	if ((rc->side == 0 && rc->ray_dir.x > 0)
		&& (rc->side == 1 && rc->ray_dir.y < 0))
		tex_x = texture->img_w - tex_x - 1;
	else
		tex_x = (int)(wallx * (double)(texture->img_w));
	return (tex_x);
}

static t_img	select_texture(t_cub3d *cub3d,t_player *player, t_raycaster *rc)
{
	t_img	texture;
	double	pos_diff_x;
	double	pos_diff_y;

	pos_diff_x = rc->map_pos.x - player->pos.x;
	pos_diff_y = rc->map_pos.y - player->pos.y;
	texture = cub3d->textures[3]; // textura oeste
	if (pos_diff_y < 0 && rc->side == 1) // textura sur
		texture = cub3d->textures[1];
	else if (pos_diff_y > 0 && rc->side == 1) // textura norte
		texture = cub3d->textures[0];	
	else if (pos_diff_x > 0 && rc->side == 0) // textura este
		texture = cub3d->textures[2];
	return (texture);
}

void	calculate_texture_pixel(t_cub3d *cub3d, t_raycaster *rc, int x)
{
	t_vector	tex;
	double		tex_pos;
	t_img		texture;
	double		step;
	int			y;

	texture = select_texture(cub3d, cub3d->player, rc);
	tex.x = calculate_tex_x(&texture, rc);
	step = 1.0 * texture.img_h / rc->line_height;
	tex_pos = (rc->draw_start - WINDOW_Y / 2 + rc->line_height / 2) * step;
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		tex.y = (int)tex_pos & (texture.img_h - 1);
		tex_pos += step;
		cub3d->buffer.data[(y * WINDOW_X) + x]
			= texture.data[texture.img_h * tex.y + tex.x];
		if (rc->side == 1)
			cub3d->buffer.data[(y * WINDOW_X) + x]
				= (cub3d->buffer.data[(y * WINDOW_X) + x] >> 1) & 8355711;
		y++;
	}
}
