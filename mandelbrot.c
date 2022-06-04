/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 12:57:04 by kmeixner          #+#    #+#             */
/*   Updated: 2022/06/04 16:13:08 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	prep_mandelbrot(t_vars *vars)
{
	vars->init = &init_mandelbrot;
	vars->draw = &draw_mandelbrot;
	vars->calcpxl = &calcpxl_mandelbrot;
	vars->max_iterations = 255;
}

void	init_mandelbrot(t_vars *vars)
{
	vars->xmin = -2.4;
	vars->xmax = 1.2;
	vars->ymin = -1.2;
	vars->ymax = 1.2;
	vars->img.img = mlx_new_image(vars->mlx, vars->width, vars->height);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	calc_org(vars);
	draw_mandelbrot(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	draw_mandelbrot(t_vars *vars)
{
	t_point	p;
	int		startsize;

	startsize = 97;
	p.y = 0;
	while (p.y < (vars->height - (startsize - 2)))
	{
		p.x = 0;
		while (p.x < (vars->width - (startsize - 2)))
		{
			box(vars, p.x, p.y, startsize);
			p.x += startsize;
		}
		p.y += startsize;
	}
}

int	calcpxl_mandelbrot(t_vars *vars, int x, int y)
{
	t_point	z;
	t_point	c;
	t_point	tmp;
	int		i;

	z.r = 0;
	z.i = 0;
	c.x = x;
	c.y = y;
	i = 0;
	transpose(&c, vars);
	while (i < vars->max_iterations && c_check(z) < 4)
	{
		tmp.r = z.r;
		tmp.i = z.i;
		z.r = (tmp.r * tmp.r) - (tmp.i * tmp.i) + c.r;
		z.i = (2 * tmp.r * tmp.i) + c.i;
		i++;
	}
	if (i < vars->max_iterations)
		return ((vars->colour)(i));
	else
		return (0x00000001);
}
