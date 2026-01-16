/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:06:53 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/15 09:31:27 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	img_create(void *mlx, int width, int height)
{
	t_img	img;

	img.ptr = mlx_new_image(mlx, width, height);
	if (!img.ptr)
		return ((t_img){0});
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
	if (!img.addr)
	{
		mlx_destroy_image(mlx, img.ptr);
		return ((t_img){0});
	}
	img.width = width;
	img.height = height;
	return (img);
}

void	img_verline(t_img *img, int x, t_vec2i bt, t_color color)
{
	int	y;

	y = bt.x;
	while (y < bt.y)
	{
		img_pixel_put(img, x, y, color);
		y++;
	}
}

void	img_clear(t_img *img)
{
	int	x;

	x = 0;
	while (x < img->width)
	{
		img_verline(img, x, (t_vec2i){0, img->height}, (t_color){0});
		x++;
	}
}

void	img_pixel_put(t_img *img, int x, int y, t_color color)
{
	char	*pixel;
	int		i;
	int		icolor;

	if (!(x >= 0 && x < img->width))
		return ;
	if (!(y >= 0 && y < img->height))
		return ;
	icolor = (color.r << 16) | (color.g << 8) | color.b;
	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (icolor >> i) & 0xFF;
		else
			*pixel++ = (icolor >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	img_destroy(void *mlx, t_img *img)
{
	if (!(img && mlx))
		return ;
	if (img->ptr)
		mlx_destroy_image(mlx, img->ptr);
	*img = (t_img){0};
}
