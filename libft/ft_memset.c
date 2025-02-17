/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:11:02 by saincesu          #+#    #+#             */
/*   Updated: 2025/01/29 12:42:20 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*x;

	i = 0;
	x = (unsigned char *)b;
	while (i < len)
	{
		x[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
