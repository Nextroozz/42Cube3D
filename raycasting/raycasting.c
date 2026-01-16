/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:06:47 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/16 15:22:51 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

bool	walls_hit(t_state *st, t_vec2i pos)
{
	int	x;

	x = 0;
	while (x < st->map.wallcount)
	{
		if (st->map.walls[x].x == pos.x && st->map.walls[x].y == pos.y)
			return (true);
		x++;
	}
	return (false);
}

bool	raycast_rayhit(t_state *st, t_rcast_vars *arg)
{
	bool	hit;
	int		loop_count;

	hit = false;
	loop_count = 0;
	while (!hit && loop_count++ < RENDER_DISTANCE)
	{
		if (arg->side_dist.x < arg->side_dist.y)
		{
			arg->side_dist.x += arg->delta_dist.x;
			arg->map_pos.x += arg->step.x;
			arg->hitside = HITSIDE_EAST
				+ ((arg->step.x > 0) * (HITSIDE_WEST - HITSIDE_EAST));
		}
		else
		{
			arg->side_dist.y += arg->delta_dist.y;
			arg->map_pos.y += arg->step.y;
			arg->hitside = HITSIDE_NORTH
				+ ((arg->step.y > 0) * (HITSIDE_SOUTH - HITSIDE_NORTH));
		}
		hit = walls_hit(st, arg->map_pos);
	}
	return (hit);
}

void	raycast_ray_setup(t_state *st, t_rcast_vars *vars)
{
	if (vars->ray_dir.x)
		vars->delta_dist.x = absf64(1 / vars->ray_dir.x);
	if (vars->ray_dir.y)
		vars->delta_dist.y = absf64(1 / vars->ray_dir.y);
	vars->step = (t_vec2i){-1, -1};
	if (vars->ray_dir.x < 0)
		vars->side_dist.x
			= (st->map.player.pos.x - vars->map_pos.x) * vars->delta_dist.x;
	else
	{
		vars->step.x = 1;
		vars->side_dist.x
			= (vars->map_pos.x + 1 - st->map.player.pos.x) * vars->delta_dist.x;
	}
	if (vars->ray_dir.y < 0)
		vars->side_dist.y
			= (st->map.player.pos.y - vars->map_pos.y) * vars->delta_dist.y;
	else
	{
		vars->step.y = 1;
		vars->side_dist.y
			= (vars->map_pos.y + 1 - st->map.player.pos.y) * vars->delta_dist.y;
	}
}

void	raycast_render(t_state *st)
{
	t_rcast_vars	vars;

	vars = (t_rcast_vars){0};
	vars.dir = (t_vec2){cos(st->map.player.dir), sin(st->map.player.dir)};
	vars.x = 0;
	while (vars.x < WINDOW_WIDTH)
	{
		vars.camerax = 2 * vars.x / (double)(WINDOW_WIDTH) - 1;
		vars.ray_dir = (t_vec2){
			vars.dir.x + st->plane.x * vars.camerax,
			vars.dir.y + st->plane.y * vars.camerax
		};
		vars.map_pos = (t_vec2i){floor(st->map.player.pos.x),
			floor(st->map.player.pos.y)};
		vars.delta_dist = (t_vec2){INFINITY, INFINITY};
		raycast_ray_setup(st, &vars);
		if (!raycast_rayhit(st, &vars))
		{
			vars.x++;
			continue ;
		}
		raycast_draw(st, &vars);
		vars.x++;
	}
}
