/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 02:01:33 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/04 22:00:58 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_last(char *str)
{
	char	*tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		return (free(str), NULL);
	}
	tmp = malloc((gnl_strlen(str) - i + 1));
	if (!tmp)
		return (free(str), NULL);
	i++;
	while (str[i])
		tmp[k++] = str[i++];
	tmp[k] = '\0';
	free(str);
	return (tmp);
}

char	*ft_line(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	tmp = malloc(i + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_read(char *str, int fd)
{
	char	*tmp;
	int		size;

	size = 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (!gnl_strchr(str, '\n') && size != 0)
	{
		size = read(fd, tmp, BUFFER_SIZE);
		if (size == -1)
		{
			return (free(str), str = NULL, free(tmp), NULL);
		}
		tmp[size] = '\0';
		str = gnl_strjoin(str, tmp);
		if (!str)
			return (free(tmp), NULL);
	}
	free(tmp);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(str), str = NULL, NULL);
	str = ft_read(str, fd);
	if (!str)
		return (free(str), str = NULL, NULL);
	tmp = ft_line(str);
	str = ft_last(str);
	return (tmp);
}
