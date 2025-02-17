/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:48:50 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 02:09:44 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	dbl_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	gnl_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char *str, char *tmp)
{
	int		i;
	int		k;
	char	*s;

	i = -1;
	k = 0;
	if (!str)
	{
		str = malloc(1);
		if (!str)
			return (free(str), NULL);
		str[0] = '\0';
	}
	if (!str || !tmp)
		return (NULL);
	s = malloc((gnl_strlen(str) + gnl_strlen(tmp) + 1));
	if (!s)
		return (free(str), NULL);
	while (str[++i])
	{
		s[i] = str[i];
	}
	while (tmp[k])
		s[i++] = tmp[k++];
	return (s[i] = '\0', free(str), s);
}
