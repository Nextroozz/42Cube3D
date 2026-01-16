/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:54:29 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/17 14:55:00 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*config_get_text_path(const char *line)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (NULL);
	len = 0;
	while (line[i + len] && !ft_isspace(line[i + len]))
		len++;
	return (ft_strndup(line + i, len));
}

static bool	config_get_textures(t_map *map, const char *line)
{
	if (!ft_strncmp(MAP_CONFIG_NO, line, sizeof(MAP_CONFIG_NO) - 1)
		&& !map->north_texture)
		return (
			map->north_texture
			= config_get_text_path(line + sizeof(MAP_CONFIG_NO) - 1), true);
	else if (!ft_strncmp(MAP_CONFIG_WE, line, sizeof(MAP_CONFIG_WE) - 1)
		&& !map->west_texture)
		return (
			map->west_texture
			= config_get_text_path(line + sizeof(MAP_CONFIG_WE) - 1), true);
	else if (!ft_strncmp(MAP_CONFIG_SO, line, sizeof(MAP_CONFIG_SO) - 1)
		&& !map->south_texture)
		return (
			map->south_texture
			= config_get_text_path(line + sizeof(MAP_CONFIG_SO) - 1), true);
	else if (!ft_strncmp(MAP_CONFIG_EA, line, sizeof(MAP_CONFIG_EA) - 1)
		&& !map->east_texture)
		return (
			map->east_texture
			= config_get_text_path(line + sizeof(MAP_CONFIG_EA) - 1), true);
	return (false);
}

static bool	config_get(t_map *map, const char *line, int *config_elem)
{
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (true);
	if (!config_get_textures(map, line + i))
	{
		if (line[i] == 'F' && !map->fcolor_set)
		{
			if (!cub3d_strtorgb(&map->floor_color, line + i + 1))
				return (false);
			map->fcolor_set = true;
		}
		else if (line[i] == 'C' && !map->ccolor_set)
		{
			if (!cub3d_strtorgb(&map->ceiling_color, line + i + 1))
				return (false);
			map->ccolor_set = true;
		}
		else
			return (cub3d_error("config_get(): Invalid configuration"), false);
	}
	return (*config_elem += 1, true);
}

bool	parse_map_config(t_map *map, int fd)
{
	char	*line;
	int		config_elem;

	if (!map)
		return (cub3d_error("parse_map_config(): map pointer is NULL"),
			false);
	config_elem = 0;
	while (config_elem != CONFIG_REQUIRED_ELEM_COUNT)
	{
		line = get_next_line(fd);
		if (!line)
			return (cub3d_error("parse_map_config(): abrupt eof"), false);
		if (!config_get(map, line, &config_elem))
			return (free(line), false);
		free(line);
	}
	if (!(map->north_texture && map->south_texture
			&& map->west_texture && map->east_texture))
		return (
			cub3d_error("parse_map_config(): failed to complete config"),
			false);
	return (true);
}
