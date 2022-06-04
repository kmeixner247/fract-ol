/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colourschemes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 12:00:59 by kmeixner          #+#    #+#             */
/*   Updated: 2022/05/18 19:32:50 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	bernstein(int n)
{
	double	t;
	double	rt;
	double	r;
	double	g;
	double	b;

	t = (double)n / 255;
	rt = 1 - t;
	r = 9 * rt * t * t * t * 255;
	g = 15 * rt * rt * t * t * 255;
	b = 8.5 * rt * rt * rt * t * 255;
	return (create_trgb(0, (unsigned char)r, (unsigned char)g, \
										(unsigned char)b));
}

int	sinclrs(int n)
{
	double		r;
	double		g;
	double		b;
	double		m;

	if (n < 50)
		m = (double)n / 50;
	else
		m = 1;
	r = m * (sin(0.16 * n + 4) * 127.5 + 127.5);
	g = m * (sin(0.13 * n + 2) * 127.5 + 127.5);
	b = m * (sin(0.1 * n + 1) * 127.5 + 127.5);
	return (create_trgb(0, (unsigned char)r, (unsigned char)g, \
									(unsigned char) b));
}

int	sinclrs_on_drugs(int n)
{
	int		r;
	int		g;
	int		b;

	r = (sin(1.6 * n + 4) * 127.5 + 127.5);
	g = (sin(1.3 * n + 2) * 127.5 + 127.5);
	b = (sin(n + 1) * 127.5 + 127.5);
	return (create_trgb(0, (unsigned char)r, (unsigned char)g, \
									(unsigned char)b));
}

int	burn(int n)
{
	double	r;
	double	g;

	if (n >= 15)
		r = 255;
	else
		r = n * 17;
	g = n * 5;
	return (create_trgb(0, (unsigned char)r, (unsigned char)g, 0));
}

int	blackwhite(int n)
{
	double			v;
	unsigned char	c;

	v = 255 - (255 / (double)n);
	c = (unsigned char)v;
	return (create_trgb(0, c, c, c));
}
