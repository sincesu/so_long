/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saincesu <saincesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 02:06:56 by saincesu          #+#    #+#             */
/*   Updated: 2025/02/17 02:09:09 by saincesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

char	*get_next_line(int fd);
int		gnl_strlen(char *str);
int		dbl_strlen(char **str);
int		gnl_strchr(char *str, int c);
char	*gnl_strjoin(char *str, char *tmp);

#endif