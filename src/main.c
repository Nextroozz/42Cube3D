#include "cub3d.h"
#include "../raycasting/raycasting.h"
#include <stdio.h>
#include <mlx.h>

int	state_clean(t_state *state)
{
	if (state->texture.ptr)
		mlx_destroy_image(state->mlx, state->texture.ptr);
	if (state->window)
		mlx_destroy_window(state->mlx, state->window);
#ifdef _LINUX_
	if (state->mlx)
		mlx_destroy_display(state->mlx);
#endif
	return (1);
}

int	cub3d_frame(t_state *state)
{
	raycast_render(state);
	mlx_put_image_to_window(state->mlx, state->window, state->texture.ptr, 0, 0);
	return (0);
}

int	cub3d_close(t_state *state)
{
#ifdef _LINUX_
	mlx_loop_end(state->mlx);
#else
	mlx_destroy_window(state->mlx, state->window);
	state->window = NULL;
#endif
	return (0);
}

int main()
{
	t_state	state;

	state = (t_state){0};
	state.mlx = mlx_init();
	if (!state.mlx)
		return (state_clean(&state));
	state.window = mlx_new_window(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	if (!state.window)
		return (state_clean(&state));
	state.texture.ptr = mlx_new_image(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!state.texture.ptr)
		return (state_clean(&state));
	state.texture.addr = mlx_get_data_addr(state.texture.ptr, &state.texture.bpp, &state.texture.line_len, &state.texture.endian);
	mlx_hook(state.window, MLX_EVENT_DESTROY, 0, cub3d_close, &state);
	mlx_loop_hook(state.mlx, cub3d_frame, &state);
	mlx_loop(state.mlx);
	state_clean(&state);
	return (0);
}
