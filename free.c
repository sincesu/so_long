/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:42:02 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 04:35:08 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>

void	mlx_free(t_graphics *graphics)
{
	if (graphics->collectible_img)
		mlx_destroy_image(graphics->mlx, graphics->collectible_img);
	if (graphics->empty_img)
		mlx_destroy_image(graphics->mlx, graphics->empty_img);
	if (graphics->exit_img)
		mlx_destroy_image(graphics->mlx, graphics->exit_img);
	if (graphics->player_img)
		mlx_destroy_image(graphics->mlx, graphics->player_img);
	if (graphics->wall_img)
		mlx_destroy_image(graphics->mlx, graphics->wall_img);
	if (graphics->mlx_win)
		mlx_destroy_window(graphics->mlx, graphics->mlx_win);
	if (graphics->mlx)
	{
		mlx_destroy_display(graphics->mlx);
		free(graphics->mlx);
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->map_test)
	{
		while (map->map_test[i])
		{
			free(map->map_test[i]);
			i++;
		}
		free(map->map_test);
	}
	free(map);
}

void	safe_exit(t_game *game, char *msg)
{
	if (game)
	{
		if (game->graphics)
		{
			mlx_free(game->graphics);
			free(game->graphics);
		}
		if (game->map)
			free_map(game->map);
		free(game);
	}
	ft_putendl_fd(msg, 1);
	exit(0);
}

void	free_visited(char **visited, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
