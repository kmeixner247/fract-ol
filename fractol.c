/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:17:53 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/17 10:42:27 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	vars.height = 1164;
	vars.width = 1746;
	check_inputs(&vars, argc, argv);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.width, \
						vars.height, "fract-ol");
	(vars.init)(&vars);
	mlx_hook(vars.win, ON_KEYDOWN, 0, keys, &vars);
	mlx_hook(vars.win, ON_DESTROY, 0, closew, &vars);
	mlx_mouse_hook(vars.win, &mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
