/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:16:47 by kmeixner          #+#    #+#             */
/*   Updated: 2022/04/26 10:30:55 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	render_next_frame(void *mystruct)
{
	return (0);
}

int main()
{	
	void	*mlx;
	void	*ptr;
	t_vars	vars;

	ptr = &vars;
	vars.test = 0;
	mlx = mlx_init();
	mlx_loop_hook(mlx, render_next_frame, ptr);
	mlx_loop(mlx);
}
