/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflandin <aflandin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:06:38 by aflandin          #+#    #+#             */
/*   Updated: 2025/12/17 14:52:34 by aflandin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 720

# define KEYCODE_Z 122
# define KEYCODE_W 119
# define KEYCODE_A 97
# define KEYCODE_Q 113
# define KEYCODE_S 115
# define KEYCODE_D 100
# define KEYCODE_ESC 65307
# define KEYCODE_LEFT 65363
# define KEYCODE_RIGHT 65361

# define RENDER_DISTANCE 64
# define FOV 66

# define EXTENSION_MAP ".cub"
# define EXPENSION_TEXTURE ".xpm"

# define PI M_PI

typedef enum e_mlxevent
{
	MLX_EVENT_KEYDOWN = 2,
	MLX_EVENT_KEYUP = 3,
	MLX_EVENT_MOUSEDOWN = 4,
	MLX_EVENT_MOUSEUP = 5,
	MLX_EVENT_MOUSEMOVE = 6,
	MLX_EVENT_DESTROY = 17
}	t_mlxevent;

typedef enum e_orientation
{
	ORIENTATION_EAST = 0,
	ORIENTATION_NORTH = 90,
	ORIENTATION_WEST = 180,
	ORIENTATION_SOUTH = 270,
}	t_orientation;

enum e_movement
{
	MVMT_FRWD = 1 << 0,
	MVMT_BCWD = 1 << 1,
	MVMT_RGHT = 1 << 0,
	MVMT_LEFT = 1 << 1,
	MVMT_TRNR = 1 << 0,
	MVMT_TRNL = 1 << 1,
};

enum e_walltexts_id
{
	WALL_NO,
	WALL_WE,
	WALL_SO,
	WALL_EA
};

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_vec2i
{
	int	x;
	int	y;
}	t_vec2i;

typedef union u_color
{
	struct
	{
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
	};
	unsigned char	params[3];
}	t_color;

typedef struct s_player
{
	t_vec2	pos;
	float	dir;
}	t_player;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char			*north_texture;
	char			*south_texture;
	char			*east_texture;
	char			*west_texture;
	t_vec2i			*walls;
	int				wallcount;
	t_player		player;
	t_color			floor_color;
	t_color			ceiling_color;
	char			*content;
	bool			fcolor_set;
	bool			ccolor_set;
}	t_map;

typedef struct s_state
{
	void		*mlx;
	void		*window;
	double		frame_s;
	struct
	{
		int	fwd_bcw;
		int	lft_rgt;
		int	trn_lft_rgt;
	}	s_mvmt;
	bool		should_close;
	t_vec2		plane;
	t_img		texture;
	t_map		map;
	t_img		wall_texts[4];
}	t_state;

// time.c
uint64_t	time_now(void);

// image.c
t_img		img_create(void *mlx, int width, int height);
void		img_verline(t_img *img, int x, t_vec2i bt, t_color color);
void		img_clear(t_img *img);
void		img_pixel_put(t_img *img, int x, int y, t_color color);
void		img_destroy(void *mlx, t_img *img);

// image2.c
bool		img_load_xpm(t_img *img, void *mlx, const char *path);
t_color		img_color_get(t_img *img, int x, int y);

// mlx_hook.c
int			cub3d_keypress(int keycode, t_state *state);
int			cub3d_keyrelease(int keycode, t_state *state);
int			cub3d_close(t_state *state);

// cub3d_frame.c
int			cub3d_frame(t_state *state);

// cub3d_math.c
double		absf64(double val);
int			maxi32(int a, int b);
int			mini32(int a, int b);
int			clampi32(int a, int b, int c);
double		minf64(double a, double b);

// parsing.c
bool		map_create(t_map *map, const char *map_file);
void		map_destroy(t_map *map);

// raycasting.c
void		raycast_render(t_state *state);

// utils.c
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s);
char		*ft_strnjoin(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);

// utils2.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
bool		cub3d_strtorgb(t_color *color, const char *s);

// utils3.c
bool		ft_isspace(int c);
bool		ft_isnum(int c);
char		*ft_strndup(const char *s, size_t n);
void		cub3d_error(const char *error);
void		*ft_memcpy(void *dest, const void *src, size_t n);

// cub3d_frame_mvt.c
void		handle_tlr_movement(t_state *st);
void		handle_lr_movement(t_state *st);
void		handle_fb_movement(t_state *st);

#endif