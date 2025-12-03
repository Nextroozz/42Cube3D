/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by maseveri          #+#    #+#             */
/*   Updated: 2025/12/03 15:33:28 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* ========================================================================= */
/*                         PARSING DES COULEURS                              */
/* ========================================================================= */

/**
 * Parse une valeur RGB (0-255)
 * Retourne la valeur si valide, -1 si erreur
 */
int	parse_rgb_value(char *str)
{
	int	value;
	int	i;

	i = 0;
	value = 0;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		if (value > 255)
			return (-1);
		i++;
	}
	return (value);
}

/**
 * Extrait une composante RGB depuis la ligne
 * Avance l'index après le nombre et retourne la valeur ou -1 si erreur
 */
int	extract_rgb_component(char *line, int *i, int need_comma)
{
	int	value;

	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	value = parse_rgb_value(&line[*i]);
	if (value == -1)
		return (-1);
	while (line[*i] >= '0' && line[*i] <= '9')
		(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (need_comma && line[*i] != ',')
		return (-1);
	if (need_comma)
		(*i)++;
	return (value);
}

/**
 * Assigne les valeurs RGB à la couleur selon le type
 */
int	assign_color(t_map *map, char type, int rgb[3])
{
	if (type == 'F')
	{
		if (map->floor_color.r != -1)
			return (0);
		map->floor_color.r = rgb[0];
		map->floor_color.g = rgb[1];
		map->floor_color.b = rgb[2];
		return (1);
	}
	else if (type == 'C')
	{
		if (map->ceiling_color.r != -1)
			return (0);
		map->ceiling_color.r = rgb[0];
		map->ceiling_color.g = rgb[1];
		map->ceiling_color.b = rgb[2];
		return (1);
	}
	return (0);
}

/**
 * Parse une ligne de couleur (F ou C)
 * Format: "F 220,100,0" ou "C 225,30,0"
 * Retourne 1 si succès, 0 si erreur
 */
int	parse_color_line(char *line, t_map *map)
{
	int		i;
	char	type;
	int		rgb[3];

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if ((line[i] != 'F' && line[i] != 'C')
		|| (line[i + 1] != ' ' && line[i + 1] != '\t'))
		return (print_error("Invalid color identifier"), 0);
	type = line[i++];
	rgb[0] = extract_rgb_component(line, &i, 1);
	rgb[1] = extract_rgb_component(line, &i, 1);
	rgb[2] = extract_rgb_component(line, &i, 0);
	if (rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1)
		return (print_error("Invalid RGB value"), 0);
	if (!assign_color(map, type, rgb))
		return (print_error("Duplicate or invalid color"), 0);
	return (1);
}

/**
 * Vérifie que les couleurs sont définies
 * Retourne 1 si valide, 0 sinon
 */
int	validate_colors(t_map *map)
{
	if (map->floor_color.r == -1 || map->ceiling_color.r == -1
		|| map->floor_color.g == -1 || map->floor_color.b == -1
		|| map->ceiling_color.g == -1 || map->ceiling_color.b == -1)
		return (0);
	return (1);
}
