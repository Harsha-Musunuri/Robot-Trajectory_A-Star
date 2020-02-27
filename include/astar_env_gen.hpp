#ifndef __ASTAR_ENV_GEN_HPP__
#define __ASTAR_ENV_GEN_HPP__

#include <iostream>
#include <random>
#include <set>
#include <stdlib.h>

#include <grid_cell.hpp>

bool check_if_direction_possible(int grid_height, int grid_width, int point_x, int point_y, int direction);
grid_cell **init_env(int grid_height, int grid_width, int *starting_point_x, int *starting_point_y);
grid_cell **generate_astar_env(grid_cell **grid_cell_object, int grid_height, int grid_width, int point_x, int point_y);
void visualize_maze_grid(grid_cell **grid_cell_object, int grid_height, int grid_width);

#endif
