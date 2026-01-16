/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:07:02 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/03 15:09:07 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

uint64_t	time_now(void)
{
	static uint64_t	start;
	struct timeval	tv;
	uint64_t		now;

	gettimeofday(&tv, (void *)0);
	now = tv.tv_sec * 1000000 + tv.tv_usec;
	if (!start)
		start = now;
	return (now - start);
}
