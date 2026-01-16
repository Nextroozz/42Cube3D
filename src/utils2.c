/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:57:38 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/16 15:24:35 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	n--;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	return (s1[i] - s2[i]);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = malloc(sizeof(unsigned char) * n);
	if (!tmp)
		return (cub3d_error(NULL), perror("ft_memmove(): malloc()"), NULL);
	i = 0;
	while (i < n)
	{
		tmp[i] = ((unsigned char *)src)[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = tmp[i];
		i++;
	}
	free(tmp);
	return (dest);
}

static void	cub3d_strtorgb_skipspace(const char *s, size_t *i)
{
	while (ft_isspace(s[*i]))
		*i += 1;
}

bool	cub3d_get_val(t_color *col, const char *s, size_t *i, int col_count)
{
	while (ft_isnum(s[*i]))
	{
		if (s[*i] - '0' + col->params[col_count] * 10 > 255)
			return (cub3d_error("cub3d_strtorgb(): uint8 overflow"),
				false);
		col->params[col_count] = col->params[col_count] * 10 + s[(*i)++] - '0';
	}
	return (true);
}

bool	cub3d_strtorgb(t_color *col, const char *s)
{
	size_t	i;
	int		col_count;

	if (!s)
		return (false);
	i = 0;
	*col = (t_color){0};
	col_count = 0;
	while (col_count < 3)
	{
		cub3d_strtorgb_skipspace(s, &i);
		if ((s[i] && !ft_isnum(s[i])) || !s[i])
			return (cub3d_error("cub3d_strtorgb(): color invalid format"),
				false);
		if (!cub3d_get_val(col, s, &i, col_count))
			return (false);
		cub3d_strtorgb_skipspace(s, &i);
		if (col_count++ < 2 && s[i++] != ',')
			return (cub3d_error("cub3d_strtorgb(): comma shall separate "
					"color values"), false);
	}
	cub3d_strtorgb_skipspace(s, &i);
	if (s[i])
		return (cub3d_error("cub3d_strtorgb(): color format's invalid"), false);
	return (true);
}
