/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:24:54 by earendil          #+#    #+#             */
/*   Updated: 2022/08/25 19:41:30 by earendil         ###   ########.fr       */
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
	// printf("rows: %zu; columns: %zu\n", rows, columns);
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

void	rectangle_fill_points(t_rectangle *rect)
{
	rect->top_right.x = my_floor(rect->top_left.x + (rect->width));
	rect->top_right.y = rect->top_left.y;

	rect->bottom_right.x = my_floor(rect->top_left.x + (rect->width));
	rect->bottom_right.y = my_floor(rect->top_left.y + (rect->height));

	rect->bottom_left.x = rect->top_left.x;
	rect->bottom_left.y = rect->bottom_right.y;

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
	float	closest_x;
	float	closest_y;

	closest.x = -1;
	closest.y = -1;

	if (sqrtf(powf(p.x - rect.top_left.x, 2)) < sqrtf(powf(p.x - rect.top_right.x, 2)))
		closest_x = rect.top_left.x;
	else
		closest_x = rect.top_right.x;

	if (sqrtf(powf(p.y - rect.top_left.y, 2)) < sqrtf(powf(p.y - rect.bottom_left.y, 2)))
		closest_y = rect.top_left.y;
	else
		closest_y = rect.bottom_left.y;

	if (sqrtf(powf(p.x - closest_x, 2)) < sqrtf(powf(p.y - closest_y, 2)))
	{
		closest.x = closest_x;
		closest.y = p.y;
	}
	else
	{
		closest.y = closest_y;
		closest.x = p.x;
	}
	return (closest);
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
