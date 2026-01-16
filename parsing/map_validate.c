/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 20:27:44 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/15 16:03:17 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	grid_destroy(char **grid, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static char	**grid_create(t_vec2i map_dim)
{
	char	**grid;
	int		i;
	int		j;

	grid = malloc(sizeof(char *) * (map_dim.y + 3));
	if (!grid)
		return (cub3d_error(NULL), perror("grid_create(): malloc()"), NULL);
	i = 0;
	while (i < map_dim.y + 3)
	{
		grid[i] = malloc(sizeof(char) * (map_dim.x + 3));
		if (!grid[i])
			return (cub3d_error(NULL), perror("grid_create(): malloc()"),
				grid_destroy(grid, i), NULL);
		j = 0;
		while (j < map_dim.x + 3)
		{
			grid[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (grid);
}

static void	grid_fill(t_map *map, char **grid)
{
	t_vec2i	pos;
	size_t	i;

	i = 0;
	pos = (t_vec2i){0};
	while (map->content[i])
	{
		if (map->content[i] == '\n')
			pos = (t_vec2i){0, pos.y + 1};
		else
		{
			grid[pos.y + 1][pos.x + 1] = map->content[i];
			pos.x++;
		}
		i++;
	}
	grid[(int)map->player.pos.y + 1][(int)map->player.pos.x + 1] = 'P';
}

static bool	grid_flood(char **grid, t_vec2i pos, t_vec2i dim)
{
	if (pos.x < 0 || pos.x >= dim.x || pos.y < 0 || pos.y >= dim.y)
		return (true);
	if (grid[pos.y][pos.x] == '1' || grid[pos.y][pos.x] == 'V')
		return (true);
	if (grid[pos.y][pos.x] == 'P' || grid[pos.y][pos.x] == '0')
		return (false);
	grid[pos.y][pos.x] = 'V';
	return (grid_flood(grid, (t_vec2i){pos.x + 1, pos.y}, dim)
		&& grid_flood(grid, (t_vec2i){pos.x, pos.y + 1}, dim)
		&& grid_flood(grid, (t_vec2i){pos.x - 1, pos.y}, dim)
		&& grid_flood(grid, (t_vec2i){pos.x, pos.y - 1}, dim));
}

bool	map_validate(t_map *map)
{
	t_vec2i	map_dim;
	char	**grid;
	bool	valid;

	if (!map->wallcount)
		return (cub3d_error("No walls defined"), false);
	map_dim = map_get_dimension(map);
	grid = grid_create(map_dim);
	if (!grid)
		return (false);
	grid_fill(map, grid);
	valid = grid_flood(grid, (t_vec2i){0},
			(t_vec2i){map_dim.x + 3, map_dim.y + 3});
	if (!valid)
		cub3d_error("Map isn't closed by walls");
	grid_destroy(grid, map_dim.y + 3);
	return (valid);
}
