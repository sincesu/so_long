/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:52:35 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 02:10:07 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ESC 65307

typedef enum e_direction
{
	UP = 119,
	DOWN = 115,
	LEFT = 97,
	RIGHT = 100
}	t_direction;

typedef struct s_graphics {
	void	*mlx;
	void	*mlx_win;
	void	*wall_img;
	void	*player_img;
	void	*collectible_img;
	void	*empty_img;
	void	*exit_img;
}	t_graphics;

typedef struct s_map
{
	char	**map_test;
	int		collectible;
	int		exit;
	int		start;
	int		wall;
	int		line;
	int		cols;
	int		player_line;
	int		player_col;
}	t_map;

typedef struct s_game
{
	t_map		*map;
	t_graphics	*graphics;
	int			move_count;
}	t_game;

void		mlx_free(t_graphics *graphics);
void		free_map(t_map *map);
void		safe_exit(t_game *game, char *msg);
void		free_visited(char **visited, int lines);
void		dfs(char **str, int *elements, int x, int y);
char		**init_visited(t_game *game);
void		check_valid_path(t_game *game);
int			ft_compare(char *s1, char *s2);
void		check_is_rect(t_game *game);
void		mini_controller(t_game *game, int l, int w);
void		map_value_controller(t_game *game);
void		map_wall_controller(t_game *game, char **str);
void		map_loader(char *filename, t_game *game);
t_game		*init_game(void);
t_map		*init_map(void);
t_graphics	*init_graphics(void);
void		filename_checker(char *str);
void		*load_image(t_game *game, char *path);
void		create_images(t_game *game);
void		create_window(t_game *game);
void		*get_image_by_tile(t_game *game, int tile);
void		render_map(t_game *game);
void		render_player(t_game *game);
void		set_player_position(t_map *map, int l, int c);
int			mov_player_if_valid(t_game *game, int new_line, int new_col);
int			process_key(int keycode, t_game *game);
void		print_move_count(int count);
int			is_collectible(t_game *game);
int			key_input_handler(int keycode, t_game *game);
int			close_window(t_game *game);

#endif