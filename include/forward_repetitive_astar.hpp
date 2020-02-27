#ifndef __FORWARD_REPETITIVE_HPP__
#define __FORWARD_REPETITIVE_HPP__

#include <a_star.hpp>

void forward_repetitive_astar(grid_cell **grid_cell_object,
								int grid_height, int grid_width,
								int start_cell_x, int start_cell_y,
								int target_cell_x, int target_cell_y,
								int mode_for_resolving_tie);

#endif
