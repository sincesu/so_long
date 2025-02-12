/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:42:22 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/12 14:45:59 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		safe_exit(NULL, "Allocation error");
	game->map = NULL;
	game->graphics = NULL;
	game->move_count = 1;
	return (game);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		safe_exit(NULL, "Allocation error");
	ft_memset(map, 0, sizeof(t_map));
	return (map);
}

t_graphics	*init_graphics(void)
{
	t_graphics	*graphics;

	graphics = malloc(sizeof(t_graphics));
	if (!graphics)
		safe_exit(NULL, "Allocation error");
	ft_memset(graphics, 0, sizeof(graphics));
	return (graphics);
}
