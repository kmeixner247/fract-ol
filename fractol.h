/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 08:41:00 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/09 14:37:12 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "mlx/mlx.h"

typedef struct s_point {
	int		x;
	int		y;
	double	r;
	double	i;
}				t_point;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef void	(*t_finit)();
typedef int		(*t_fcolour)();
typedef void	(*t_fdraw)();
typedef int		(*t_fcalcpxl)();

typedef struct s_vars {
	void		*mlx;
	void		*win;
	t_finit		init;
	t_fdraw		draw;
	t_fcolour	colour;
	t_fcalcpxl	calcpxl;
	int			height;
	int			width;
	double		xmin;
	double		xmax;
	double		ymin;
	double		ymax;
	t_point		org;
	t_data		img;
	double		julia_r;
	double		julia_i;
	int			max_iterations;
}				t_vars;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

//			box.c
void		box(t_vars *vars, int xstart, int ystart, int size);

//			burningship.c
void		prep_burningship(t_vars *vars);
void		init_burningship(t_vars *vars);
void		draw_burningship(t_vars *vars);
int			calcpxl_burningship(t_vars *vars, int x, int y);

//			colour_utils.c
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			create_trgb(int t, int r, int g, int b);
int			getpxl(t_vars *vars, int x, int y);

//			colourschemes.c
int			bernstein(int n);
int			sinclrs(int n);
int			sinclrs_on_drugs(int n);
int			burn(int n);
int			blackwhite(int n);

//			fractol_utils.c
size_t		ft_strlen(char *str);
void		do_stuff(t_vars *vars, int x, int y);
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);

//			input.c
void		check_inputs(t_vars *vars, int argc, char **argv);

//			julia.c
void		prep_julia(t_vars *vars, double juliar, double juliai);
void		init_julia(t_vars *vars);
void		draw_julia(t_vars *vars);
int			calcpxl_julia(t_vars *vars, int x, int y);

//			keys.c
int			closew(t_vars *vars);
int			keys(int keycode, t_vars *vars);

//			mandelbrot.c
void		prep_mandelbrot(t_vars *vars);
void		init_mandelbrot(t_vars *vars);
void		draw_mandelbrot(t_vars *vars);
int			calcpxl_mandelbrot(t_vars *vars, int x, int y);

//			math_utils.c
double		c_check(t_point p);
void		transpose(t_point *p, t_vars *vars);
double		my_abs(double d);
int			calc_org(t_vars *vars);

//			mouse.c
int			mouse_hook(int mousecode, int x, int y, void *mystruct);

//			moveimg.c
int			moveimg(t_vars *vars, double movefactor, int keycode);

//			zoom.c
void		zoom(t_vars *vars, int x, int y, double factor);

#endif