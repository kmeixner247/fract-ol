/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:10:03 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/02 22:49:28 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "fractol.h"

double	get_distance(int *pa, int *pb)
{
	int dx;
	int dy;

	dx = pa[0] - pb[0];
	dy = pa[1] - pb[1];
	return (sqrt(dx * dx + dy * dy));
}

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		p[2];
	int		center[2];
	int		pred[2];
	int		pgreen[2];
	int		pblue[2];
	int		red;
	int		green;
	int		blue;
	int		dred;
	int		dgreen;
	int		dblue;

	pred[0] = 399;
	pred[1] = 0;
	pgreen[0] = 0;
	pgreen[1] = 691;
	pblue[0] = 799;
	pblue[1] = 691;
	center[0] = 399;
	center[1] = 345;
	dred = get_distance(pred, center);
	dgreen = get_distance(pgreen, center);
	dblue = get_distance(pblue, center);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 692, "WAZZUP BOIII!");
	img.img = mlx_new_image(mlx, 800, 692);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
								&img.line_length, &img.endian);
	p[0] = 0;
	while (p[0] < 800)
	{
		p[1] = 0;
		while (p[1] < 692)
		{
			red = 255 - ((get_distance(pred, p) * 255)) / 800;
			green = 255 - ((get_distance(pgreen, p) * 255)) / 800;
			blue = 255 - ((get_distance(pblue, p) * 255)) / 800;
			my_mlx_pixel_put(&img, p[0], p[1], create_trgb(0, red, green, blue));
			p[1]++;
		}
		p[0]++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
