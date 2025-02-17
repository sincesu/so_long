/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:06:02 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 05:02:26 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mov_player_if_valid(t_game *game, int new_line, int new_col)
{
	if (game->map->map_test[new_line][new_col] == '1')
		return (0);
	set_player_position(game->map, new_line, new_col);
	return (1);
}

int	process_key(int keycode, t_game *game)
{
	int	new_line;
	int	new_col;

	new_line = game->map->player_line;
	new_col = game->map->player_col;
	if (keycode == UP)
		new_line--;
	else if (keycode == DOWN)
		new_line++;
	else if (keycode == LEFT)
		new_col--;
	else if (keycode == RIGHT)
		new_col++;
	else
		return (0);
	return (mov_player_if_valid(game, new_line, new_col));
}

int	key_input_handler(int keycode, t_game *game)
{
	if (keycode == ESC)
		safe_exit(game, "Program finished");
	if (!process_key(keycode, game))
		return (0);
	if (is_collectible(game))
	{
		game->map->map_test[game->map->player_line]
		[game->map->player_col] = '0';
		game->map->collectible--;
	}
	print_move_count(game->move_count++);
	if (game->map->map_test[game->map->player_line]
		[game->map->player_col] == 'E'
		&& game->map->collectible == 0)
		safe_exit(game, "Program finished");
	render_map(game);
	render_player(game);
	return (0);
}
