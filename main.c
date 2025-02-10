#include <stdio.h>
#include "so_long.h"
#include "libs/get_next_line/get_next_line.h"
#include "libs/minilibx-linux/mlx.h"
#include "libs/libft/libft.h"
#include <X11/X.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	safe_exit(t_game *game, char *msg)
{
	if(game)
	{
	if(game->graphics)
	{
		free(game->graphics);
		mlx_free(game->graphics);
	}
	if(game->map)
		free(game->map);
	free(game);
	}
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(msg, 1);
	exit(1);
}

void	mlx_free(t_graphics *graphics)
{
	if(graphics->mlx_win)
		mlx_destroy_window(graphics->mlx, graphics->mlx_win);
	if(graphics->collectible_img)
		mlx_destroy_image(graphics->mlx, graphics->collectible_img);
	if(graphics->empty_img)
		mlx_destroy_image(graphics->mlx, graphics->empty_img);
	if(graphics->exit_img)
		mlx_destroy_image(graphics->mlx, graphics->exit_img);
	if(graphics->player_img)
		mlx_destroy_image(graphics->mlx, graphics->player_img);
	if(graphics->wall_img)
		mlx_destroy_image(graphics->mlx, graphics->wall_img);
	if(graphics->player_up_img)
		mlx_destroy_image(graphics->mlx, graphics->player_up_img);
	if(graphics->player_down_img)
		mlx_destroy_image(graphics->mlx, graphics->player_down_img);
	if(graphics->player_left_img)
		mlx_destroy_image(graphics->mlx, graphics->player_left_img);
	if(graphics->player_right_img)
		mlx_destroy_image(graphics->mlx, graphics->player_right_img);
	if(graphics->mlx)
		mlx_destroy_display(graphics->mlx);
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
			safe_exit(game, "Allocation error");
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
        safe_exit(game, "unreachable map");
    while (i < game->map->line)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
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
			safe_exit(game->map, "Map is not rect");
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
		while(str[l][i])
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
	fd = open(filename, 02);
	if (fd <= -1)
		safe_exit(game->map, "File descriptor error");
	while(get_next_line(fd) != NULL)
		game->map->line++;
	close(fd);
	game->map->map_test = malloc((game->map->line + 1) * sizeof(char *));
	fd = open(filename, 02);
	if (fd <= -1)
		safe_exit(game, "File descriptor error");
	while((tmp = get_next_line(fd)) != NULL)
	{
		game->map->cols = ft_strlen(tmp);
		game->map->map_test[k] = malloc(game->map->cols + 1);
		ft_memcpy(game->map->map_test[k], tmp, game->map->cols);
		game->map->map_test[k][game->map->cols] = '\0';
		k++;
		free(tmp);
	}
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
	game->graphics=NULL;
	game->map=NULL;
	game->move_count=1;
	return(game);
}

t_map	*init_map(void)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if(!map)
		safe_exit(NULL, "Allocation error");
	map->collectible=0;
	map->exit=0;
	map->start=0;
	map->wall=0;
	map->line=0;
	map->cols=0;
	map->player_col=0;
	map->player_line=0;
	return (map);
}

t_graphics *init_graphics(void)
{
	t_graphics *graphics;

	graphics = malloc(sizeof(t_graphics));
	if (!graphics)
		safe_exit(NULL, "Allocation error");
	graphics->mlx = NULL;
	graphics->mlx_win = NULL;
	graphics->wall_img = NULL;
	graphics->player_img = NULL;
	graphics->collectible_img = NULL;
	graphics->empty_img = NULL;
	graphics->exit_img = NULL;
	graphics->player_up_img = NULL;
	graphics->player_down_img = NULL;
	graphics->player_left_img = NULL;
	graphics->player_right_img = NULL;
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
	game->graphics->wall_img = load_image(game, "./images/wall.xpm");
	game->graphics->player_img = load_image(game, "./images/player.xpm");
	game->graphics->collectible_img = load_image(game, "./images/collectible.xpm");
	game->graphics->empty_img = load_image(game, "./images/empty.xpm");
	game->graphics->exit_img = load_image(game, "./images/exit.xpm");
	game->graphics->player_up_img = load_image(game, "./images/player_up.xpm");
	game->graphics->player_down_img = load_image(game, "./images/player_down.xpm");
	game->graphics->player_left_img = load_image(game, "./images/player_left.xpm");
	game->graphics->player_right_img = load_image(game, "./images/player_right.xpm");
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

    return img;
}


void	render_map(t_game *game)
{
	int	line;
	int	col;
	void	*img;

	line = 0;
	while(game->map->map_test[line])
	{
		col = 0;
		while(game->map->map_test[line][col])
		{
			img = get_image_by_tile(game, game->map->map_test[line][col]);
			mlx_put_image_to_window(game->graphics->mlx,
			game->graphics->mlx_win, img , line * 64, col * 64);
			col++;
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

int process_key_landr(int keycode, t_game *game)
{
	int	new_col;

	new_col = game->map->player_col;

	if (keycode == LEFT)
	{
		game->graphics->player_img = game->graphics->player_left_img;
		new_col--;
	}
	else if (keycode == RIGHT)
	{
		game->graphics->player_img = game->graphics->player_right_img;
		new_col++;
	}

	return(new_col);
}

int	process_key(int keycode, t_game *game)
{
	int	new_line;
	int	new_col;

	new_line = game->map->player_line;
	new_col = game->map->player_col;
	if (keycode == UP)
	{
		game->graphics->player_img = game->graphics->player_up_img;
		new_line--;
	}
	else if (keycode == DOWN)
	{
		game->graphics->player_img = game->graphics->player_down_img;
		new_line++;
	}
	else if (keycode == LEFT)
		new_col = process_key_landr(keycode, game);
	else if (keycode == RIGHT)
		new_col = process_key_landr(keycode, game);
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
		exit(1);
	//burda kaldım
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
		exit(1);
	render_map(game);
	render_player(game);
	return 0;
}

int close_window()
{
	exit(1);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
	t_game *game;
	int i;
	char *filename;
	char **str;


	i = 0;
	filename = av[1];
	filename_checker(av[1]);
	game = init_game();
	if(!game)
		safe_exit(NULL, "Allocation error");
	game->map = init_map();
	if(!game->map)
		safe_exit(game, "Allocation error");
	map_loader(filename, game);
	check_is_rect(game);
	map_value_controller(game);
	str = game->map->map_test;
	map_wall_controller(game, str);
	check_valid_path(game);

	game->graphics = init_graphics();
	if(!game->graphics)
		safe_exit(game, "Allocation error");
	create_window(game);
	create_images(game);
	render_map(game);
	render_player(game);

	mlx_hook(game->graphics->mlx_win, KeyPress, KeyPressMask, key_input_handler, game); //bak


	}
	else
		safe_exit(NULL, "Too few argument");
	// int i = 0;
	// char *filename = av[1];
	
	// filename_checker(av[1]);
 
	// map_loader(filename, game->map); //map okuma, char **'a atama, satır sütun sayısı bulma
	// check_is_rect(game->map);
	// map_controller(game->map);
	// map_controller2(game->map);
	// check_valid_path(game->map);

	// create_window(game);
	// create_images(game->graphics);
	// render_map(game);
	// render_player(game);
	// mlx_hook(game->graphics->mlx_win, KeyPress, KeyPressMask, key_input_handler, game);
	// mlx_hook(game->graphics->mlx_win, 17, 1 << 17L, close_window, game);
	// mlx_loop(game->graphics->mlx);

	// while(game->map->map_test[i])
	// {
	// 	printf("[%s]\n", game->map->map_test[i++]);
	// }
}