/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:24:51 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/16 15:24:08 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	raycast_render_texsetup(t_state *st,
	t_rcast_vars *arg, double perp_wall_dist)
{
	if (arg->hitside == HITSIDE_NORTH)
		arg->wall_texture = st->wall_texts[WALL_NO];
	else if (arg->hitside == HITSIDE_WEST)
		arg->wall_texture = st->wall_texts[WALL_WE];
	else if (arg->hitside == HITSIDE_SOUTH)
		arg->wall_texture = st->wall_texts[WALL_SO];
	else
		arg->wall_texture = st->wall_texts[WALL_EA];
	if (arg->hitside == HITSIDE_EAST || arg->hitside == HITSIDE_WEST)
		arg->wall.x = st->map.player.pos.y + perp_wall_dist * arg->ray_dir.y;
	else
		arg->wall.x = st->map.player.pos.x + perp_wall_dist * arg->ray_dir.x;
	arg->wall.x -= floor(arg->wall.x);
	arg->tex.x = clampi32(arg->wall.x * (double)arg->wall_texture.width,
			0, arg->wall_texture.width - 1);
	if ((arg->hitside == HITSIDE_WEST || arg->hitside == HITSIDE_EAST))
	{
		if (arg->ray_dir.x > 0)
			arg->tex.x = arg->wall_texture.width - arg->tex.x - 1;
	}
	else
		if (arg->ray_dir.y < 0)
			arg->tex.x = arg->wall_texture.width - arg->tex.x - 1;
}

void	raycast_draw(t_state *st, t_rcast_vars *arg)
{
	double		perp_wall_dist;
	int			line_height;
	t_vec2i		draw;
	double		step;
	double		tex_pos;

	if (arg->hitside == HITSIDE_EAST || arg->hitside == HITSIDE_WEST)
		perp_wall_dist = arg->side_dist.x - arg->delta_dist.x;
	else
		perp_wall_dist = arg->side_dist.y - arg->delta_dist.y;
	line_height = WINDOW_HEIGHT / perp_wall_dist;
	draw.x = maxi32(-line_height / 2 + WINDOW_HEIGHT / 2, 0);
	draw.y = mini32(line_height / 2 + WINDOW_HEIGHT / 2, WINDOW_HEIGHT - 1);
	raycast_render_texsetup(st, arg, perp_wall_dist);
	step = (double)arg->wall_texture.height / (double)line_height;
	tex_pos = (draw.x - WINDOW_HEIGHT / 2 + line_height / 2) * step;
	while (draw.x < draw.y)
	{
		arg->tex.y = (int)tex_pos;
		tex_pos += step;
		if (arg->tex.y >= 0 && arg->tex.y < arg->wall_texture.height)
			img_pixel_put(&st->texture, arg->x, draw.x, img_color_get(
					&arg->wall_texture, arg->tex.x, arg->tex.y));
		draw.x++;
	}
}
