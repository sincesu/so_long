#include <stdio.h>
#include "so_long.h"
#include "libs/get_next_line/get_next_line.h"
#include "libs/minilibx-linux/mlx.h"
#include "libs/libft/libft.h"
#include <X11/X.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	mlx_free(t_graphics *graphics)
{
	if(graphics->collectible_img)
	{
		printf("Freeing collectible image\n");
		mlx_destroy_image(graphics->mlx, graphics->collectible_img);
	}
	if(graphics->empty_img)
	{
		printf("Freeing empty image\n");
		mlx_destroy_image(graphics->mlx, graphics->empty_img);
	}
	if(graphics->exit_img)
	{
		printf("Freeing exit image\n");
		mlx_destroy_image(graphics->mlx, graphics->exit_img);
	}
	if(graphics->player_img)
	{
		printf("Freeing player image\n");
		mlx_destroy_image(graphics->mlx, graphics->player_img);
	}
	if(graphics->wall_img)
	{
		printf("Freeing wall image\n");
		mlx_destroy_image(graphics->mlx, graphics->wall_img);
	}
	if(graphics->mlx_win)
	{
		printf("Destroying mlx window\n");
		mlx_destroy_window(graphics->mlx, graphics->mlx_win);
	}
	if(graphics->mlx)
	{
		printf("Destroying MLX display\n");
		mlx_destroy_display(graphics->mlx);
		free(graphics->mlx);
		printf("MLX freed\n");
	}

	printf("MLX free completed\n");
}

void	free_map(t_map *map)
{
	int i;

	i = 0;
	if (map->map_test)
	{
		while(map->map_test[i])
		{
			free(map->map_test[i]);
			i++;
		}
		free(map->map_test);
	}
	free(map);
}

void safe_exit(t_game *game, char *msg)
{
    printf("Safe exit started\n");
    
    if(game)
    {
        if(game->graphics)
        {
            printf("Freeing graphics\n");
            mlx_free(game->graphics);
            printf("Graphics MLX freed\n");
            free(game->graphics);
            printf("Graphics structure freed\n");
        }
        
        if(game->map)
        {
            printf("Freeing map\n");
            free_map(game->map);
            printf("Map freed\n");
        }
        
        printf("Freeing game structure\n");
        free(game);
        printf("Game freed\n");
    }
    
    ft_putendl_fd(msg, 1);
    printf("Exiting program\n");
    exit(0);
}

void	free_visited(int **visited, int lines)
{
	int i;

	i = 0;
	while(i < lines)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}


int dfs(char **str, int x, int y, int **visited, int *found_collectible, int *found_exit)
{
    if (str[x][y] == 'E')
    {
        *found_exit = 1;
    }
    if (str[x][y] == 'C')
    {
        *found_collectible = 1;
    }
    if (str[x][y] == '1' || visited[x][y])
        return 0;
    
    visited[x][y] = 1;
    
    dfs(str, x + 1, y, visited, found_collectible, found_exit);
    dfs(str, x - 1, y, visited, found_collectible, found_exit);
    dfs(str, x, y + 1, visited, found_collectible, found_exit);
    dfs(str, x, y - 1, visited, found_collectible, found_exit);
    
    return (*found_collectible && *found_exit);
}

int **init_visited(t_game *game)
{
    int **visited;
	int i;
	int j;

	visited = malloc(game->map->line * sizeof(int *));
	if(!visited)
		safe_exit(game, "Allocation error");
    i = 0;
    while (i < game->map->line)
    {
        visited[i] = malloc(game->map->cols * sizeof(int));
		if(!visited[i])
		{
			free_visited(visited, i);
			safe_exit(game, "Allocation error");
		}
        j = 0;
        while (j < game->map->cols)
        {
            visited[i][j] = 0;
            j++;
        }
        i++;
    }
    return (visited);
}

void check_valid_path(t_game *game)
{
    int i;
    int found_collectible;
    int found_exit;
    int **visited;

	found_collectible = 0;
	found_exit = 0;
	i = 0;
	visited = init_visited(game);

    dfs(game->map->map_test, game->map->player_line, game->map->player_col, 
		visited, &found_collectible, &found_exit);
    if (!found_collectible || !found_exit)
	{
		free_visited(visited, game->map->line);
        safe_exit(game, "unreachable map");
	}
	free_visited(visited, game->map->line);
}

