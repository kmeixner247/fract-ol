/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 21:18:04 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/09 14:43:01 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int mousecode, int x, int y, void *mystruct)
{
	t_vars	*vars;
	double	zoomfactor;

	zoomfactor = 1.25;
	vars = (t_vars *)mystruct;
	if (x < 0 || x > vars->width - 1 || y < 0 || y > vars->height)
		return (0);
	if (mousecode == 4)
	{
		if (((vars->ymax - vars->ymin) / zoomfactor) >= 0.000001)
			zoom(vars, x, y, 1 / zoomfactor);
	}
	if (mousecode == 5)
		if ((vars->ymax - vars->ymin) * zoomfactor <= 100)
			zoom(vars, x, y, zoomfactor);
	return (0);
}
