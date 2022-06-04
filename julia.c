/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 12:53:08 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/02 21:27:14 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	prep_julia(t_vars *vars, double juliar, double juliai)
{
	vars->init = &init_julia;
	vars->draw = &draw_julia;
	vars->calcpxl = &calcpxl_julia;
	vars->max_iterations = 255;
	vars->julia_r = juliar;
	vars->julia_i = juliai;
}

void	init_julia(t_vars *vars)
{
	vars->xmin = -2;
	vars->xmax = 2;
	vars->ymin = -2;
	vars->ymax = 2;
	vars->img.img = mlx_new_image(vars->mlx, vars->width, vars->height);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	calc_org(vars);
	draw_julia(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	draw_julia(t_vars *vars)
{
	t_point	p;
	int		clr;

	p.x = 0;
	while (p.x < vars->width)
	{
		p.y = 0;
		while (p.y < vars->height)
		{
			do_stuff(vars, p.x, p.y);
			p.y++;
		}
	p.x++;
	}
	return ;
}

int	calcpxl_julia(t_vars *vars, int x, int y)
{
	t_point	z;
	t_point	c;
	t_point	tmp;
	int		i;

	z.x = x;
	z.y = y;
	c.r = vars->julia_r;
	c.i = vars->julia_i;
	i = 0;
	transpose(&z, vars);
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
