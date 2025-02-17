/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:50:47 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 09:09:13 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

void	filename_checker(char *str)
{
	char	*tmp;

	tmp = ft_strchr(str, '.');
	if (!tmp)
		safe_exit(NULL, "map file has no .");
	if (!ft_compare(tmp, ".ber"))
		safe_exit(NULL, "map file extension must be ber");
}

void	check_is_rect(t_game *game)
{
	int	l;

	l = 0;
	while (game->map->map_test[l])
	{
		if (gnl_strlen(game->map->map_test[l]) != game->map->cols)
			safe_exit(game, "Map is not rect");
		l++;
	}
}

void	map_value_controller(t_game *game)
{
	int	w;
	int	l;

	l = 0;
	while (game->map->map_test[l])
	{
		w = 0;
		while (game->map->map_test[l][w])
		{
			mini_controller(game, l, w);
			w++;
		}
		l++;
	}
	if (game->map->exit != 1)
		safe_exit (game, "You must have one exit");
	if (game->map->collectible < 1)
		safe_exit (game, "You must have one or more collectible");
	if (game->map->start != 1)
		safe_exit(game, "You must have a one player");
}

void	mini_controller(t_game *game, int l, int w)
{
	char	c;

	c = game->map->map_test[l][w];
	if (c == 'C')
		game->map->collectible++;
	else if (c == 'P')
	{
		game->map->player_line = l;
		game->map->player_col = w;
		game->map->start++;
	}
	else if (c == 'E')
		game->map->exit++;
	else if (game->map->map_test[l][w] != '0'
		&& game->map->map_test[l][w] != '1')
		safe_exit(game, "You can't use the different value for map");
}

void	map_wall_controller(t_game *game, char **str)
{
	int	l;
	int	i;

	l = 0;
	while (str[l])
	{
		i = 0;
		while (str[l][i])
		{
			if (str[0][i] != '1' || str[l][0] != '1'
				|| str[l][game->map->cols - 1] != '1')
				safe_exit(game, "Check walls");
			if (l == game->map->line - 1)
			{
				while (str[l][i])
					if (str[l][i++] != '1')
						safe_exit(game, "Check walls");
			}
			else
				i++;
		}
		l++;
	}
}
