/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipaint.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:25:58 by earendil          #+#    #+#             */
/*   Updated: 2022/08/26 11:17:55 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PAINT_H
# define MINI_PAINT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "math.h"

# define ARG_ERR "Error: argument" "\n"
# define IO_ERR "Error: Operation file corrupted" "\n"

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_zone
{
	int		width;
	int		height;
	char	**map;
	char	b_char;
}	t_zone;

typedef struct s_circle
{
	char	type;
	t_point	center;
	float	radius;
	char	mark;
}	t_circle;

//* utils
size_t	ft_strlen(char const *str);
void	free_matrix(char **m, int rows);
void	print_matrix(char **m, int rows, int columns);
float	my_abs(float nbr);
float	distance(t_point a, t_point b);
int		is_in_circle(t_point p, t_circle circle);
float	circumference_distance(t_circle circle, t_point p);

#endif