int ft_compare(char *s1, char *s2)
{
	int i = 0;
	while(s1[i] || s2[i])
	{
		if(s1[i] == s2[i])
			i++;
		else
			return 0;
	}
	return 1;
}

void check_is_rect(t_game *game)
{
	int l;

	l = 0;
	while(game->map->map_test[l])
	{
		if(ft_strlen(game->map->map_test[l]) != game->map->cols)
			safe_exit(game, "Map is not rect");
		l++;
	}
}

void mini_controller(t_game *game, int l, int w)
{
	char c;

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
	else if(game->map->map_test[l][w] != '0' && game->map->map_test[l][w] != '1')
		safe_exit(game, "You can't use the different value for map");
}

void map_value_controller(t_game *game)
{
	int w;
	int l;

	l = 0;
	while (game->map->map_test[l]) //farklı value kontrolü
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
		safe_exit(game, "You must have one exit");
	if (game->map->collectible < 1)
	safe_exit(game, "You must have one or more collectible");
	if (game->map->start != 1)
	safe_exit(game, "You must have a one player");
}

void map_wall_controller(t_game *game, char **str)
{
	int l;
	int i;

	l = 0;
	while(str[l])
	{
		i = 0;
		while(str[l][i]) //6- 14
		{
			if (str[0][i] != '1' || str[l][0] != '1'
				|| str[l][game->map->cols - 1] != '1')
				safe_exit(game, "Check walls");
			if(l == game->map->line - 1)
			{
				while(str[l][i])
				{
					if(str[l][i] != '1')
						safe_exit(game, "Check walls");
					i++;
				}
			}
			else
				i++;
		}
		l++;
	}
}


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
	//if (game->map->line == 0)
	//	safe_exit(game, "Map file is empty");
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
	printf("Satır Sayısı: [%d]\n", game->map->line);
	printf("Sütun Sayısı: [%d]\n", game->map->cols);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if(!game)
		safe_exit(NULL, "Allocation error");
	game->map=NULL;
	game->graphics=NULL;
	game->move_count=1;
	return(game);
}

t_map	*init_map(void)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if(!map)
		safe_exit(NULL, "Allocation error");
	ft_memset(map, 0, sizeof(t_map));
	// map->map_test=NULL;
	// printf("[%d]\n", map->collectible);
	// printf("[%d]\n", map->exit);
	// printf("[%d]\n", map->start);
	// printf("[%d]\n", map->wall);
	// printf("[%d]\n", map->line);
	// printf("[%d]\n", map->cols);
	// printf("[%d]\n", map->player_col);
	// printf("[%d]\n", map->player_line);
	// printf("[%s]\n", map->map_test);

	// map->collectible=0;
	// map->exit=0;
	// map->start=0;
	// map->wall=0;
	// map->line=0;
	// map->cols=0;
	// map->player_col=0;
	// map->player_line=0;
	return (map);
}

t_graphics *init_graphics(void)
{
	t_graphics *graphics;

	graphics = malloc(sizeof(t_graphics));
	if (!graphics)
		safe_exit(NULL, "Allocation error");
	
	printf("Initializing graphics pointers...\n");
	ft_memset(graphics, 0, sizeof(graphics));
	// graphics->mlx = NULL;
	// graphics->mlx_win = NULL;
	// graphics->wall_img = NULL;
	// graphics->player_img = NULL;
	// graphics->collectible_img = NULL;
	// graphics->empty_img = NULL;
	// graphics->exit_img = NULL;
	printf("All graphics pointers initialized to NULL\n");
	return (graphics);
}


void	filename_checker(char *str)
{
	char *tmp;
	tmp = ft_strchr(str, '.');
	if(!tmp)
		safe_exit(NULL, "map file has no .");
	if(!ft_compare(tmp, ".ber"))
		safe_exit(NULL, "map file extension must be ber");
}

void	*load_image(t_game *game, char *path)
{
	int	h;
	int	w;
	void *img;

	img = mlx_xpm_file_to_image(game->graphics->mlx, path, &w, &h);
	if(!img)
		safe_exit(game, "Mlx file has not right name");
	return (img);
}

