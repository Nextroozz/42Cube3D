/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by maseveri          #+#    #+#             */
/*   Updated: 2025/12/03 15:33:28 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/* ========================================================================= */
/*                         PARSING DES TEXTURES                              */
/* ========================================================================= */

/**
 * Extrait le chemin de texture depuis la ligne à partir de l'index start
 * Retourne le chemin alloué ou NULL si erreur
 */
char	*extract_texture_path(char *line, int start)
{
	int		i;
	int		len;
	char	*path;

	i = start;
	while (line[i] != '\0' && line[i] != '\n' && line[i] != ' '
		&& line[i] != '\t')
		i++;
	len = i - start;
	if (len == 0)
		return (NULL);
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	i = 0;
	while (i < len)
	{
		path[i] = line[start + i];
		i++;
	}
	path[len] = '\0';
	return (path);
}

/**
 * Vérifie que le chemin a l'extension .xpm et que le fichier existe
 * Retourne 1 si valide, 0 sinon
 */
int	validate_texture_file(char *path)
{
	int	len;
	int	fd;

	len = ftstrlen(path);
	if (len < 4 || path[len - 4] != '.' || path[len - 3] != 'x'
		|| path[len - 2] != 'p' || path[len - 1] != 'm')
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

/**
 * Assigne le chemin de texture à la bonne variable de map
 * Retourne 1 si succès, 0 si déjà défini
 */
int	assign_texture(t_map *map, char identifier[3], char *path)
{
	if (identifier[0] == 'N' && identifier[1] == 'O')
	{
		if (map->north_texture != NULL)
			return (0);
		map->north_texture = path;
	}
	else if (identifier[0] == 'S' && identifier[1] == 'O')
	{
		if (map->south_texture != NULL)
			return (0);
		map->south_texture = path;
	}
	else if (identifier[0] == 'W' && identifier[1] == 'E')
	{
		if (map->west_texture != NULL)
			return (0);
		map->west_texture = path;
	}
	else if (identifier[0] == 'E' && identifier[1] == 'A')
	{
		if (map->east_texture != NULL)
			return (0);
		map->east_texture = path;
	}
	return (1);
}

/**
 * Extrait et valide l'identifiant de texture depuis la ligne
 * Retourne l'index après l'identifiant, ou -1 si invalide
 */
int	extract_identifier(char *line, char identifier[3])
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0'
		|| (line[i + 2] != ' ' && line[i + 2] != '\t'))
		return (-1);
	identifier[0] = line[i];
	identifier[1] = line[i + 1];
	identifier[2] = '\0';
	if (!((line[i] == 'N' && line[i + 1] == 'O')
			|| (line[i] == 'S' && line[i + 1] == 'O')
			|| (line[i] == 'W' && line[i + 1] == 'E')
			|| (line[i] == 'E' && line[i + 1] == 'A')))
		return (-1);
	i += 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

/**
 * Parse une ligne de texture (NO, SO, WE, EA)
 * Format: "NO textures/path/to/texture.xpm"
 * Retourne 1 si succès, 0 si erreur
 */
int	parse_texture_line(char *line, t_map *map)
{
	int		i;
	char	identifier[3];
	char	*path;

	i = extract_identifier(line, identifier);
	if (i == -1)
		return (print_error("Invalid texture identifier"), 0);
	path = extract_texture_path(line, i);
	if (!path)
		return (print_error("Missing texture path"), 0);
	if (!validate_texture_file(path))
		return (print_error("Invalid texture file"), free(path), 0);
	if (!assign_texture(map, identifier, path))
		return (print_error("Duplicate texture definition"), free(path), 0);
	return (1);
}
