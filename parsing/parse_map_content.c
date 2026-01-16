/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:21:44 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/17 13:14:38 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	init_player(t_map *map, char line_char,
	t_vec2i pos, bool *player_set)
{
	if (line_char != 'N' && line_char != 'S'
		&& line_char != 'E' && line_char != 'W')
		return (cub3d_error("map content must be one of those: '10NWES'"),
			false);
	if (*player_set)
		return (cub3d_error("only one player is allowed"), false);
	map->player.pos = (t_vec2){pos.x + 0.5, pos.y + 0.5};
	if (line_char == 'N')
		map->player.dir = ORIENTATION_NORTH;
	else if (line_char == 'S')
		map->player.dir = ORIENTATION_SOUTH;
	else if (line_char == 'W')
		map->player.dir = ORIENTATION_WEST;
	else
		map->player.dir = ORIENTATION_EAST;
	*player_set = true;
	return (true);
}

static bool	fill_map_field(t_map *map, const char *line,
	t_vec2i pos, bool *pset)
{
	size_t	i;
	t_vec2i	*walls_tmp;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1')
		{
			walls_tmp = malloc((map->wallcount + 1) * sizeof(t_vec2i));
			if (map->wallcount)
			{
				ft_memcpy(walls_tmp, map->walls,
					map->wallcount * sizeof(t_vec2i));
				free(map->walls);
			}
			walls_tmp[map->wallcount++] = pos;
			map->walls = walls_tmp;
		}
		else if (line[i] != '0' && line[i] != ' ')
			if (!init_player(map, line[i], pos, pset))
				return (false);
		pos.x++;
		i++;
	}
	return (true);
}

static bool	empty_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (!line[i]);
}

bool	parse_map_content(t_map *map, int fd)
{
	t_vec2i	pos;
	char	*line;
	bool	player_set;

	line = NULL;
	player_set = false;
	pos = (t_vec2i){0};
	while (true)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (empty_line(line) && pos.y == 0)
			continue ;
		if (!fill_map_field(map, line, pos, &player_set))
			return (free(line), false);
		if (!gnl_strnjoin_free(&map->content, line, ft_strlen(line)))
			return (free(line), false);
		pos = (t_vec2i){0, pos.y + 1};
	}
	if (!player_set)
		return (cub3d_error("player isn't defined"), false);
	return (true);
}
