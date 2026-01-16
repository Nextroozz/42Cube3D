/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:06:59 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/15 09:35:54 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../raycasting/raycasting.h"

void	cub3d_usage(char *progname)
{
	cub3d_error(NULL);
	write(STDERR_FILENO, "Usage: ", 7);
	write(STDERR_FILENO, progname, ft_strlen(progname));
	write(STDERR_FILENO, " map_path(.cub)\n", 16);
}

void	state_clean(t_state *state)
{
	int	i;

	i = 0;
	while (i < 4)
		img_destroy(state->mlx, &state->wall_texts[i++]);
	if (state->map.wallcount)
		map_destroy(&state->map);
	if (state->texture.ptr)
		img_destroy(state->mlx, &state->texture);
	if (state->window)
		mlx_destroy_window(state->mlx, state->window);
	if (state->mlx)
		mlx_destroy_display(state->mlx);
}

static bool	cub3d_setup(t_state *state)
{
	double	fov;

	fov = tan((FOV >> 1) * PI / 180.0);
	state->plane = (t_vec2){
		-sin(state->map.player.dir) * fov,
		cos(state->map.player.dir) * fov
	};
	if (!img_load_xpm(&state->wall_texts[WALL_NO], state->mlx,
			state->map.north_texture))
		return (false);
	if (!img_load_xpm(&state->wall_texts[WALL_WE], state->mlx,
			state->map.west_texture))
		return (false);
	if (!img_load_xpm(&state->wall_texts[WALL_SO], state->mlx,
			state->map.south_texture))
		return (false);
	if (!img_load_xpm(&state->wall_texts[WALL_EA], state->mlx,
			state->map.east_texture))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc != 2)
		return (cub3d_usage(argv[0]), 1);
	state = (t_state){0};
	state.mlx = mlx_init();
	if (!state.mlx)
		return (state_clean(&state), 1);
	state.window
		= mlx_new_window(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	if (!state.window)
		return (state_clean(&state), 1);
	state.texture = img_create(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!state.texture.ptr)
		return (state_clean(&state), 1);
	if (!map_create(&state.map, argv[1]))
		return (state_clean(&state), 1);
	if (!cub3d_setup(&state))
		return (state_clean(&state), 1);
	mlx_hook(state.window, MLX_EVENT_DESTROY, 0, cub3d_close, &state);
	mlx_hook(state.window, MLX_EVENT_KEYDOWN, 1L << 0, cub3d_keypress, &state);
	mlx_hook(state.window, MLX_EVENT_KEYUP, 1L << 1, cub3d_keyrelease, &state);
	mlx_loop_hook(state.mlx, cub3d_frame, &state);
	mlx_loop(state.mlx);
	return (state_clean(&state), 0);
}
