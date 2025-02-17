/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:44:09 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 02:59:51 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

char	**init_visited(t_game *game)
{
	char	**visited;
	int		i;
	int		j;

	visited = malloc(game->map->line * sizeof(char *));
	if (!visited)
		safe_exit(game, "Allocation error");
	i = 0;
	while (i < game->map->line)
	{
		visited[i] = malloc(game->map->cols * sizeof(char));
		if (!visited[i])
		{
			free_visited(visited, i);
			safe_exit(game, "Allocation error");
		}
		j = 0;
		while (j < game->map->cols)
		{
			visited[i][j] = game->map->map_test[i][j];
			j++;
		}
		i++;
	}
	return (visited);
}

void	dfs(char **str, int *elements, int x, int y)
{
	if (str[x][y] == '1' || *elements == 0)
		return ;
	if (str[x][y] == 'E' || str[x][y] == 'C')
		*elements -= 1;
	str[x][y] = '1';
	dfs(str, elements, x, y + 1);
	dfs(str, elements, x, y - 1);
	dfs(str, elements, x + 1, y);
	dfs(str, elements, x - 1, y);
}

void	check_valid_path(t_game *game)
{
	int		elements;
	char	**visited;

	visited = init_visited(game);
	elements = game->map->collectible + game->map->exit;
	dfs(visited, &elements, game->map->player_line, game->map->player_col);
	if (elements != 0)
	{
		free_visited(visited, game->map->line);
		safe_exit(game, "unreachable map");
	}
	free_visited(visited, game->map->line);
}
