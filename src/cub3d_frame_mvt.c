/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_frame_mvt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:06:28 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/15 16:21:44 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_fb_movement(t_state *st)
{
	double	mspeed;
	int		pstv;

	mspeed = st->frame_s * 5.0;
	if ((st->s_mvmt.fwd_bcw & MVMT_FRWD) == MVMT_FRWD
		|| (st->s_mvmt.fwd_bcw & MVMT_BCWD) == MVMT_BCWD)
	{
		pstv = -1;
		if ((st->s_mvmt.fwd_bcw & MVMT_FRWD) == MVMT_FRWD)
			pstv = 1;
		st->map.player.pos.x += cos(st->map.player.dir) * mspeed * pstv;
		st->map.player.pos.y += sin(st->map.player.dir) * mspeed * pstv;
	}
}

void	handle_lr_movement(t_state *st)
{
	double	mspeed;
	int		pstv;

	mspeed = st->frame_s * 4.0;
	if ((st->s_mvmt.lft_rgt & MVMT_LEFT) == MVMT_LEFT
		|| (st->s_mvmt.lft_rgt & MVMT_RGHT) == MVMT_RGHT)
	{
		pstv = -1;
		if ((st->s_mvmt.lft_rgt & MVMT_LEFT) == MVMT_LEFT)
			pstv = 1;
		st->map.player.pos.x += sin(st->map.player.dir) * pstv * mspeed;
		st->map.player.pos.y += -cos(st->map.player.dir) * pstv * mspeed;
	}
}

void	handle_tlr_movement(t_state *st)
{
	double	rspeed;
	int		pstv;
	double	fov;

	rspeed = st->frame_s * 3.0;
	fov = tan((FOV >> 1) * PI / 180.0);
	if ((st->s_mvmt.trn_lft_rgt & MVMT_TRNR) == MVMT_TRNR
		|| (st->s_mvmt.trn_lft_rgt & MVMT_TRNL) == MVMT_TRNL)
	{
		pstv = -1;
		if ((st->s_mvmt.trn_lft_rgt & MVMT_TRNL) == MVMT_TRNL)
			pstv = 1;
		st->map.player.dir += rspeed * pstv;
		st->plane = (t_vec2){
			-sin(st->map.player.dir) * fov,
			cos(st->map.player.dir) * fov
		};
	}
}
