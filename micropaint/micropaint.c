/* ************************************************************************** */
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

#include "micropaint.h"

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
