/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
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
/*                         VALIDATION DU FICHIER                             */
/* ========================================================================= */

/**
 * Vérifie que le fichier existe et a l'extension .cub
 * Retourne 1 si valide, 0 sinon
 */
int	validate_filename(char *filename)
{
	int	len;

	if (filename == NULL)
		return (0);
	len = ftstrlen(filename);
	if (len < 4)
		return (0);
	if (filename[len - 4] != '.' || filename[len - 3] != 'c'
		|| filename[len - 2] != 'u' || filename[len - 1] != 'b')
		return (0);
	if (len == 4)
		return (0);
	return (1);
}

/**
 * Ouvre le fichier et retourne le file descriptor
 * Retourne -1 en cas d'erreur
 */
int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error("Cannot open file");
		return (-1);
	}
	return (fd);
}
