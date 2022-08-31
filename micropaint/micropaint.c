/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micropaint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:13:33 by earendil          #+#    #+#             */
/*   Updated: 2022/08/31 19:04:48 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micropaint.h"

static int	micropaint(FILE *fhandle);
static int	region_init(t_region *drawRegion, FILE *fhandle);
static void	draw_rectangle(t_rectangle rect, t_region *drawRegion);
//* end of static declarations

int main(int argc, char const *argv[])
{
	FILE	*fhandle;

	if (argc == 2)
	{
		if (
			NULL	==	(fhandle = fopen(argv[1], "r"))
			|| 1	==	micropaint(fhandle)
			|| EOF	==	fclose(fhandle)
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

static int	micropaint(FILE *fhandle)
{
	t_region	drawRegion;
	
	if (region_init(&drawRegion, fhandle))
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
				free_matrix(drawRegion.map, drawRegion.height);
				return (1);
			}
			draw_rectangle(rectangle, &drawRegion);
		}
		print_matrix(drawRegion.map, drawRegion.height, drawRegion.width);
		free_matrix(drawRegion.map, drawRegion.height);
		return (0);
	}
}

static int	region_init(t_region *drawRegion, FILE *fhandle)
{
	if (3 != fscanf(fhandle, "%d %d %c",
			&drawRegion->width, &drawRegion->height, &drawRegion->b_char)
		|| ( drawRegion->width <= 0 || drawRegion->width > 300)
		|| ( drawRegion->height <= 0 || drawRegion->height > 300))
	{
		return (1);
	}
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

static void	draw_rectangle(t_rectangle rect, t_region *drawRegion)
{
	t_point	p;

	if (rect.mark == '\n')
		rect.mark = drawRegion->b_char;
	rectangle_set_edges(&rect);
	for (int i = 0; i < drawRegion->height; i++)
		for (int j = 0; j < drawRegion->width; j++)
		{
			p.x = j;
			p.y = i;
			if (is_in_rectangle(p, rect))
			{
				if (rect.type == 'R'
					|| distance(p, get_closest_border_pt(rect, p)) < 1)
					drawRegion->map[i][j] = rect.mark;
			}
		}
}
