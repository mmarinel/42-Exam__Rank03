/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:54:00 by earendil          #+#    #+#             */
/*   Updated: 2022/08/31 19:22:48 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minipaint.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	if (NULL == str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_matrix(char **m, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			write(STDOUT_FILENO, &m[i][j], sizeof(char));
		write(STDOUT_FILENO, "\n", sizeof(char));
	}
}

void	free_matrix(char **m, int rows)
{
	for (int i = 0; i < rows; i++)
		free(m[i]);
	free(m);
}

float	distance(t_point a, t_point b)
{
	return (sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2)));
}

int	is_in_circle(t_point p, t_circle circle)
{
	return (distance(p, circle.center) <= circle.radius);
}

float	distance_from_circumference(t_point p, t_circle circle)
{
	return (circle.radius - distance(p, circle.center));
}
