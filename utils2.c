/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:32:47 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 09:11:06 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "minilibx-linux/mlx.h"
#include <stdlib.h>

int	close_window(t_game *game)
{
	safe_exit(game, "Program finished");
	return (0);
}

void	*load_image(t_game *game, char *path)
{
	int		h;
	int		w;
	void	*img;

	img = mlx_xpm_file_to_image(game->graphics->mlx, path, &w, &h);
	if (!img)
		safe_exit(game, "Mlx file has not right name");
	return (img);
}

void	*get_image_by_tile(t_game *game, int tile)
{
	void	*img;

	img = NULL;
	if (tile == '1')
		img = game->graphics->wall_img;
	else if (tile == '0' || tile == 'P')
		img = game->graphics->empty_img;
	else if (tile == 'E')
		img = game->graphics->exit_img;
	else if (tile == 'C')
		img = game->graphics->collectible_img;
	if (!img)
		safe_exit(game, "image could not be suppressed");
	return (img);
}
