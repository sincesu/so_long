/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:34:41 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 09:44:35 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <X11/X.h>

void	map_process(char *filename, t_game **game)
{
	filename_checker(filename);
	(*game) = init_game();
	(*game)->map = init_map();
	map_loader(filename, *game);
	check_is_rect(*game);
	map_value_controller(*game);
}

int	main(int ac, char **av)
{
	t_game	*game;
	char	*filename;
	char	**str;

	if (ac == 2)
	{
		game = NULL;
		filename = av[1];
		map_process(filename, &game);
		str = game->map->map_test;
		map_wall_controller(game, str);
		check_valid_path(game);
		game->graphics = init_graphics();
		create_window(game);
		create_images(game);
		render_map(game);
		render_player(game);
		mlx_hook(game->graphics->mlx_win, KeyPress, KeyPressMask,
			key_input_handler, game);
		mlx_hook(game->graphics->mlx_win, 17, 1 << 17L, close_window, game);
		mlx_loop(game->graphics->mlx);
	}
	else
		safe_exit(NULL, "Too few argument");
}
