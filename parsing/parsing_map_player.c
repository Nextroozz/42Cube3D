/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by maseveri          #+#    #+#             */
/*   Updated: 2025/12/03 15:33:28 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Assigne l'orientation du joueur selon le caractère
 */
void	assign_player_direction(t_map *map, char c)
{
	if (c == 'N')
		map->player.dir = ORIENTATION_NORTH;
	else if (c == 'S')
		map->player.dir = ORIENTATION_SOUTH;
	else if (c == 'E')
		map->player.dir = ORIENTATION_EAST;
	else
		map->player.dir = ORIENTATION_WEST;
}

/**
 * Traite un caractère joueur trouvé dans la map
 */
static void	set_player_pos(t_map *map, char c, int xy[2], int *count)
{
	(*count)++;
	map->player.pos.x = (float)xy[0] + 0.5f;
	map->player.pos.y = (float)xy[1] + 0.5f;
	assign_player_direction(map, c);
}

/**
 * Trouve la position du joueur dans la map texte
 */
int	find_player_in_text(char *map_text, t_map *map)
{
	int	i;
	int	xy[2];
	int	player_count;

	i = 0;
	xy[0] = 0;
	xy[1] = 0;
	player_count = 0;
	while (map_text[i])
	{
		if (map_text[i] == '\n' && ++xy[1])
			xy[0] = 0;
		else if (map_text[i] == 'N' || map_text[i] == 'S'
			|| map_text[i] == 'E' || map_text[i] == 'W')
		{
			set_player_pos(map, map_text[i], xy, &player_count);
			xy[0]++;
		}
		else
			xy[0]++;
		i++;
	}
	if (player_count != 1)
		return (print_error("Invalid number of player start positions"), 0);
	return (1);
}
