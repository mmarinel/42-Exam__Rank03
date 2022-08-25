/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:14:11 by earendil          #+#    #+#             */
/*   Updated: 2022/08/25 21:58:04 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//*************************************************************************************************/
//*          this file is a compressed version of the three files present in this directory      */
//*          (DO NOT COMPILE THIS FILE!-instead feed it to the "Glagan" Tester)                 */
//**********************************************************************************************/

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
float	my_abs(float nbr);
size_t	ft_strlen(char const *str);
void	*ft_memset(void *s, int c, size_t len);
void	print_matrix(char **matrix, size_t rows, size_t columns);
void	free_matrix(char **matrix, size_t rows);
float	distance(t_point a, t_point b);
void	rectangle_set_edges(t_rectangle *rect);
int		is_in_rectangle(t_point p, t_rectangle rect);
t_point	get_closest_border_pt(t_rectangle rect, t_point p);


#endif/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micropaint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:13:33 by earendil          #+#    #+#             */
/*   Updated: 2022/08/25 21:39:55 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	micropaint(FILE *fhandle);
static int	zone_init(t_zone *drawZone, FILE *fhandle);
static void	draw_rectangle(t_rectangle rect, t_zone *drawZone);
//* end of static declarations

int main(int argc, char const *argv[])
{
	FILE	*fhandle;

	if (argc == 2)
	{
		fhandle = fopen(argv[1], "r");
		if (NULL == fhandle)
		{
			write(STDOUT_FILENO, IO_ERR, ft_strlen(IO_ERR));
			return (1);
		}
		else
			return (micropaint(fhandle));
	}
	else
	{
		write(STDOUT_FILENO, ARG_ERR, ft_strlen(ARG_ERR));
		return (1);
	}
}

static int	micropaint(FILE *fhandle)
{
	t_zone	drawZone;
	
	if (zone_init(&drawZone, fhandle))
		return (1);
	else
	{
		t_rectangle	rectangle;
		int			scan_ret;
		while (1)
		{
			scan_ret = fscanf(fhandle, "\n%c %f %f %f %f %c", &rectangle.type,
						&rectangle.top_left.x, &rectangle.top_left.y,
						&rectangle.width, &rectangle.height,
						&rectangle.mark);
			if (scan_ret == EOF)
			{
				break ;
			}
			if (scan_ret != 6 || rectangle.width <= 0 || rectangle.height <= 0
				|| (rectangle.type != 'R' && rectangle.type != 'r'))
			{
				write(STDOUT_FILENO, IO_ERR, ft_strlen(IO_ERR));
				free_matrix(drawZone.map, drawZone.height);
				return (1);
			}
			draw_rectangle(rectangle, &drawZone);
		}
		print_matrix(drawZone.map, drawZone.height, drawZone.width);
		free_matrix(drawZone.map, drawZone.height);
		return (0);
	}
}

static int	zone_init(t_zone *drawZone, FILE *fhandle)
{
	if (3 != fscanf(fhandle, "%d %d %c",
			&drawZone->width, &drawZone->height, &drawZone->b_char)
		|| ( drawZone->width <= 0 || drawZone->width > 300)
		|| ( drawZone->height <= 0 || drawZone->height > 300))
	{
		write(STDOUT_FILENO, IO_ERR, ft_strlen(IO_ERR));
		return (1);
	}
	else
	{
		drawZone->map = (char **) malloc(drawZone->height * sizeof(char *));
		if (NULL == drawZone->map)
			return (1);
		for (int i = 0; i < drawZone->height; i++)
		{
			drawZone->map[i] = (char *) malloc(drawZone->width * sizeof(char));
			if (NULL == drawZone->map[i])
			{
				free_matrix(drawZone->map, i);
				return (1);
			}
			ft_memset(drawZone->map[i], drawZone->b_char, drawZone->width);
		}
		return (0);
	}
}

static void	draw_rectangle(t_rectangle rect, t_zone *drawZone)
{
	t_point	p;

	if (rect.mark == '\n')
		rect.mark = drawZone->b_char;
	rectangle_set_edges(&rect);
	for (int y = 0; y < drawZone->height; y++)
		for (int x = 0; x < drawZone->width; x++)
		{
			p.x = x;
			p.y = y;
			if (is_in_rectangle(p, rect))
			{
				if (rect.type == 'R'
					|| distance(p, get_closest_border_pt(rect, p)) < 1)
					drawZone->map[y][x] = rect.mark;
			}
		}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:24:54 by earendil          #+#    #+#             */
