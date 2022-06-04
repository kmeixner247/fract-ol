/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 19:19:34 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/03 10:37:32 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	wrong_input(char *s)
{
	ft_putstr_fd(s, 1);
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("Required form: ./fractol <fractal name> (<julia index>) ", 1);
	ft_putstr_fd("<colour scheme>\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("Available fractals:\nmandelbrot\njulia\nburningship\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("Available colour schemes:\nbernstein\nsinus\n", 1);
	ft_putstr_fd("drugs\nburn\nblackwhite\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("Available Julia indices:\tcalculated parameters\n", 1);
	ft_putstr_fd("1\t\t\t\t-0.8696 + 0.26i\n2\t\t\t\t-0.8696 - 0.26i\n", 1);
	ft_putstr_fd("3\t\t\t\t-0.4 + 0.6i\n4\t\t\t\t-0.4 - 0.6i\n", 1);
	ft_putstr_fd("5\t\t\t\t0.285 + 0.01i\n6\t\t\t\t-0.835 - 0.2321i\n", 1);
	exit (-1);
}

static void	check_julia(t_vars *vars, int argc, char **argv)
{
	if (argc < 4)
		wrong_input("Not enough arguments\n");
	if (argc > 4)
		wrong_input("Too many arguments\n");
	if (argv[2][0] == '1')
		prep_julia(vars, -0.8696, 0.26);
	else if (argv[2][0] == '2')
		prep_julia(vars, -0.8696, -0.26);
	else if (argv[2][0] == '3')
		prep_julia(vars, -0.4, 0.6);
	else if (argv[2][0] == '4')
		prep_julia(vars, -0.4, -0.6);
	else if (argv[2][0] == '5')
		prep_julia(vars, 0.285, 0.01);
	else if (argv[2][0] == '6')
		prep_julia(vars, -0.835, -0.2321);
	else
		wrong_input("Error: No valid Julia index specified\n");
}

static void	check_fractal(t_vars *vars, int argc, char **argv)
{
	if (!ft_strcmp(argv[1], "julia"))
		check_julia(vars, argc, argv);
	else if (!ft_strcmp(argv[1], "mandelbrot"))
		prep_mandelbrot(vars);
	else if (!ft_strcmp(argv[1], "burningship"))
		prep_burningship(vars);
	else
	{
		wrong_input("Error: No valid fractal specified.\n");
		exit(-1);
	}
}

static void	check_colours(t_vars *vars, int argc, char **argv)
{
	if (!ft_strcmp(argv[argc - 1], "bernstein"))
		vars->colour = &bernstein;
	else if (!ft_strcmp(argv[argc - 1], "sinus"))
		vars->colour = &sinclrs;
	else if (!ft_strcmp(argv[argc - 1], "drugs"))
		vars->colour = &sinclrs_on_drugs;
	else if (!ft_strcmp(argv[argc - 1], "burn"))
		vars->colour = &burn;
	else if (!ft_strcmp(argv[argc - 1], "blackwhite"))
		vars->colour = &blackwhite;
	else
		wrong_input("Error: No valid colour scheme specified\n");
}

void	check_inputs(t_vars *vars, int argc, char **argv)
{
	if (argc < 3)
		wrong_input("Error: Not enough arguments\n");
	if (ft_strcmp(argv[1], "julia") && argc > 3)
		wrong_input("Error: Too many arguments\n");
	check_fractal(vars, argc, argv);
	check_colours(vars, argc, argv);
}
