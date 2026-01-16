/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:17:09 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/15 15:49:21 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_isspace(int c)
{
	return (c == ' ' || (c >= 7 && c <= 13));
}

bool	ft_isnum(int c)
{
	return (c >= '0' && c <= '9');
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	size_t	slen;
	char	*ret;

	slen = ft_strlen(s);
	if (slen > n)
		slen = n;
	if (!slen)
		return (NULL);
	ret = malloc(sizeof(char) * (slen + 1));
	if (!ret)
		return (cub3d_error(NULL), perror("ft_strndup(): malloc()"), NULL);
	i = 0;
	while (i < slen)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!(n && src && dest))
		return (dest);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

void	cub3d_error(const char *error)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (error)
	{
		write(STDERR_FILENO, error, ft_strlen(error));
		write(STDERR_FILENO, "\n", 1);
	}
}
