/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:38:22 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/15 09:18:35 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_vec2i	map_get_dimension(t_map *map)
{
	t_vec2i	max;
	t_vec2i	wpos;
	int		i;

	max = (t_vec2i){0};
	i = 0;
	while (i < map->wallcount)
	{
		wpos = map->walls[i];
		if (wpos.x > max.x)
			max.x = wpos.x;
		if (wpos.y > max.y)
			max.y = wpos.y;
		i++;
	}
	return (max);
}

bool	map_path_valid(const char *path)
{
	const char	*extension;
	size_t		extension_len;
	size_t		path_len;

	extension = EXTENSION_MAP;
	extension_len = sizeof(EXTENSION_MAP) / sizeof(EXTENSION_MAP)[0] - 1;
	path_len = ft_strlen(path);
	return (path_len >= extension_len
		&& ft_strcmp(path + path_len - extension_len, extension) == 0);
}

bool	map_create(t_map *map, const char *map_file)
{
	int		fd;

	if (!map)
		return (false);
	*map = (t_map){0};
	if (!map_file)
		return (cub3d_error("map_create(): given map path is NULL"), false);
	if (!map_path_valid(map_file))
		return (
			cub3d_error(
				"map_create(): map path must be a " EXTENSION_MAP " file"),
			false);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (cub3d_error(NULL), perror("map_create(): open()"), false);
	if (!parse_map_config(map, fd))
		return (close(fd), map_destroy(map), false);
	if (!parse_map_content(map, fd))
		return (close(fd), map_destroy(map), false);
	close(fd);
	if (!map_validate(map))
		return (map_destroy(map), false);
	return (true);
}

void	map_destroy(t_map *map)
{
	if (!map)
		return ;
	free(map->north_texture);
	free(map->east_texture);
	free(map->south_texture);
	free(map->west_texture);
	free(map->walls);
	free(map->content);
	*map = (t_map){0};
}
