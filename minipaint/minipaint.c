/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipaint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:25:19 by earendil          #+#    #+#             */
/*   Updated: 2022/08/26 11:24:40 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minipaint.h"

static int	minipaint(FILE *handle);
static int	zone_init(t_zone *zone, FILE *handle);
static void	draw_circle(t_circle circle, t_zone *zone);
//* end of static declarations

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		FILE	*handle;

		handle = fopen(argv[1], "r");
		if (NULL == handle)
		{
			write(STDOUT_FILENO, IO_ERR, ft_strlen(IO_ERR));
			return (1);
		}
		return (minipaint(handle));
	}
	else
	{
		write(STDOUT_FILENO, ARG_ERR, ft_strlen(ARG_ERR));
		return (1);
	}
}

static int	minipaint(FILE *handle)
{
	t_zone	zone;

	if (zone_init(&zone, handle))
		return (1);
	else
	{
		t_circle	circle;
		int			scan_return;

		while (1)
		{
			scan_return = fscanf(handle,
						"\n%c %f %f %f %c",
						&circle.type,
						&circle.center.x, &circle.center.y,
						&circle.radius,
						&circle.mark
						);
			if (EOF == scan_return)
				break ;
			if (5 != scan_return
				|| (circle.type != 'c' && circle.type != 'C')
				|| circle.radius <= 0)
			{
				write(STDOUT_FILENO, IO_ERR, ft_strlen(IO_ERR));
				free_matrix(zone.map, zone.height);
				return (1);
			}
			draw_circle(circle, &zone);
		}
		print_matrix(zone.map, zone.height, zone.width);
		free_matrix(zone.map, zone.height);
		return (0);
	}
}

static void	draw_circle(t_circle circle, t_zone *zone)
{
	t_point	p;

	if (circle.mark == '\n')
		circle.mark = zone->b_char;
	for (int i = 0; i < zone->height; i++)
	{
		for (int j = 0; j < zone->width; j++)
		{
			p.x = j;
			p.y = i;

			if (is_in_circle(p, circle))
			{
				if (circle.type == 'C'
					|| circumference_distance(circle, p) < 1)
					zone->map[i][j] = circle.mark;
			}
		}
	}
}

static int	zone_init(t_zone *zone, FILE *handle)
{
	if (3 != fscanf(handle, "%d %d %c", &zone->width, &zone->height, &zone->b_char)
		|| (zone->width <= 0 || zone->width > 300)
		|| (zone->height <= 0 || zone->height > 300))
	{
		write(STDOUT_FILENO, IO_ERR, ft_strlen(IO_ERR));
		return (1);
	}
	zone->map = (char **) malloc(zone->height * sizeof(char *));
	if (NULL == zone->map)
		return (1);
	for (int i = 0; i < zone->height; i++)
	{
		zone->map[i] = (char *) malloc(zone->width * sizeof(char));
		if (NULL == zone->map[i])
		{
			free_matrix(zone->map, i);
			return (1);
		}
		memset(zone->map[i], zone->b_char, zone->width);
	}
	return (0);
}
