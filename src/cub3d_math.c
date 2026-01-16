/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:11:04 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/16 15:24:44 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	absf64(double val)
{
	if (val >= 0)
		return (val);
	return (-val);
}

int	maxi32(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	mini32(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	clampi32(int a, int b, int c)
{
	return (mini32(maxi32(a, b), c));
}

double	minf64(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
