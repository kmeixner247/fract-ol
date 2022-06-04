/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveimg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:22:30 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/02 22:10:58 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	moveright(t_vars *vars, double factor, t_data *img)
{
	int		x;
	int		y;
	int		pxls;
	double	shiftval;

	pxls = vars->width * factor;
	shiftval = (vars->xmax - vars->xmin) / vars->width * pxls;
	vars->xmin += shiftval;
	vars->xmax += shiftval;
	calc_org(vars);
	x = 0;
	while (x < vars->width)
	{
		y = 0;
		while (y < vars->height)
		{
			if (x + pxls < vars->width)
				my_mlx_pixel_put(img, x, y, getpxl(vars, x + pxls, y));
			else
				my_mlx_pixel_put(img, x, y, (vars->calcpxl)(vars, x, y));
			y++;
		}
		x++;
	}
	return (0);
}

int	moveleft(t_vars *vars, double factor, t_data *img)
{
	int		x;
	int		y;
	int		pxls;
	double	shiftval;

	pxls = vars->width * factor;
	shiftval = (vars->xmax - vars->xmin) / vars->width * pxls;
	vars->xmin -= shiftval;
	vars->xmax -= shiftval;
	calc_org(vars);
	x = vars->width - 1;
	while (x > 0)
	{
		y = 0;
		while (y < vars->height)
		{
			if (x - pxls > 0)
				my_mlx_pixel_put(img, x, y, getpxl(vars, x - pxls, y));
			else
				my_mlx_pixel_put(img, x, y, (vars->calcpxl)(vars, x, y));
			y++;
		}
		x--;
	}
	return (0);
}

int	moveup(t_vars *vars, double factor, t_data *img)
{
	int		x;
	int		y;
	int		pxls;
	double	shiftval;

	pxls = vars->height * factor;
	shiftval = (vars->ymax - vars->ymin) / vars->height * pxls;
	vars->ymin -= shiftval;
	vars->ymax -= shiftval;
	calc_org(vars);
	y = vars->height - 1;
	while (y > 0)
	{
		x = 0;
		while (x < vars->width)
		{
			if (y - pxls > 0)
				my_mlx_pixel_put(img, x, y, getpxl(vars, x, y - pxls));
			else
				my_mlx_pixel_put(img, x, y, (vars->calcpxl)(vars, x, y));
			x++;
		}
		y--;
	}
	return (0);
}

int	movedown(t_vars *vars, double factor, t_data *img)
{
	int		x;
	int		y;
	int		pxls;
	double	shiftval;

	pxls = vars->height * factor;
	shiftval = (vars->ymax - vars->ymin) / vars->height * pxls;
	vars->ymin += shiftval;
	vars->ymax += shiftval;
	calc_org(vars);
	y = 0;
	while (y < vars->height)
	{
		x = 0;
		while (x < vars->width)
		{
			if (y + pxls < vars->height)
				my_mlx_pixel_put(img, x, y, getpxl(vars, x, y + pxls));
			else
				my_mlx_pixel_put(img, x, y, (vars->calcpxl)(vars, x, y));
			x++;
		}
		y++;
	}
	return (0);
}

int	moveimg(t_vars *vars, double movefactor, int keycode)
{
	t_data	tmp;

	tmp.img = mlx_new_image(vars->mlx, vars->width, vars->height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, \
									&tmp.line_length, &tmp.endian);
	if (keycode == 123)
		moveleft(vars, movefactor, &tmp);
	if (keycode == 124)
		moveright(vars, movefactor, &tmp);
	if (keycode == 125)
		movedown(vars, movefactor, &tmp);
	if (keycode == 126)
		moveup(vars, movefactor, &tmp);
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img = tmp;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}
