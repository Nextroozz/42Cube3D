/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:17:00 by maxandresev       #+#    #+#             */
/*   Updated: 2025/12/03 15:49:13 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "./get_next_line.h"
#include <stdlib.h>

/**
 * Vérifie qu'il n'y a pas de contenu de map après des lignes vides
 */
static int	check_no_content_after(int fd, char **map_text)
{
	int		read_bytes;
	char	*line;

	read_bytes = 1;
	while (read_bytes == 1)
	{
		read_bytes = get_next_line(fd, &line);
		if (read_bytes == 1)
		{
			if (is_map_line(line))
			{
				free(line);
				free(*map_text);
				*map_text = NULL;
				print_error("Map has holes");
				return (0);
			}
			free(line);
		}
	}
	return (1);
}

/**
 * Lit toutes les lignes de map
 */
static char	*read_all_lines(int fd, char *first_line, int *err)
{
	int		read_bytes;
	char	*line;
	char	*map_text;

	map_text = NULL;
	if (first_line)
	{
		map_text = append_map_line(map_text, first_line);
		free(first_line);
	}
	read_bytes = 1;
	while (read_bytes == 1)
	{
		read_bytes = get_next_line(fd, &line);
		if (read_bytes != 1)
			break ;
		if (!is_map_line(line) && (free(line), 1))
			break ;
		map_text = append_map_line(map_text, line);
		free(line);
	}
	*err = (read_bytes == -1);
	return (map_text);
}

/**
 * Lit et stocke toutes les lignes de la map
 */
int	read_map_lines(int fd, t_map *map, char *first_line)
{
	char	*map_text;
	int		err;

	map_text = read_all_lines(fd, first_line, &err);
	if (err)
		return (free(map_text), print_error("Error reading file"), 0);
	if (!map_text)
		return (print_error("Map is empty"), 0);
	if (!check_no_content_after(fd, &map_text))
		return (0);
	if (!map_text)
		return (0);
	if (!find_player_in_text(map_text, map))
		return (free(map_text), 0);
	if (!allocate_and_fill_walls(map_text, map))
		return (free(map_text), print_error("Memory allocation failed"), 0);
	map->map_text = map_text;
	return (1);
}
