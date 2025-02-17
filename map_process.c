/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:27:09 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 09:10:28 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	map_line_calc(char *filename, t_game *game)
{
	char	*tmp;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd <= -1)
		safe_exit(game, "File descriptor error");
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		game->map->line++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
	game->map->map_test = malloc((game->map->line + 1) * sizeof(char *));
	if (!game->map->map_test)
		safe_exit(game, "Allocation error");
}

void	map_loader(char *filename, t_game *game)
{
	int		k;
	char	*tmp;
	int		fd;

	k = 0;
	map_line_calc(filename, game);
	fd = open(filename, O_RDONLY);
	if (fd <= -1)
		safe_exit(game, "File descriptor error");
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		game->map->cols = ft_strlen(tmp);
		game->map->map_test[k] = malloc(game->map->cols + 1);
		if (!game->map->map_test[k])
			safe_exit(game, "Allocation error");
		ft_memcpy(game->map->map_test[k], tmp, game->map->cols);
		game->map->map_test[k][game->map->cols] = '\0';
		k++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
	game->map->map_test[k] = NULL;
}
