#include <stdio.h>
#include "so_long.h"
#include "libs/get_next_line/get_next_line.h"
#include "libs/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void find_player(char **map, int *x, int *y)
{
    int i, j;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
            {
                *x = i;
                *y = j;
                return;
            }
            j++;
        }
        i++;
    }
}

int dfs(char **map, int x, int y, int **visited, int *found_collectible)
{
    if (map[x][y] == 'E')
        return (1);
    if (map[x][y] == 'C')
    {
        *found_collectible = 1;
        return (1);
    }
    if (map[x][y] == '1' || visited[x][y])
        return (0);
    visited[x][y] = 1;
    if (dfs(map, x + 1, y, visited, found_collectible)
        || dfs(map, x - 1, y, visited, found_collectible)
        || dfs(map, x, y + 1, visited, found_collectible)
        || dfs(map, x, y - 1, visited, found_collectible))
        return (1);
    return (0);
}

int **init_visited_matrix(int rows, int cols)
{
    int **visited, i, j;
    visited = malloc(rows * sizeof(int *));
    if (!visited)
        return (NULL);
    i = 0;
    while (i < rows)
    {
        visited[i] = malloc(cols * sizeof(int));
        if (!visited[i])
            return (NULL);
        j = 0;
        while (j < cols)
            visited[i][j++] = 0;
        i++;
    }
    return (visited);
}

void free_visited_matrix(int **visited, int rows)
{
    int i = 0;
    while (i < rows)
        free(visited[i++]);
    free(visited);
}

void check_valid_path(char **map, t_map *loc)
{
    int x, y, **visited, found_collectible = 0;
    find_player(map, &x, &y);
    visited = init_visited_matrix(loc->rows, loc->cols);
    if (!visited)
        error(loc);
    if (!dfs(map, x, y, visited, &found_collectible))
    {
        free_visited_matrix(visited, loc->rows);
        error(loc);
    }
    if (!found_collectible)
    {
        free_visited_matrix(visited, loc->rows);
        error(loc);
    }
    free_visited_matrix(visited, loc->rows);
}

void init_null(t_map *loc)
{
    loc->collectible = 0;
    loc->empty = 0;
    loc->exit = 0;
    loc->start = 0;
    loc->wall = 0;
    loc->rows = 0;
    loc->cols = 0;
}

char **map_loader(char *filename, t_map *loc)
{
    int fd, k = 0;
    char **map, *tmp;
    loc->rows = 0;
    fd = open(filename, O_RDONLY);
    while (get_next_line(fd) != NULL)
        loc->rows++;
    close(fd);
    map = malloc((loc->rows + 1) * sizeof(char *));
    if (!map)
        error(loc);
    fd = open(filename, O_RDONLY);
    while ((tmp = get_next_line(fd)) != NULL)
    {
        if (k == 0)
            loc->cols = ft_strlen(tmp);
        map[k] = malloc(loc->cols + 1);
        ft_memcpy(map[k], tmp, loc->cols);
        map[k][loc->cols] = '\0';
        k++;
        free(tmp);
    }
    map[k] = NULL;
    close(fd);
    return (map);
}

void error(t_map *loc)
{
    free(loc);
    write(2, "Error\n", 6);
    exit(1);
}

void filename_checker(char *str)
{
    char *tmp = ft_strchr(str, '.');
    if (!tmp || !ft_compare(tmp, ".ber"))
        error(NULL);
}

int main(int ac, char **av)
{
    t_map *loc;
    char **map;
    if (ac != 2)
        error(NULL);
    filename_checker(av[1]);
    loc = malloc(sizeof(t_map));
    if (!loc)
        return (1);
    init_null(loc);
    map = map_loader(av[1], loc);
    map_controller(map, loc);
    map_controller2(map, loc);
    check_valid_path(map, loc);
    for (int i = 0; map[i]; i++)
        printf("[%s]\n", map[i]);
    return (0);
}
