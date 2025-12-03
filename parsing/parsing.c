/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:32:50 by maxandresev       #+#    #+#             */
/*   Updated: 2025/12/03 15:49:13 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include "./get_next_line.h"

/* ========================================================================= */
/*                          FONCTIONS UTILITAIRES                            */
/* ========================================================================= */

/**
 * Alloue et initialise la structure t_map
 * Retourne NULL en cas d'erreur d'allocation
 */
static t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->east_texture = NULL;
	map->west_texture = NULL;
	map->wallcount = 0;
	map->walls = NULL;
	map->player.pos.x = -1.0f;
	map->player.pos.y = -1.0f;
	map->player.dir = -1.0f;
	map->floor_color.r = -1;
	map->floor_color.g = -1;
	map->floor_color.b = -1;
	map->ceiling_color.r = -1;
	map->ceiling_color.g = -1;
	map->ceiling_color.b = -1;
	map->map_text = NULL;
	return (map);
}

/**
 * Libère toute la mémoire allouée pour la structure t_map
 */
static void	free_map(t_map *map)
{
	free(map->north_texture);
	free(map->south_texture);
	free(map->east_texture);
	free(map->west_texture);
	free(map->walls);
	free(map->map_text);
	free(map);
}

/**
 * Affiche un message d'erreur sur stderr
 */
void	print_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ftstrlen(message));
	write(2, "\n", 1);
}

/* ========================================================================= */
/*                       PARSING PRINCIPAL DU FICHIER                        */
/* ========================================================================= */

/**
 * Nettoie et retourne NULL en cas d'erreur
 */
static t_map	*cleanup_and_fail(t_map *map, int fd)
{
	if (map)
		free_map(map);
	if (fd != -1)
		close(fd);
	return (NULL);
}

/**
 * Parse le fichier .cub complet
 * Retourne un pointeur vers t_map si succès, NULL si erreur
 */
t_map	*parse_cub_file(char *filename)
{
	int		fd;
	t_map	*map;
	char	*first_line;
	int		success;

	if (!validate_filename(filename))
		return (print_error("Invalid filename"), NULL);
	fd = open_file(filename);
	if (fd == -1)
		return (NULL);
	map = init_map();
	if (!map)
		return (print_error("Allocation failed"), cleanup_and_fail(NULL, fd));
	first_line = parse_config_elements(fd, map, &success);
	if (!success)
		return (cleanup_and_fail(map, fd));
	if (!read_map_lines(fd, map, first_line))
		return (cleanup_and_fail(map, fd));
	if (!validate_map(map))
		return (cleanup_and_fail(map, fd));
	close(fd);
	return (map);
}
