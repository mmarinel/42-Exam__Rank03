/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:24:54 by earendil          #+#    #+#             */
/*   Updated: 2022/08/31 18:54:16 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micropaint.h"

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
	rect->top_right.x = ft_floor(rect->top_left.x + (rect->width));
	rect->top_right.y = ft_ceil(rect->top_left.y);

	rect->bottom_right.x = ft_floor(rect->top_left.x + (rect->width));
	rect->bottom_right.y = ft_floor(rect->top_left.y + (rect->height));

	rect->bottom_left.x = ft_ceil(rect->top_left.x);
	rect->bottom_left.y = rect->bottom_right.y;

	//* updating top left //
	rect->top_left.x = ft_ceil(rect->top_left.x);
	rect->top_left.y = ft_ceil(rect->top_left.y);
}

int	is_in_rectangle(t_point p, t_rectangle rect)
{
	return (
		(p.x >= rect.top_left.x && p.x <= rect.bottom_right.x)
		&&
		(p.y >= rect.top_left.y && p.y <= rect.bottom_right.y)
	);
}

t_point	get_closest_border_pt(t_rectangle rect, t_point p)
{
	t_point	closest;
	float	border_closest_x;
	float	border_closest_y;

	if (ft_abs(p.x - rect.top_left.x) < ft_abs(p.x - rect.top_right.x))
		border_closest_x = rect.top_left.x;
	else
		border_closest_x = rect.top_right.x;

	if (ft_abs(p.y - rect.top_left.y) < ft_abs(p.y - rect.bottom_left.y))
		border_closest_y = rect.top_left.y;
	else
		border_closest_y = rect.bottom_left.y;

	if (ft_abs(p.x - border_closest_x) < ft_abs(p.y - border_closest_y))
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

float	ft_abs(float nbr)
{
	if (nbr >= 0)
		return (nbr);
	else
		return (-nbr);
}

int	ft_ceil(float nbr)
{
	if (nbr >= 0)
	{
		if (nbr > (int)nbr)
			return ((int)nbr + 1);
		else
			return ((int)nbr);
	}
	else
	{
		return ((int)nbr);
	}
}

int	ft_floor(float nbr)
{
	if (nbr >= 0)
	{
		return ((int)nbr);
	}
	else
	{
		if (nbr < (int)nbr)
			return ((int)nbr - 1);
		else
			return ((int)nbr);
	}
}
