/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:07:18 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/15 16:06:43 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_floor_ceiling_col(t_state *state)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		img_verline(&state->texture, x,
			(t_vec2i){0, WINDOW_HEIGHT / 2},
			state->map.ceiling_color);
		img_verline(&state->texture, x,
			(t_vec2i){WINDOW_HEIGHT / 2, WINDOW_HEIGHT - 1},
			state->map.floor_color);
		x++;
	}
}

int	cub3d_frame(t_state *state)
{
	static uint64_t	last;
	uint64_t		now;

	if (state->should_close)
		return (cub3d_close(state), 0);
	if (!state->window)
		return (0);
	now = time_now();
	state->frame_s = (now - last) / 1000000.0;
	last = now;
	mlx_clear_window(state->mlx, state->window);
	img_clear(&state->texture);
	render_floor_ceiling_col(state);
	raycast_render(state);
	mlx_put_image_to_window(
		state->mlx, state->window, state->texture.ptr, 0, 0);
	handle_fb_movement(state);
	handle_lr_movement(state);
	handle_tlr_movement(state);
	return (0);
}
