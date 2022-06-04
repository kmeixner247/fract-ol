/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:07:43 by kmeixner          #+#    #+#             */
/*   Updated: 2022/04/30 16:10:00 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	calc_minmax(t_vars *vars, t_point anchor, double factor)
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
	calc_org(vars);
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, vars->width, vars->height);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	(*vars->draw)(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
