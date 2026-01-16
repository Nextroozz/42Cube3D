/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:57:41 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/15 09:17:37 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

# define CONFIG_REQUIRED_ELEM_COUNT 6

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 42
# endif

# define MAP_CONFIG_NO "NO"
# define MAP_CONFIG_WE "WE"
# define MAP_CONFIG_SO "SO"
# define MAP_CONFIG_EA "EA"

// parse_map_config.c
bool	parse_map_config(t_map *map, int fd);

// parsing_map_content.c
bool	parse_map_content(t_map *map, int fd);

// map_validate.c
bool	map_validate(t_map *map);

// get_next_line.c
char	*get_next_line(int fd);
bool	gnl_strnjoin_free(char **s1, const char *s2, size_t len);

// parsing.c
t_vec2i	map_get_dimension(t_map *map);

#endif
