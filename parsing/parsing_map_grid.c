/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by maseveri          #+#    #+#             */
/*   Updated: 2025/12/03 15:34:31 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

/**
 * Trouve les dimensions maximales de la map
 */
void	get_map_dimensions(t_map *map, int *max_x, int *max_y)
{
	int	i;

	*max_x = 0;
	*max_y = 0;
	i = 0;
	while (i < map->wallcount)
	{
		if ((int)map->walls[i].x > *max_x)
			*max_x = (int)map->walls[i].x;
		if ((int)map->walls[i].y > *max_y)
			*max_y = (int)map->walls[i].y;
		i++;
	}
}

/**
 * Alloue une grille 2D pour la validation
 */
char	**create_grid(int max_x, int max_y)
{
	char	**grid;
	int		i;
	int		j;

	grid = malloc(sizeof(char *) * (max_y + 1));
	if (!grid)
		return (NULL);
	i = 0;
	while (i <= max_y)
	{
		grid[i] = malloc(sizeof(char) * (max_x + 1));
		if (!grid[i])
			return (NULL);
		j = 0;
		while (j <= max_x)
		{
			grid[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (grid);
}

/**
 * Remplit la grille depuis map_text
 */
void	fill_grid_with_walls(char **grid, t_map *map)
{
	int		i;
	int		x;
	int		y;
	char	c;

	i = 0;
	x = 0;
	y = 0;
	while (map->map_text && map->map_text[i])
	{
		c = map->map_text[i];
		if (c == '\n' && ++y)
			x = 0;
		else
		{
			if (c == '1' || c == '0')
				grid[y][x] = c;
			else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				grid[y][x] = '0';
			x++;
		}
		i++;
	}
}

/**
 * Libère la grille allouée
 */
void	free_grid(char **grid, int max_y)
{
	int	i;

	i = 0;
	while (i <= max_y)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

/**
 * Vérifie qu'une case accessible n'a pas de voisin vide
 */
int	check_cell_neighbors(char **grid, int x, int y, int *dims)
{
	if (x > 0 && grid[y][x - 1] == ' ')
		return (0);
	if (x < dims[0] && grid[y][x + 1] == ' ')
		return (0);
	if (y > 0 && grid[y - 1][x] == ' ')
		return (0);
	if (y < dims[1] && grid[y + 1][x] == ' ')
		return (0);
	return (1);
}
