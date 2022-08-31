/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipaint.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:25:58 by earendil          #+#    #+#             */
/*   Updated: 2022/08/31 19:20:52 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PAINT_H
# define MINI_PAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# include "math.h"

# define ARG_ERR "Error: argument" "\n"
# define IO_ERR "Error: Operation file corrupted" "\n"

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_region
{
	char	b_char;
	int		width;
	int		height;
	char	**map;
}	t_region;

typedef struct s_circle
{
	char	type;
	t_point	center;
	float	radius;
	char	mark;
}	t_circle;

//* utils

size_t	ft_strlen(char const *str);

float	distance(t_point a, t_point b);

	//* map

void	free_matrix(char **m, int rows);
void	print_matrix(char **m, int rows, int columns);


	//* circle
int		is_in_circle(t_point p, t_circle circle);
float	distance_from_circumference(t_point p, t_circle circle);

#endif