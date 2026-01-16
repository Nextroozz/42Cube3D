/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 09:23:37 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/16 13:41:48 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	img_load_err(const char *path)
{
	write(STDERR_FILENO, "Failed to load ", 15);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, "\n", 1);
}

bool	img_load_xpm(t_img *img, void *mlx, const char *path)
{
	if (!(img && path))
		return (false);
	*img = (t_img){0};
	img->ptr = mlx_xpm_file_to_image(mlx, (char *)path,
			&img->width, &img->height);
	if (!img->ptr)
		return (cub3d_error(NULL), img_load_err(path), false);
	img->addr
		= mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
		return (cub3d_error(NULL), img_load_err(path),
			img_destroy(mlx, img), false);
	return (true);
}

t_color	img_color_get(t_img *img, int x, int y)
{
	unsigned int	*raw;
	char			*px;
	t_color			col;

	col = (t_color){0};
	if (img && img->addr
		&& x >= 0 && x < img->width
		&& y >= 0 && y < img->height)
	{
		px = img->addr + y * img->line_len + x * (img->bpp / 8);
		raw = (unsigned int *)px;
		col.b = (*raw >> 0) & 0xFF;
		col.g = (*raw >> 8) & 0xFF;
		col.r = (*raw >> 16) & 0xFF;
	}
	return (col);
}
