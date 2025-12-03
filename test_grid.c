#include "./include/cub3d.h"
#include <stdio.h>

extern void get_map_dimensions(t_map *map, int *max_x, int *max_y);
extern char **create_grid(int max_x, int max_y);
extern void fill_grid_with_walls(char **grid, t_map *map);
extern void free_grid(char **grid, int max_y);

int main(void)
{
	t_map *map = parse_cub_file("maps/good/subject_map.cub");
	if (!map)
	{
		printf("Parsing failed\n");
		return (1);
	}
	
	printf("Map parsed successfully!\n");
	printf("Map text:\n[%s]\n", map->map_text);
	
	int max_x, max_y;
	get_map_dimensions(map, &max_x, &max_y);
	printf("\nDimensions: %d x %d\n", max_x, max_y);
	
	char **grid = create_grid(max_x, max_y);
	fill_grid_with_walls(grid, map);
	
	printf("\nGrid:\n");
	for (int y = 0; y <= max_y; y++)
	{
		for (int x = 0; x <= max_x; x++)
			printf("%c", grid[y][x]);
		printf("\n");
	}
	
	free_grid(grid, max_y);
	return (0);
}
