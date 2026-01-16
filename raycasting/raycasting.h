/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:06:51 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/16 15:02:38 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

typedef enum e_hitside
{
	HITSIDE_NORTH,
	HITSIDE_SOUTH,
	HITSIDE_EAST,
	HITSIDE_WEST,
}	t_hitside;

typedef struct s_rcast_vars
{
	t_vec2i		map_pos;
	t_vec2i		step;
	t_vec2		dir;
	double		camerax;
	t_vec2		ray_dir;
	t_vec2		side_dist;
	t_vec2		delta_dist;
	t_hitside	hitside;
	int			x;
	t_img		wall_texture;
	t_vec2		wall;
	t_vec2i		tex;
}	t_rcast_vars;

// raycasting_render.c
void	raycast_draw(t_state *st, t_rcast_vars *arg);

#endif
