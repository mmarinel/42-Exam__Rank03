/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipaint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:25:19 by earendil          #+#    #+#             */
/*   Updated: 2022/08/31 19:30:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minipaint.h"

static int	minipaint(FILE *fhandle);
static int	region_init(t_region *drawRegion, FILE *fhandle);
static void	draw_circle(t_circle circle, t_region *drawRegion);
//* end of static declarations

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		FILE	*fhandle;

		if (
			NULL	==	(fhandle = fopen(argv[1], "r"))
			|| 1	==	minipaint(fhandle)
			|| EOF	== fclose(fhandle)
		)
		{
			write(STDOUT_FILENO, IO_ERR, ft_strlen(IO_ERR));
			return (1);
		}
		else
			return (0);
	}
	else
	{
		write(STDOUT_FILENO, ARG_ERR, ft_strlen(ARG_ERR));
		return (1);
	}
}

static int	minipaint(FILE *fhandle)
{
	t_region	drawRegion;

	if (region_init(&drawRegion, fhandle))
		return (1);
	else
	{
		t_circle	circle;
		int			scan_return;

		while (1)
		{
			scan_return = fscanf(fhandle,
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
				free_matrix(drawRegion.map, drawRegion.height);
				return (1);
			}
			draw_circle(circle, &drawRegion);
		}
		print_matrix(drawRegion.map, drawRegion.height, drawRegion.width);
		free_matrix(drawRegion.map, drawRegion.height);
		return (0);
	}
}

static void	draw_circle(t_circle circle, t_region *drawRegion)
{
	t_point	p;

	if (circle.mark == '\n')
		circle.mark = drawRegion->b_char;
	for (int i = 0; i < drawRegion->height; i++)
	{
		for (int j = 0; j < drawRegion->width; j++)
		{
			p.x = j;
			p.y = i;

			if (is_in_circle(p, circle))
			{
				if (circle.type == 'C'
					|| distance_from_circumference(p, circle) < 1)
					drawRegion->map[i][j] = circle.mark;
			}
		}
	}
}

static int	region_init(t_region *drawRegion, FILE *fhandle)
{
	if (3 != fscanf(fhandle, "%d %d %c",
				&drawRegion->width, &drawRegion->height, &drawRegion->b_char)
		|| (drawRegion->width <= 0 || drawRegion->width > 300)
		|| (drawRegion->height <= 0 || drawRegion->height > 300))
		return (1);
	else
	{
		drawRegion->map = (char **) malloc(drawRegion->height * sizeof(char *));
		if (NULL == drawRegion->map)
			return (1);
		for (int i = 0; i < drawRegion->height; i++)
		{
			drawRegion->map[i] = (char *) malloc(drawRegion->width * sizeof(char));
			if (NULL == drawRegion->map[i])
			{
				free_matrix(drawRegion->map, i);
				return (1);
			}
			memset(drawRegion->map[i], drawRegion->b_char, drawRegion->width);
		}
		return (0);
	}
}
