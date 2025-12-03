/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:50:00 by maxandresev       #+#    #+#             */
/*   Updated: 2025/12/03 15:33:28 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

/* Forward declarations */
size_t		ft_strlen_gnl(const char *s);
char		*ft_strdup_gnl(const char *s);

static char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*extract_and_save(char **storage)
{
	char	*line;
	char	*temp;
	size_t	i;
	size_t	j;

	if (!*storage || !(*storage)[0])
		return (NULL);
	i = 0;
	while ((*storage)[i] && (*storage)[i] != '\n')
		i++;
	line = malloc(i + ((*storage)[i] == '\n') + 1);
	if (!line)
		return (NULL);
	j = -1;
	while (++j < i)
		line[j] = (*storage)[j];
	if ((*storage)[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	temp = *storage;
	*storage = NULL;
	if (temp[i] == '\n' && temp[i + 1])
		*storage = ft_strdup_gnl(temp + i + 1);
	free(temp);
	return (line);
}

static char	*ft_strjoin_free(char *s1, char *s2, size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s2)
		return (NULL);
	result = malloc(ft_strlen_gnl(s1) + len + 1);
	if (!result)
		return (free(s1), NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			result[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (j < len)
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

static char	*read_and_store(int fd, char *storage)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr_gnl(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(storage), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		storage = ft_strjoin_free(storage, buffer, bytes_read);
		if (!storage)
			return (NULL);
	}
	return (storage);
}

int	get_next_line(int fd, char **line)
{
	static char	*storage;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	storage = read_and_store(fd, storage);
	if (!storage)
	{
		*line = NULL;
		return (0);
	}
	*line = extract_and_save(&storage);
	if (!*line)
		return (0);
	return (1);
}
