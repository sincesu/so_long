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
    void    *mlx;
    void    *mlx_win;
    void    *wall_img;
    void    *player_img;
    void    *collectible_img;
    void    *empty_img;
    void    *exit_img;
}   t_graphics;

typedef struct s_map
{
    char **map_test;
    int collectible;
    int exit;
    int start;
    int wall;
    int line;  // Satır sayısı
    int cols;  // Sütun sayısı
    int player_line;
    int player_col;
} t_map;

typedef struct s_game
{
    t_map   *map;
    t_graphics  *graphics;
    int     move_count;
} t_game;


#endif