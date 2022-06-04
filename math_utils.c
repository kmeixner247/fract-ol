/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 08:44:34 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/17 15:39:40 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	c_check(t_point p)
{
	return (p.r * p.r + p.i * p.i);
}

void	transpose(t_point *p, t_vars *vars)
{
	p->r = ((double)p->x - (double)vars->org.x) / \
		((double)vars->width / (vars->xmax - vars->xmin));
	p->i = ((double)p->y - (double)vars->org.y) / \
		((double)vars->height / (vars->ymax - vars->ymin));
}

double	my_abs(double d)
{
	if (d >= 0)
		return (d);
	else
		return (-d);
}

int	calc_org(t_vars *vars)
{
	vars->org.x = (0 - vars->xmin) * (vars->width / (vars->xmax - vars->xmin));
	vars->org.y = (0 - vars->ymin) * (vars->height / (vars->ymax - vars->ymin));
	return (0);
}
