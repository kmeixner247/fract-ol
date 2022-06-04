/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 08:53:12 by kmeixner          #+#    #+#             */
/*   Updated: 2022/04/30 10:59:48 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	closew(int keycode, t_vars *vars)
{
	// printf("Keycode is %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

// void nextlayer(t_point *p, int x)
// {
// 	int	i;

// 	i = 0;
// 	while ()
// 	while (i < x)
// 	{
// 		calculate_mandelbrot(p, -x, i);
// 		calculate_mandelbrot(p, x, i);
// 		i++;
// 	}
// }

// void	draw_mandelbrot2(t_vars *vars, int	iterations)
// {
	
// }

void	draw_mandelbrot(t_vars *vars, int iterations)
{
	t_point	p;
	t_point	tmp;
	int		i;

	p.x = 0;
	while (p.x < vars->width)
	{
	p.y = 0;
		while (p.y < vars->height)
		{
			transpose(&p, vars);
			i = 0;
			tmp.r = 0;
			tmp.i = 0;
			while (i < iterations && c_check(tmp) < 4)
			{
				tmp = mandelbrot_iterate(tmp, p);
				i++;
			}
			if (i < iterations)
				my_mlx_pixel_put(&vars->img, p.x, p.y, colourconversion(i));
			p.y++;
		}
		p.x++;
	}
}

void	calc_minmax(t_vars *vars, t_point anchor, double factor)
{
	double	dxold;
	double	dyold;
	double	dx;
	double	dy;

	dxold = vars->xmax - vars->xmin;
	dyold = vars->ymax - vars->ymin;
	dx = dxold * factor;
	dy = dyold * factor;
	vars->ymin = anchor.i - (dy / (dyold / (anchor.i - vars->ymin)));
	vars->ymax = anchor.i + (dy / (dyold / (vars->ymax - anchor.i)));
	vars->xmin = anchor.r - (dx / (dxold / (anchor.r - vars->xmin)));
	vars->xmax = anchor.r + (dx / (dxold / (vars->xmax - anchor.r)));
}

void	zoom(t_vars *vars, int x, int y, double factor)
{
	t_point	anchor;

	anchor.x = x;
	anchor.y = y;
	transpose(&anchor, vars);
	calc_minmax(vars, anchor, factor);
	vars->org.x = (0 - vars->xmin) * (vars->width / (vars->xmax - vars->xmin));
	vars->org.y = (0 - vars->ymin) * (vars->height / (vars->ymax - vars->ymin));
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, vars->width, vars->height);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, \
						&vars->img.line_length, &vars->img.endian);
	draw_mandelbrot(vars, 765);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

int	mouse_hook(int mousecode, int x, int y, void *mystruct)
{
	t_vars	*vars;
	double	zoomfactor;

	zoomfactor = 1.25;
	vars = (t_vars *)mystruct;
	if (mousecode == 4)
		zoom(vars, x, y, 1 / zoomfactor);
	if (mousecode == 5)
		zoom(vars, x, y, zoomfactor);
	return (0);
}

int loop(void *mystruct)
{
	t_vars	*vars;

	vars = (t_vars *)mystruct;
	mlx_mouse_hook(vars->win, &mouse_hook, &vars);
	return (0);
}

int	main(void)
{
	t_vars		vars;

	vars.width = 1500;
	vars.height = 1000;
	vars.xmin = -2.4;
	vars.xmax = 1.2;
	vars.ymin = -1.2;
	vars.ymax = 1.2;
	vars.org.x = (0 - vars.xmin) * (vars.width / (vars.xmax - vars.xmin));
	vars.org.y = (0 - vars.ymin) * (vars.height / (vars.ymax - vars.ymin));
	vars.org.r = 0;
	vars.org.i = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.width, vars.height, "yo");
	vars.img.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, \
							&vars.img.line_length, &vars.img.endian);
	vars.test = 0;
	draw_mandelbrot(&vars, 765);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hook(vars.win, ON_KEYDOWN, 0, closew, &vars);
	// mlx_loop_hook(vars.mlx, loop, &vars);
	mlx_mouse_hook(vars.win, &mouse_hook, &vars);
	mlx_loop(vars.mlx);
}
