#include "so_long.h"
#include <stdlib.h>
#include <fcntl.h>

void	map_loader(char *filename, t_game *game)
{
	int k;
	char *tmp;
	int fd;

	k = 0;
	fd = open(filename, O_RDONLY);
	if (fd <= -1)
		safe_exit(game, "File descriptor error");
	while((tmp = get_next_line(fd)) != NULL)
	{
		game->map->line++;
		free(tmp);
	}
	close(fd);
	game->map->map_test = malloc((game->map->line + 1) * sizeof(char *));
	if(!game->map->map_test)
		safe_exit(game, "Allocation error");
	fd = open(filename, O_RDONLY);
	if (fd <= -1)
		safe_exit(game, "File descriptor error");
	while((tmp = get_next_line(fd)) != NULL)
	{
		game->map->cols = ft_strlen(tmp);
		game->map->map_test[k] = malloc(game->map->cols + 1);
		if(!game->map->map_test[k])
			safe_exit(game, "Allocation error");
		ft_memcpy(game->map->map_test[k], tmp, game->map->cols);
		game->map->map_test[k][game->map->cols] = '\0';
		k++;
		free(tmp);
	}
	close(fd);
	game->map->map_test[k] = NULL;
}
