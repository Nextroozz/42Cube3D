/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by maseveri          #+#    #+#             */
/*   Updated: 2025/12/03 16:10:08 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "./get_next_line.h"
#include <stdlib.h>

/**
 * Traite une ligne de configuration (texture ou couleur)
 * Retourne 1 si succès, 0 si erreur
 */
static int	process_config_line(char *line, t_map *map, int *count)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
	{
		if (!parse_texture_line(line, map))
			return (0);
		(*count)++;
	}
	else if (line[i] == 'F' || line[i] == 'C')
	{
		if (!parse_color_line(line, map))
			return (0);
		(*count)++;
	}
	else
		return (print_error("Invalid configuration line"), 0);
	return (1);
}

/**
 * Valide que toutes les configurations sont présentes
 * Retourne 1 si succès, 0 si erreur
 */
static int	validate_config_complete(t_map *map, int elements_count)
{
	if (elements_count != 6)
		return (print_error("Incomplete configuration"), 0);
	if (!validate_textures(map))
		return (print_error("Missing texture definitions"), 0);
	if (!validate_colors(map))
		return (print_error("Missing color definitions"), 0);
	return (1);
}

/**
 * Traite une ligne config
 */
static int	handle_config_line(char *line, t_map *map, int *count, char **fl)
{
	if (is_map_line(line))
	{
		*fl = ft_strdup(line);
		free(line);
		return (2);
	}
	if (!process_config_line(line, map, count))
	{
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

/**
 * Parse les éléments de configuration (textures et couleurs)
 * Continue jusqu'à rencontrer le début de la map
 */
char	*parse_config_elements(int fd, t_map *map, int *success)
{
	int		read_bytes;
	char	*line;
	int		elements_count;
	int		result;
	char	*first_line;

	elements_count = 0;
	first_line = NULL;
	*success = 1;
	while (1)
	{
		read_bytes = get_next_line(fd, &line);
		if (read_bytes != 1)
			break ;
		result = handle_config_line(line, map, &elements_count, &first_line);
		if (result == 2 && validate_config_complete(map, elements_count))
			return (first_line);
		if (result == 0 || result == 2)
			return (free(first_line), *success = 0, NULL);
	}
	if (read_bytes == -1)
		return (print_error("Error reading file"), *success = 0, NULL);
	if (!validate_config_complete(map, elements_count))
		return (*success = 0, NULL);
	return (first_line);
}
