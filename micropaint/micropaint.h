/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micropaint.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:14:11 by earendil          #+#    #+#             */
/*   Updated: 2022/08/25 14:52:04 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROPAINT_H
# define MICROPAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <math.h>

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
	char	b_char;
	char	**map;
}	t_zone;

typedef struct s_rectangle
{
	char	type;
	float	width;
	float	height;
	char	mark;
	t_point	top_left;
	t_point	top_right;
	t_point	bottom_left;
	t_point	bottom_right;
}	t_rectangle;

//* utils
int		my_ceil(float nbr);
int		my_floor(float nbr);
size_t	ft_strlen(char const *str);
void	*ft_memset(void *s, int c, size_t len);
void	print_matrix(char **matrix, size_t rows, size_t columns);
void	free_matrix(char **matrix, size_t rows);
float	distance(t_point a, t_point b);
void	rectangle_fill_points(t_rectangle *rect);
int		is_in_rectangle(t_point p, t_rectangle rect);
t_point	get_closest_border_pt(t_rectangle rect, t_point p);


#endif