/*   Updated: 2022/08/25 21:47:18 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	ft_strlen(char const *str)
{
	size_t	i = 0;

	if (NULL == str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	for (size_t i = 0; i < len; i++)
		ptr[i] = (unsigned char)c;
	return (s);
}

void	print_matrix(char **matrix, size_t rows, size_t columns)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
			write(STDOUT_FILENO, &matrix[i][j], sizeof(char));
		write(STDOUT_FILENO, "\n", sizeof(char));
	}
}

void	free_matrix(char **matrix, size_t rows)
{
	for (size_t i = 0; i < rows; i++)
			free(matrix[i]);
	free(matrix);
}

float	distance(t_point a, t_point b)
{
	return (sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2)));
}

void	rectangle_set_edges(t_rectangle *rect)
{
	rect->top_right.x = my_floor(rect->top_left.x + (rect->width));
	rect->top_right.y = rect->top_left.y;

	rect->bottom_right.x = my_floor(rect->top_left.x + (rect->width));
	rect->bottom_right.y = my_floor(rect->top_left.y + (rect->height));

	rect->bottom_left.x = rect->top_left.x;
	rect->bottom_left.y = rect->bottom_right.y;

	//* updating top left //
	rect->top_left.x = my_ceil(rect->top_left.x);
	rect->top_left.y = my_ceil(rect->top_left.y);
// 	printf("top left: y: %f, x: %f\n
// top right: y: %f, x: %f\n
// bottom left: y: %f, x: %f\n
// bottom right: y: %f, x: %f\n",
// 			rect->top_left.y, rect->top_left.x,
// 			rect->top_right.y, rect->top_right.x,
// 			rect->bottom_left.y, rect->bottom_left.x,
// 			rect->bottom_right.y, rect->bottom_right.x);
}

int	is_in_rectangle(t_point p, t_rectangle rect)
{
	return ((p.x >= rect.top_left.x && p.x <= rect.bottom_right.x)
			&& (p.y >= rect.top_left.y && p.y <= rect.bottom_right.y));
}

t_point	get_closest_border_pt(t_rectangle rect, t_point p)
{
	t_point	closest;
	float	border_closest_x;
	float	border_closest_y;

	if (my_abs(p.x - rect.top_left.x) < my_abs(p.x - rect.top_right.x))
		border_closest_x = rect.top_left.x;
	else
		border_closest_x = rect.top_right.x;

	if (my_abs(p.y - rect.top_left.y) < my_abs(p.y - rect.bottom_left.y))
		border_closest_y = rect.top_left.y;
	else
		border_closest_y = rect.bottom_left.y;

	if (my_abs(p.x - border_closest_x) < my_abs(p.y - border_closest_y))
	{
		closest.x = border_closest_x;
		closest.y = p.y;
	}
	else
	{
		closest.y = border_closest_y;
		closest.x = p.x;
	}
	return (closest);
}

float	my_abs(float nbr)
{
	if (nbr >= 0)
		return (nbr);
	else
		return (-nbr);
}

int	my_ceil(float nbr)
{
	if (nbr >= 0)
	{
		if ((int)nbr < nbr)
			return ((int)nbr + 1);
		else
			return ((int)nbr);
	}
	else
	{
		return ((int)nbr);
	}
}

int	my_floor(float nbr)
{
	if (nbr >= 0)
	{
		return ((int)nbr);
	}
	else
	{
		return ((int)nbr - 1);
	}
}