void	create_images(t_game *game)
{
	game->graphics->wall_img = load_image(game, "./textures/wall.xpm");
	printf("wall image loaded\n");
	game->graphics->player_img = load_image(game, "./textures/player.xpm");
	printf("player image loaded\n");
	game->graphics->collectible_img = load_image(game, "./textures/collectible.xpm");
	printf("collectible image loaded\n");
	game->graphics->empty_img = load_image(game, "./textures/empty.xpm");
	printf("empty image loaded\n");
	game->graphics->exit_img = load_image(game, "./textures/exit.xpm");
	printf("exit image loaded\n");
}

void create_window(t_game *game)
{
	game->graphics->mlx = mlx_init();
	if(!game->graphics->mlx)
		safe_exit(game, "Failed to run mlx library");
	game->graphics->mlx_win = mlx_new_window(game->graphics->mlx,
		game->map->cols * 64, game->map->line * 64, "so_long");
}

void *get_image_by_tile(t_game *game, int tile)
{
    void *img;

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


void	render_map(t_game *game)
{
	int	col;
	int	line;
	void	*img;

	col = 0;
	while(game->map->map_test[col])
	{
		line = 0;
		while(game->map->map_test[col][line])
		{
			img = get_image_by_tile(game, game->map->map_test[col][line]);
			mlx_put_image_to_window(game->graphics->mlx,
			game->graphics->mlx_win, img , line * 64, col * 64);
			line++;
		}
		col++;
	}
}

void	render_player(t_game *game)
{
	if (game->map->map_test[game->map->player_line][game->map->player_col] == 'E')
	{
		mlx_put_image_to_window(game->graphics->mlx, game->graphics->mlx_win,
			game->graphics->exit_img, game->map->player_col * 64,
			game->map->player_line * 64);
	}
	mlx_put_image_to_window(game->graphics->mlx, game->graphics->mlx_win,
		game->graphics->player_img, game->map->player_col * 64,
		game->map->player_line * 64);
}

void	set_player_position(t_map *map, int l, int c)
{
	map->player_line = l;
	map->player_col = c;
}

int	mov_player_if_valid(t_game *game, int new_line, int new_col)
{
	if(game->map->map_test[new_line][new_col] == '1')
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
 
void	print_move_count(int count)
{
	ft_putstr_fd("Move count: ", 1);
	ft_putnbr_fd(count, 1);
	ft_putchar_fd('\n', 1);
}

int is_collectible(t_game *game)
{
	return (game->map->map_test[game->map->player_line][game->map->player_col] == 'C');
}

int	key_input_handler(int keycode, t_game *game)
{
	if (keycode == ESC)
		safe_exit(game, "Program finished");
	if(!process_key(keycode, game))
		return (0);
	if (is_collectible(game))
	{
		game->map->map_test[game->map->player_line][game->map->player_col] = '0';
		game->map->collectible--;
	}
	print_move_count(game->move_count++);
	if (game->map->map_test[game->map->player_line][game->map->player_col] == 'E'
		&& game->map->collectible == 0)
		{
		printf("Exit reached! Collectibles: %d\n", game->map->collectible);
		safe_exit(game, "Program finished");
		}
	render_map(game);
	render_player(game);
	return (0);
}

int close_window(t_game *game)
{
	safe_exit(game, "Program finished");
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
	t_game *game;
	int i;
	char *filename;
	char **str;

	game = NULL;
	i = 0;
	filename = av[1];
	filename_checker(av[1]);
	game = init_game(); //OK
	if(!game)
		safe_exit(NULL, "Allocation error");
	game->map = init_map(); //OK
	if(!game->map)
		safe_exit(game, "Allocation error");
	map_loader(filename, game);
	check_is_rect(game);
	map_value_controller(game);
	str = game->map->map_test;
	map_wall_controller(game, str);
	check_valid_path(game);

	game->graphics = init_graphics(); //OK
	if(!game->graphics)
		safe_exit(game, "Allocation error");
	create_window(game);
	create_images(game);
	render_map(game);
	render_player(game);

	mlx_hook(game->graphics->mlx_win, KeyPress, KeyPressMask, key_input_handler, game); //bak
	mlx_hook(game->graphics->mlx_win, 17, 1 << 17L, close_window, game);
	mlx_loop(game->graphics->mlx);
	}
	else
		safe_exit(NULL, "Too few argument");
}