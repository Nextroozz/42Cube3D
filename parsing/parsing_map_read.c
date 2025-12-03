/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by maseveri          #+#    #+#             */
/*   Updated: 2025/12/03 15:33:28 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "./get_next_line.h"
#include <stdlib.h>

/**
 * Vérifie si une ligne fait partie de la map
 * Retourne 1 si c'est une ligne de map, 0 sinon
 */
int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Ajoute une ligne à la map en cours de construction
 * Retourne le nouveau pointeur ou NULL si erreur
 */
char	*append_map_line(char *map_data, char *line)
{
	char	*temp;
	char	*new_data;

	temp = map_data;
	if (!map_data)
		new_data = ft_strdup(line);
	else
		new_data = ft_strjoin(map_data, line);
	free(temp);
	return (new_data);
}

/**
 * Compte le nombre de murs dans la map texte
 */
int	count_walls(char *map_text)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map_text[i])
	{
		if (map_text[i] == '1')
			count++;
		i++;
	}
	return (count);
}

/**
 * Remplit le tableau de murs avec les positions depuis la map texte
 */
void	fill_walls_array(char *map_text, t_vec2 *walls)
{
	int	i;
	int	x;
	int	y;
	int	wall_idx;

	i = 0;
	x = 0;
	y = 0;
	wall_idx = 0;
	while (map_text[i])
	{
		if (map_text[i] == '\n' && ++y)
			x = 0;
		else if (map_text[i] == '1')
		{
			walls[wall_idx].x = (float)x;
			walls[wall_idx].y = (float)y;
			wall_idx++;
			x++;
		}
		else
			x++;
		i++;
	}
}

/**
 * Alloue et remplit le tableau de murs
 */
int	allocate_and_fill_walls(char *map_text, t_map *map)
{
	map->wallcount = count_walls(map_text);
	map->walls = malloc(sizeof(t_vec2) * map->wallcount);
	if (!map->walls)
		return (0);
	fill_walls_array(map_text, map->walls);
	return (1);
}
