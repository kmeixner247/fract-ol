/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 12:53:30 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/02 21:24:16 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	prep_burningship(t_vars *vars)
{
	vars->init = &init_burningship;
	vars->draw = &draw_burningship;
	vars->calcpxl = &calcpxl_burningship;
	vars->max_iterations = 255;
}

void	init_burningship(t_vars *vars)
{
	vars->xmin = -3.3;
	vars->xmax = 3.3;
	vars->ymin = -2.2;
	vars->ymax = 2.2;
	vars->img.img = mlx_new_image(vars->mlx, vars->width, vars->height);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	calc_org(vars);
	draw_burningship(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	draw_burningship(t_vars *vars)
{
	t_point	p;

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

int	calcpxl_burningship(t_vars *vars, int x, int y)
{
	t_point	z;
	t_point	c;
	double	tmp;
	int		i;

	z.r = 0;
	z.i = 0;
	c.x = x;
	c.y = y;
	i = 0;
	transpose(&c, vars);
	while (i < vars->max_iterations && c_check(z) < 4)
	{
		tmp = z.r * z.r - z.i * z.i + c.r;
		z.i = my_abs(2 * z.r * z.i) + c.i;
		z.r = tmp;
		i++;
	}
	if (i < vars->max_iterations)
		return ((vars->colour)(i));
	else
		return (0x00000001);
	return (0);
}
