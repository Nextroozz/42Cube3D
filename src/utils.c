/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:22:18 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/14 20:39:22 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	slen;
	size_t	i;

	slen = ft_strlen(s);
	if (!slen)
		return (NULL);
	ret = malloc(sizeof(char) * (slen + 1));
	if (!ret)
		return (cub3d_error(NULL), perror("ft_strdup(): malloc()"), NULL);
	i = 0;
	while (i < slen)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strnjoin(const char *s1, const char *s2, size_t n)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;
	char	*ret;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s2_len > n)
		s2_len = n;
	if (!(s1_len || s2_len))
		return (NULL);
	ret = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ret)
		return (cub3d_error(NULL), perror("ft_strnjoin(): malloc()"), NULL);
	i = 0;
	while (i < s1_len)
		*ret++ = s1[i++];
	j = 0;
	while (j < s2_len)
		*ret++ = s2[j++];
	*ret = '\0';
	return (ret - i - j);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		if (s[i++] == (char)c)
			return (&((char *)s)[i - 1]);
	return (NULL);
}
