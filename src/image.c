#include "cub3d.h"

void	img_pixel_put(t_img *img, int x, int y, t_color color)
{
	char	*pixel;
	int		i;
	int		icolor;

	icolor = (color.r << 16) | (color.g << 8) | color.b;
	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0) {
		if (img->endian != 0)
			*pixel++ = (icolor >> i) & 0xFF;
		else
			*pixel++ = (icolor >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
