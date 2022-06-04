/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:10:37 by kmeixner          #+#    #+#             */
/*   Updated: 2022/04/30 17:46:10 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fill_box(t_vars *vars, int xstart, int ystart, int size)
{
	int	x;
	int	y;
	int	clr;

	clr = getpxl(vars, xstart, ystart);
	x = xstart + 1;
	while (x < xstart + size)
	{
		y = ystart + 1;
		while (y < ystart + size)
		{
			my_mlx_pixel_put(&vars->img, x, y, clr);
			y++;
		}
		x++;
	}
}

static void	calc_four(t_vars *vars, int x, int y)
{
	my_mlx_pixel_put(&vars->img, x, y, (vars->calcpxl)(vars, x, y));
	my_mlx_pixel_put(&vars->img, x, y + 1, (vars->calcpxl)(vars, x, y + 1));
	my_mlx_pixel_put(&vars->img, x + 1, y, (vars->calcpxl)(vars, x + 1, y));
	my_mlx_pixel_put(&vars->img, x + 1, y + 1, \
									(vars->calcpxl)(vars, x + 1, y + 1));
}

static int	check_box(t_vars *vars, int xstart, int ystart, int size)
{
	int	i;
	int	clr;

	clr = getpxl(vars, xstart, ystart);
	i = 0;
	while (i < size - 1)
	{
		if (getpxl(vars, xstart + i, ystart) != clr || \
			getpxl(vars, xstart + size - 1, ystart + i) != clr || \
			getpxl(vars, xstart, ystart + size - 1 - i) != clr || \
			getpxl(vars, xstart + size - 1 - i, ystart + size - 1) != clr)
			return (1);
		i++;
	}
	return (0);
}

static void	draw_border(t_vars *vars, int xstart, int ystart, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (!getpxl(vars, xstart + i, ystart))
			do_stuff(vars, xstart + i, ystart);
		if (!getpxl(vars, xstart + size - 1, ystart + i))
			do_stuff(vars, xstart + size - 1, ystart + i);
		if (!getpxl(vars, xstart, ystart + size - 1 - i))
			do_stuff(vars, xstart, ystart + size - 1 - i);
		if (!getpxl(vars, xstart + size - 1 - i, ystart + size - 1))
			do_stuff(vars, xstart + size - 1 - i, ystart + size - 1);
		i++;
	}
}

void	box(t_vars *vars, int xstart, int ystart, int size)
{
	draw_border(vars, xstart, ystart, size);
	if (!check_box(vars, xstart, ystart, size))
		fill_box(vars, xstart, ystart, size);
	else if (size == 4)
		calc_four(vars, xstart + 1, ystart + 1);
	else
	{
		box(vars, xstart, ystart, size / 2 + 1);
		box(vars, xstart + size / 2, ystart, size / 2 + 1);
		box(vars, xstart, ystart + size / 2, size / 2 + 1);
		box(vars, xstart + size / 2, ystart + size / 2, size / 2 + 1);
	}
}
