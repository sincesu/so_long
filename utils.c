/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:04:56 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/16 21:39:21 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

int	ft_compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	return (1);
}

int	is_collectible(t_game *game)
{
	return (game->map->map_test[game->map->player_line]
		[game->map->player_col] == 'C');
}

void	set_player_position(t_map *map, int l, int c)
{
	map->player_line = l;
	map->player_col = c;
}

void	print_move_count(int count)
{
	ft_putstr_fd("Move count: ", 1);
	ft_putnbr_fd(count, 1);
	ft_putchar_fd('\n', 1);
}
