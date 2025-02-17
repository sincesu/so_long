/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:53:00 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 02:57:28 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "minilibx-linux/mlx.h"

void	create_window(t_game *game)
{
	game->graphics->mlx = mlx_init();
	if (!game->graphics->mlx)
		safe_exit(game, "Failed to run mlx library");
	game->graphics->mlx_win = mlx_new_window(game->graphics->mlx,
			game->map->cols * 64, game->map->line * 64, "so_long");
}

void	create_images(t_game *game)
{
	game->graphics->wall_img = load_image(game, "./textures/wall.xpm");
	game->graphics->player_img = load_image(game, "./textures/player.xpm");
	game->graphics->collectible_img = load_image(game,
			"./textures/collectible.xpm");
	game->graphics->empty_img = load_image(game, "./textures/empty.xpm");
	game->graphics->exit_img = load_image(game, "./textures/exit.xpm");
}

void	render_map(t_game *game)
{
	int		col;
	int		line;
	void	*img;

	line = 0;
	while (game->map->map_test[line])
	{
		col = 0;
		while (game->map->map_test[line][col])
		{
			img = get_image_by_tile(game, game->map->map_test[line][col]);
			mlx_put_image_to_window(game->graphics->mlx,
				game->graphics->mlx_win, img, col * 64, line * 64);
			col++;
		}
		line++;
	}
}

void	render_player(t_game *game)
{
	if (game->map->map_test[game->map->player_line]
		[game->map->player_col] == 'E')
	{
		mlx_put_image_to_window(game->graphics->mlx, game->graphics->mlx_win,
			game->graphics->exit_img, game->map->player_col * 64,
			game->map->player_line * 64);
	}
	mlx_put_image_to_window(game->graphics->mlx, game->graphics->mlx_win,
		game->graphics->player_img, game->map->player_col * 64,
		game->map->player_line * 64);
}
