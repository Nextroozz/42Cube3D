/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:05:29 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/15 09:01:55 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	gnl_strnjoin_free(char **s1, const char *s2, size_t len)
{
	char	*tmp;

	if (!len)
		return (true);
	tmp = *s1;
	*s1 = ft_strnjoin(*s1, s2, len);
	free(tmp);
	if (!*s1)
		return (cub3d_error("gnl_strnjoin_free(): failed to join"), false);
	return (true);
}

char	*get_next_line(int fd)
{
	static char	buf[GNL_BUFFER_SIZE + 1];
	char		*ret;
	char		*tmp;
	ssize_t		read_ret;
	size_t		nl_len;

	ret = NULL;
	tmp = ft_strchr(buf, '\n');
	while (!tmp)
	{
		if (!gnl_strnjoin_free(&ret, buf, ft_strlen(buf)))
			return (NULL);
		read_ret = read(fd, buf, GNL_BUFFER_SIZE);
		if (read_ret < 0)
			return (cub3d_error(NULL),
				perror("get_next_line(): read()"), NULL);
		buf[read_ret] = '\0';
		if (read_ret == 0)
			return (ret);
		tmp = ft_strchr(buf, '\n');
	}
	nl_len = ft_strlen(tmp + 1);
	gnl_strnjoin_free(&ret, buf, tmp - buf + 1);
	return (ft_memmove(buf, tmp + 1, nl_len), buf[nl_len] = '\0', ret);
}
