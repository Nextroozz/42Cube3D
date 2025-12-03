/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by maseveri          #+#    #+#             */
/*   Updated: 2025/12/03 15:33:28 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Vérifie que toutes les textures requises sont présentes
 * Retourne 1 si valide, 0 sinon
 */
int	validate_textures(t_map *map)
{
	if (map->north_texture == NULL || map->south_texture == NULL
		|| map->east_texture == NULL || map->west_texture == NULL)
		return (0);
	return (1);
}
