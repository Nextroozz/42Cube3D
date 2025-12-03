#ifndef CUB3D_H
#define CUB3D_H

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define FOV 60

typedef enum e_mlxevent {
  MLX_EVENT_KEYDOWN = 2,
  MLX_EVENT_KEYUP = 3,
  MLX_EVENT_MOUSEDOWN = 4,
  MLX_EVENT_MOUSEUP = 5,
  MLX_EVENT_MOUSEMOVE = 6,
  MLX_EVENT_DESTROY = 17
} t_mlxevent;

typedef enum e_orientation {
  ORIENTATION_EAST = 0,
  ORIENTATION_NORTH = 90,
  ORIENTATION_WEST = 180,
  ORIENTATION_SOUTH = 270,
} t_orientation;

typedef struct s_vec2 {
  float x;
  float y;
} t_vec2;

typedef struct s_color {
  int r;
  int g;
  int b;
} t_color;

typedef struct s_player {
  t_vec2 pos;
  float dir;
} t_player;

typedef struct s_map {
  char *north_texture;
  char *south_texture;
  char *east_texture;
  char *west_texture;
  t_vec2 *walls;
  int wallcount;
  t_player player;
  t_color floor_color;
  t_color ceiling_color;
  char *map_text;
} t_map;

typedef struct s_img {
  void *ptr;
  char *addr;
  int bpp;
  int line_len;
  int endian;
} t_img;

void img_pixel_put(t_img *img, int x, int y, t_color color);

typedef struct s_state {
  void *mlx;
  void *window;
  t_img texture;
  t_map map;
} t_state;

/* ========================================================================= */
/*                         PARSING FUNCTION PROTOTYPES                       */
/* ========================================================================= */

/* parsing.c */
void print_error(char *message);
t_map *parse_cub_file(char *filename);

/* parsing_file.c */
int validate_filename(char *filename);
int open_file(char *filename);

/* parsing_textures.c */
char *extract_texture_path(char *line, int start);
int validate_texture_file(char *path);
int assign_texture(t_map *map, char identifier[3], char *path);
int extract_identifier(char *line, char identifier[3]);
int parse_texture_line(char *line, t_map *map);

/* parsing_textures_utils.c */
int validate_textures(t_map *map);

/* parsing_colors.c */
int parse_rgb_value(char *str);
int extract_rgb_component(char *line, int *i, int need_comma);
int assign_color(t_map *map, char type, int rgb[3]);
int parse_color_line(char *line, t_map *map);
int validate_colors(t_map *map);

/* parsing_config.c */
char	*parse_config_elements(int fd, t_map *map, int *success);

/* parsing_map.c */
int		read_map_lines(int fd, t_map *map, char *first_line);

/* parsing_map_read.c */
int		is_map_line(char *line);
char	*append_map_line(char *map_data, char *line);
int		count_walls(char *map_text);
void	fill_walls_array(char *map_text, t_vec2 *walls);
int		allocate_and_fill_walls(char *map_text, t_map *map);

/* parsing_map_player.c */
void	assign_player_direction(t_map *map, char c);
int		find_player_in_text(char *map_text, t_map *map);

/* parsing_map_grid.c */
void	get_map_dimensions(t_map *map, int *max_x, int *max_y);
char	**create_grid(int max_x, int max_y);
void	fill_grid_with_walls(char **grid, t_map *map);
void	free_grid(char **grid, int max_y);
int		check_cell_neighbors(char **grid, int x, int y, int *dims);

/* parsing_map_validation.c */
int		check_borders(char **grid, int max_x, int max_y);
int		check_accessible_cells(char **grid, int max_x, int max_y);
int		validate_map_walls(t_map *map);
int		validate_map(t_map *map);

/* utils.c */
int ftstrlen(char *str);
char *ft_strdup(char *s);
char *ft_strjoin(const char *s1, const char *s2);

#endif