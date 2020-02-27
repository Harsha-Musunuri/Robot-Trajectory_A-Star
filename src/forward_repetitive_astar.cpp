#include <forward_repetitive_astar.hpp>

void forward_repetitive_astar(grid_cell **grid_cell_object,
								int grid_height, int grid_width,
								int start_cell_x, int start_cell_y,
								int target_cell_x, int target_cell_y,
								int mode_for_resolving_tie){

	std::vector<int> f_func_heap;
	std::vector<std::pair<int, int>> closed_list;
	std::map<std::pair<int, int>, std::vector<int>> blocked_list;
	std::vector<int> path_vector;
	std::multimap<int, std::vector<int>> f_func_values_map;
	reset_visited_status(grid_cell_object,
						grid_height, grid_width,
						start_cell_x, start_cell_y,
						path_vector, -1);

	bool blockage_exists = get_blocked_neighbours_info(grid_cell_object,
														blocked_list,
														grid_height, grid_width,
														start_cell_x, start_cell_y, -1);
	run_astar(grid_cell_object, f_func_heap,
			closed_list, blocked_list,
			f_func_values_map,
			grid_height, grid_width,
			start_cell_x, start_cell_y,
			start_cell_x, start_cell_y,
			target_cell_x, target_cell_y,
			mode_for_resolving_tie);
	fill_path_vector(grid_cell_object,
					grid_height, grid_width,
					start_cell_x, start_cell_y,
					target_cell_x, target_cell_y,
					path_vector);
	int curr_cell_x = start_cell_x;
	int curr_cell_y = start_cell_y;
	int i = 0;
	while(1){
		blockage_exists = get_blocked_neighbours_info(grid_cell_object,
													blocked_list,
													grid_height, grid_width,
													curr_cell_x, curr_cell_y, path_vector[i]);
		if(blockage_exists){
			std::vector<int> new_optimal_path;
			f_func_heap.clear();
			closed_list.clear();
			f_func_values_map.clear();
			reset_visited_status(grid_cell_object,
						grid_height, grid_width,
						start_cell_x, start_cell_y,
						path_vector, i);
			run_astar(grid_cell_object, f_func_heap,
					closed_list, blocked_list,
					f_func_values_map,
					grid_height, grid_width,
					curr_cell_x, curr_cell_y,
					curr_cell_x, curr_cell_y,
					target_cell_x, target_cell_y,
					mode_for_resolving_tie);
			fill_path_vector(grid_cell_object,
					grid_height, grid_width,
					curr_cell_x, curr_cell_y,
					target_cell_x, target_cell_y,
					new_optimal_path);

			path_vector.erase(path_vector.begin() + i, path_vector.end());
			path_vector.insert(path_vector.end(), new_optimal_path.begin(), new_optimal_path.end());
			if(path_vector[i] == 1)
				curr_cell_x --;
			else if(path_vector[i] == 2)
				curr_cell_y ++;
			else if(path_vector[i] == 3)
				curr_cell_x ++;
			else if(path_vector[i] == 4)
				curr_cell_y --;
		}
		else{
			if(path_vector[i] == 1)
				curr_cell_x --;
			else if(path_vector[i] == 2)
				curr_cell_y ++;
			else if(path_vector[i] == 3)
				curr_cell_x ++;
			else if(path_vector[i] == 4)
				curr_cell_y --;
		}
		if(curr_cell_x == target_cell_x && curr_cell_y == target_cell_y)
			break;
		i++;
	}
	// print_path(path_vector);
	std::vector<std::pair<int,int>> coordinates;
	coordinates.push_back({start_cell_x, start_cell_y});
	directions_to_coordinate(path_vector, start_cell_x, start_cell_y, coordinates);
	clean_path(coordinates);
	coordinate_to_directions(coordinates, start_cell_x, start_cell_y);
}
