/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:15:40 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/10 17:30:54 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub3d_keypress(int keycode, t_state *state)
{
	if (keycode == KEYCODE_Z || keycode == KEYCODE_W)
		state->s_mvmt.fwd_bcw |= MVMT_FRWD;
	if (keycode == KEYCODE_S)
		state->s_mvmt.fwd_bcw |= MVMT_BCWD;
	if (keycode == KEYCODE_D)
		state->s_mvmt.lft_rgt |= MVMT_RGHT;
	if (keycode == KEYCODE_LEFT)
		state->s_mvmt.trn_lft_rgt |= MVMT_TRNL;
	if (keycode == KEYCODE_RIGHT)
		state->s_mvmt.trn_lft_rgt |= MVMT_TRNR;
	if (keycode == KEYCODE_Q || keycode == KEYCODE_A)
		state->s_mvmt.lft_rgt |= MVMT_LEFT;
	if (keycode == KEYCODE_ESC)
		state->should_close = true;
	return (0);
}

int	cub3d_keyrelease(int keycode, t_state *state)
{
	if (keycode == KEYCODE_Z || keycode == KEYCODE_W)
		state->s_mvmt.fwd_bcw &= ~MVMT_FRWD;
	if (keycode == KEYCODE_S)
		state->s_mvmt.fwd_bcw &= ~MVMT_BCWD;
	if (keycode == KEYCODE_D)
		state->s_mvmt.lft_rgt &= ~MVMT_RGHT;
	if (keycode == KEYCODE_LEFT)
		state->s_mvmt.trn_lft_rgt &= ~MVMT_TRNL;
	if (keycode == KEYCODE_RIGHT)
		state->s_mvmt.trn_lft_rgt &= ~MVMT_TRNR;
	if (keycode == KEYCODE_Q || keycode == KEYCODE_A)
		state->s_mvmt.lft_rgt &= ~MVMT_LEFT;
	return (0);
}

int	cub3d_close(t_state *state)
{
	mlx_destroy_window(state->mlx, state->window);
	state->window = NULL;
	return (0);
}
