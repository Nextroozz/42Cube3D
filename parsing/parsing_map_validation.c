/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by maseveri          #+#    #+#             */
/*   Updated: 2025/12/03 15:33:28 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * Vérifie que les bords de la map sont fermés
 * Les cases '0' (accessibles) ne doivent PAS être sur les bords
 */
int	check_borders(char **grid, int max_x, int max_y)
{
	int	i;

	i = 0;
	while (i <= max_x)
	{
		if (grid[0][i] == '0')
			return (0);
		if (grid[max_y][i] == '0')
			return (0);
		i++;
	}
	i = 0;
	while (i <= max_y)
	{
		if (grid[i][0] == '0')
			return (0);
		if (grid[i][max_x] == '0')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Vérifie toutes les cases accessibles
 */
int	check_accessible_cells(char **grid, int max_x, int max_y)
{
	int	x;
	int	y;
	int	dims[2];

	dims[0] = max_x;
	dims[1] = max_y;
	y = 0;
	while (y <= max_y)
	{
		x = 0;
		while (x <= max_x)
		{
			if (grid[y][x] == '0')
			{
				if (!check_cell_neighbors(grid, x, y, dims))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/**
 * Vérifie que la map est entourée de murs (caractère '1')
 * Utilise un algorithme de flood fill ou parcours récursif
 * Retourne 1 si valide, 0 si erreur
 */
int	validate_map_walls(t_map *map)
{
	char	**grid;
	int		max_x;
	int		max_y;

	if (!map->walls || map->wallcount == 0)
		return (print_error("No walls defined in map"), 0);
	get_map_dimensions(map, &max_x, &max_y);
	grid = create_grid(max_x, max_y);
	if (!grid)
		return (print_error("Memory allocation failed"), 0);
	fill_grid_with_walls(grid, map);
	if (!check_borders(grid, max_x, max_y))
		return (free_grid(grid, max_y), print_error("Map not closed"), 0);
	if (!check_accessible_cells(grid, max_x, max_y))
		return (free_grid(grid, max_y), print_error("Map has holes"), 0);
	free_grid(grid, max_y);
	return (1);
}

/**
 * Valide la map complète
 * Retourne 1 si valide, 0 si erreur
 */
int	validate_map(t_map *map)
{
	int	max_x;
	int	max_y;

	max_x = 0;
	max_y = 0;
	if (map == NULL)
		return (0);
	if (map->walls == NULL || map->wallcount < 12)
		return (print_error("No walls defined in map"), 0);
	if (map->player.pos.x < 0 || map->player.pos.y < 0)
		return (print_error("Player start position not defined"), 0);
	if (map->player.dir != 0 && map->player.dir != 90
		&& map->player.dir != 180 && map->player.dir != 270)
		return (print_error("Player direction not defined"), 0);
	get_map_dimensions(map, &max_x, &max_y);
	if (max_x < 3 || max_y < 3)
		return (print_error("Map dimensions invalid"), 0);
	if (!validate_map_walls(map))
		return (0);
	return (1);
}
