/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxandreseverin <maxandreseverin@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:00:00 by maseveri          #+#    #+#             */
/*   Updated: 2025/12/03 14:20:10 by maxandresev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

#define COLOR_RED     "\033[0;31m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[0;34m"
#define COLOR_RESET   "\033[0m"

int	g_test_count = 0;
int	g_passed = 0;
int	g_failed = 0;

void	print_header(char *title)
{
	printf("\n" COLOR_BLUE "═══════════════════════════════════════════\n");
	printf("  %s\n", title);
	printf("═══════════════════════════════════════════\n" COLOR_RESET);
}

void	test_result(char *test_name, int success)
{
	g_test_count++;
	printf("Test %d: %s... ", g_test_count, test_name);
	if (success)
	{
		printf(COLOR_GREEN "✓ PASS\n" COLOR_RESET);
		g_passed++;
	}
	else
	{
		printf(COLOR_RED "✗ FAIL\n" COLOR_RESET);
		g_failed++;
	}
}

void	print_map_info(t_map *map)
{
	printf("\n" COLOR_YELLOW "Map Information:" COLOR_RESET "\n");
	printf("  North texture: %s\n", map->north_texture ? map->north_texture : "NULL");
	printf("  South texture: %s\n", map->south_texture ? map->south_texture : "NULL");
	printf("  East texture:  %s\n", map->east_texture ? map->east_texture : "NULL");
	printf("  West texture:  %s\n", map->west_texture ? map->west_texture : "NULL");
	printf("  Floor color:   R=%d G=%d B=%d\n", map->floor_color.r, map->floor_color.g, map->floor_color.b);
	printf("  Ceiling color: R=%d G=%d B=%d\n", map->ceiling_color.r, map->ceiling_color.g, map->ceiling_color.b);
	printf("  Player pos:    X=%.2f Y=%.2f\n", map->player.pos.x, map->player.pos.y);
	printf("  Player dir:    %.0f°\n", map->player.dir);
	printf("  Wall count:    %d\n", map->wallcount);
}

void	test_valid_map(char *filename)
{
	t_map	*map;
	int		success;

	printf("\n" COLOR_YELLOW "Testing: %s" COLOR_RESET "\n", filename);
	map = parse_cub_file(filename);
	success = (map != NULL);
	test_result(filename, success);
	
	if (success)
	{
		print_map_info(map);
		free(map->north_texture);
		free(map->south_texture);
		free(map->east_texture);
		free(map->west_texture);
		free(map->walls);
		free(map);
	}
	else
	{
		printf(COLOR_RED "  Parsing failed for this map\n" COLOR_RESET);
	}
}

void	test_invalid_map(char *filename)
{
	t_map	*map;
	int		success;

	map = parse_cub_file(filename);
	success = (map == NULL);
	test_result(filename, success);
	
	if (!success && map)
	{
		free(map->north_texture);
		free(map->south_texture);
		free(map->east_texture);
		free(map->west_texture);
		free(map->walls);
		free(map);
	}
}

int	main(void)
{
	printf(COLOR_BLUE);
	printf("╔════════════════════════════════════════════════════════════╗\n");
	printf("║           CUB3D PARSING UNIT TESTER                        ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n");
	printf(COLOR_RESET);

	/* Test valid maps */
	print_header("VALID MAPS");
	test_valid_map("maps/good/subject_map.cub");
	test_valid_map("maps/good/test_map.cub");
	test_valid_map("maps/good/square_map.cub");
	test_valid_map("maps/good/cheese_maze.cub");
	test_valid_map("maps/good/dungeon.cub");
	test_valid_map("maps/good/matrix.cub");
	test_valid_map("maps/good/library.cub");

	/* Test invalid maps */
	print_header("INVALID MAPS - FILE/EXTENSION");
	test_invalid_map("maps/bad/filetype_wrong.buc");
	test_invalid_map("maps/bad/filetype_missing");
	test_invalid_map("maps/bad/file_letter_end.cub");
	test_invalid_map("maps/bad/empty.cub");

	print_header("INVALID MAPS - TEXTURES");
	test_invalid_map("maps/bad/textures_none.cub");
	test_invalid_map("maps/bad/textures_missing.cub");
	test_invalid_map("maps/bad/textures_duplicates.cub");
	test_invalid_map("maps/bad/textures_invalid.cub");
	test_invalid_map("maps/bad/textures_not_xpm.cub");
	test_invalid_map("maps/bad/textures_dir.cub");

	print_header("INVALID MAPS - COLORS");
	test_invalid_map("maps/bad/color_none.cub");
	test_invalid_map("maps/bad/color_missing.cub");
	test_invalid_map("maps/bad/color_missing_floor_rgb.cub");
	test_invalid_map("maps/bad/color_missing_ceiling_rgb.cub");
	test_invalid_map("maps/bad/color_invalid_rgb.cub");

	print_header("INVALID MAPS - MAP STRUCTURE");
	test_invalid_map("maps/bad/map_missing.cub");
	test_invalid_map("maps/bad/map_only.cub");
	test_invalid_map("maps/bad/map_first.cub");
	test_invalid_map("maps/bad/map_middle.cub");
	test_invalid_map("maps/bad/map_too_small.cub");

	print_header("INVALID MAPS - PLAYER");
	test_invalid_map("maps/bad/player_none.cub");
	test_invalid_map("maps/bad/player_multiple.cub");
	test_invalid_map("maps/bad/player_on_edge.cub");

	print_header("INVALID MAPS - WALLS");
	test_invalid_map("maps/bad/wall_none.cub");
	test_invalid_map("maps/bad/wall_hole_north.cub");
	test_invalid_map("maps/bad/wall_hole_south.cub");
	test_invalid_map("maps/bad/wall_hole_east.cub");
	test_invalid_map("maps/bad/wall_hole_west.cub");

	/* Results */
	printf("\n" COLOR_BLUE);
	printf("═══════════════════════════════════════════\n");
	printf("  RESULTS\n");
	printf("═══════════════════════════════════════════\n");
	printf(COLOR_RESET);
	printf("Total tests:  " COLOR_BLUE "%d\n" COLOR_RESET, g_test_count);
	printf("Passed:       " COLOR_GREEN "%d\n" COLOR_RESET, g_passed);
	printf("Failed:       " COLOR_RED "%d\n" COLOR_RESET, g_failed);

	if (g_failed == 0)
	{
		printf("\n" COLOR_GREEN);
		printf("╔════════════════════════════════════════════════════════════╗\n");
		printf("║                  ALL TESTS PASSED! 🎉                      ║\n");
		printf("╚════════════════════════════════════════════════════════════╝\n");
		printf(COLOR_RESET);
		return (0);
	}
	else
	{
		printf("\n" COLOR_RED);
		printf("╔════════════════════════════════════════════════════════════╗\n");
		printf("║              SOME TESTS FAILED ❌                          ║\n");
		printf("╚════════════════════════════════════════════════════════════╝\n");
		printf(COLOR_RESET);
		return (1);
	}
}
