#ifndef __A_STAR_HPP__
#define __A_STAR_HPP__

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <map>

#include <grid_cell.hpp>

int manhattan_distance(int cell_x, int cell_y, int target_cell_x, int target_cell_y);
bool check_for_tie(int max_value, std::multimap<int, std::vector<int>> &f_func_values_map);
void resolve_tie(int max_value, std::multimap<int, std::vector<int>> &f_func_values_map,
				int *best_coord_x, int *best_coord_y, int mode_for_resolving_tie);
bool get_blocked_neighbours_info(grid_cell **grid_cell_object,
								std::map<std::pair<int, int>, std::vector<int>> &blocked_list,
								int grid_height, int grid_width,
								int curr_cell_x, int curr_cell_y,
								int direction);
void reset_visited_status(grid_cell **grid_cell_object,
							int grid_height, int grid_width,
							int start_cell_x, int start_cell_y,
							std::vector<int> &path_vector, int path_vector_end_point);
void fill_path_vector(grid_cell **grid_cell_object,
						int grid_height, int grid_width,
						int start_cell_x, int start_cell_y,
						int target_cell_x, int target_cell_y,
						std::vector<int> &path_vector);
void print_path(std::vector<int> &path_vector);
void directions_to_coordinate(std::vector<int> &path_vector, int start_cell_x, int start_cell_y, std::vector<std::pair<int,int>> &coordinates);
void coordinate_to_directions(std::vector<std::pair<int,int>> &coordinates, int start_cell_x, int start_cell_y);
void clean_path(std::vector<std::pair<int,int>> &coordinates);
void run_astar(grid_cell **grid_cell_object,
				std::vector<int> &f_func_heap,
				std::vector<std::pair<int, int>> &closed_list,
				std::map<std::pair<int, int>, std::vector<int>> &blocked_list,
				std::multimap<int, std::vector<int>> &f_func_values_map,
				int grid_height, int grid_width,
				int start_cell_x, int start_cell_y,
				int curr_cell_x, int curr_cell_y,
				int target_cell_x, int target_cell_y,
				int mode_for_resolving_tie);

#endif
