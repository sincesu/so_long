/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:12:30 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 02:07:19 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*buffer;
	int		i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(s) < len + start)
		len = ft_strlen(s) - start;
	buffer = (char *)malloc((len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		buffer[i] = s[start + i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
