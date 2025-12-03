#include "raycasting.h"
#include <mlx.h>

void	raycast_render(t_state *state)
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			img_pixel_put(&state->texture, i, j, (t_color){255, 255, 255});
		}
	}
}
