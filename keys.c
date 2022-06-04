/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 21:16:53 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/17 10:42:33 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	closew(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

static int	reset(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	(vars->init)(vars);
	return (0);
}

static int	colourshift(t_vars *vars, int keycode)
{
	t_data	tmp;

	tmp.img = mlx_new_image(vars->mlx, vars->width, vars->height);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, \
									&tmp.line_length, &tmp.endian);
	if (keycode == 18)
		vars->colour = &bernstein;
	else if (keycode == 19)
		vars->colour = &sinclrs;
	else if (keycode == 20)
		vars->colour = &sinclrs_on_drugs;
	else if (keycode == 21)
		vars->colour = &burn;
	else if (keycode == 23)
		vars->colour = &blackwhite;
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img = tmp;
	(vars->draw)(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	keys(int keycode, t_vars *vars)
{
	double	movefactor;
	double	zoomfactor;

	movefactor = 0.1;
	zoomfactor = 1.5;
	if (keycode == 53)
		closew(vars);
	if (keycode == 15)
		reset(vars);
	if (keycode <= 126 && keycode >= 123)
		moveimg(vars, movefactor, keycode);
	if (keycode == 30 && (vars->ymax - vars->ymin) / zoomfactor >= 0.000001)
		zoom(vars, 872, 581, 1 / zoomfactor);
	if (keycode == 44 && (vars->ymax - vars->ymin) * zoomfactor <= 100)
		zoom(vars, 872, 581, zoomfactor);
	if (keycode <= 23 && keycode >= 18)
		colourshift(vars, keycode);
	return (0);
}
