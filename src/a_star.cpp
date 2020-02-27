#include<a_star.hpp>

int manhattan_distance(int cell_x, int cell_y, int target_cell_x, int target_cell_y){
	return (abs(target_cell_x - cell_x)) + (abs(target_cell_y - cell_y));
}

bool check_for_tie(int max_value, std::multimap<int, std::vector<int>> &f_func_values_map){
	if(f_func_values_map.count(max_value) == 1){
		return false;
	}
	else{
		return true;
	}
}

void resolve_tie(int max_value, std::multimap<int, std::vector<int>> &f_func_values_map,
				int *best_coord_x, int *best_coord_y, int mode_for_resolving_tie){
	//mode_for_resolving_tie 0 for smallest g value and 1 for largest g value
	std::pair <std::multimap<int,std::vector<int>>::iterator, std::multimap<int,std::vector<int>>::iterator> pair;
	pair = f_func_values_map.equal_range(max_value);
	int value;
	if(!mode_for_resolving_tie)
		value = 2147483647;
	else
		value = -1;

	for (std::multimap<int, std::vector<int>>::iterator it=pair.first; it!=pair.second; ++it){
		if(!mode_for_resolving_tie){
			if(it->second[1] < value){
				*(best_coord_x) = it->second[2];
				*(best_coord_y) = it->second[3];
				value = it->second[1];
			}
		}
		else{
			if(it->second[1] > value){
				*(best_coord_x) = it->second[2];
				*(best_coord_y) = it->second[3];
				value = it->second[1];
			}
		}
	}

	for (std::multimap<int, std::vector<int>>::iterator it=pair.first; it!=pair.second; ++it){
		if(it->second[2] == *(best_coord_x) && it->second[3] == *(best_coord_y)){
			// std::cout << "Erasing " << it->first << " " << it->second[2] << it->second[3] << "\n";
			f_func_values_map.erase(it);
			break;
		}
	}
}

bool get_blocked_neighbours_info(grid_cell **grid_cell_object,
								std::map<std::pair<int, int>, std::vector<int>> &blocked_list,
								int grid_height, int grid_width,
								int curr_cell_x, int curr_cell_y,
								int direction){
	bool blockage_exists = false;

	if(curr_cell_x > 0){
		if(!(grid_cell_object[curr_cell_x][curr_cell_y].get_top_neighbour_status() ||
			grid_cell_object[curr_cell_x-1][curr_cell_y].get_bottom_neighbour_status())){
			blocked_list[{curr_cell_x,curr_cell_y}].push_back(1);
			// std::cout << "Blocked path btw " << curr_cell_x << curr_cell_y << " and " << curr_cell_x-1 << curr_cell_y <<std::endl;
			if(direction == 1)
				blockage_exists = true;
		}
	}

	if(curr_cell_y < grid_width - 1){
		if(!(grid_cell_object[curr_cell_x][curr_cell_y].get_right_neighbour_status() ||
			grid_cell_object[curr_cell_x][curr_cell_y+1].get_left_neighbour_status())){
			// std::cout << "Blocked path btw " << curr_cell_x << curr_cell_y << " and " << curr_cell_x << curr_cell_y+1 <<std::endl;
			blocked_list[{curr_cell_x,curr_cell_y}].push_back(2);
			if(direction == 2)
				blockage_exists = true;
		}
	}

	if(curr_cell_x < grid_height - 1){
		if(!(grid_cell_object[curr_cell_x][curr_cell_y].get_bottom_neighbour_status() ||
			grid_cell_object[curr_cell_x+1][curr_cell_y].get_top_neighbour_status())){
			blocked_list[{curr_cell_x,curr_cell_y}].push_back(3);
			// std::cout << "Blocked path btw " << curr_cell_x << curr_cell_y << " and " << curr_cell_x+1 << curr_cell_y <<std::endl;
			if(direction == 3)
				blockage_exists = true;
		}
	}

	if(curr_cell_y > 0){
		if(!(grid_cell_object[curr_cell_x][curr_cell_y].get_left_neighbour_status() ||
			grid_cell_object[curr_cell_x][curr_cell_y-1].get_right_neighbour_status())){
			blocked_list[{curr_cell_x,curr_cell_y}].push_back(4);
			// std::cout << "Blocked path btwy " << curr_cell_x << curr_cell_y << " and " << curr_cell_x << curr_cell_y-1 <<std::endl;
			if(direction == 4)
				blockage_exists = true;
		}
	}
	return blockage_exists;
}

void reset_visited_status(grid_cell **grid_cell_object,
							int grid_height, int grid_width,
							int start_cell_x, int start_cell_y,
							std::vector<int> &path_vector, int path_vector_end_point){
	for(int i = 0; i < grid_height; i++){
		for(int j = 0; j< grid_width; j++){
			grid_cell_object[i][j].set_visited_status(false);
			grid_cell_object[i][j].set_h_val(0);
			grid_cell_object[i][j].set_g_val(0);
			grid_cell_object[i][j].set_f_val(0);
		}
	}
}

void fill_path_vector(grid_cell **grid_cell_object,
						int grid_height, int grid_width,
						int start_cell_x, int start_cell_y,
						int target_cell_x, int target_cell_y,
						std::vector<int> &path_vector){
	int curr_cell_x = target_cell_x;
	int curr_cell_y = target_cell_y;

	while(1){
		int temp_x = grid_cell_object[curr_cell_x][curr_cell_y].get_parent_x();
		int temp_y = grid_cell_object[curr_cell_x][curr_cell_y].get_parent_y();
		if(temp_x-1 == curr_cell_x){
			path_vector.push_back(1);
		}
		else if(temp_y+1 == curr_cell_y){
			path_vector.push_back(2);
		}
		else if(temp_x+1 == curr_cell_x){
			path_vector.push_back(3);
		}
		else if(temp_y-1 == curr_cell_y){
			path_vector.push_back(4);
		}
		curr_cell_x = temp_x;
		curr_cell_y = temp_y;
		if(curr_cell_x == start_cell_x && curr_cell_y == start_cell_y)
			break;
	}
	std::reverse(path_vector.begin(), path_vector.end());
}

void print_path(std::vector<int> &path_vector){
	for (int i = 0; i < path_vector.size(); ++i){
		if(path_vector[i] == 1)
			std::cout << "Top ";
		else if(path_vector[i] == 2)
			std::cout << "Right ";
		else if(path_vector[i] == 3)
			std::cout << "Bottom ";
		else if(path_vector[i] == 4)
			std::cout << "Left ";
	}
	std::cout << std::endl;
}

void directions_to_coordinate(std::vector<int> &path_vector, int start_cell_x, int start_cell_y, std::vector<std::pair<int,int>> &coordinates){
	for (int i = 0; i < path_vector.size(); ++i){
		if(path_vector[i] == 1){
			coordinates.push_back({--start_cell_x, start_cell_y});
		}
		else if(path_vector[i] == 2){
			coordinates.push_back({start_cell_x,++start_cell_y});
		}
		else if(path_vector[i] == 3){
			coordinates.push_back({++start_cell_x,start_cell_y});
		}
		else if(path_vector[i] == 4){
			coordinates.push_back({start_cell_x,--start_cell_y});
		}
	}
}

void coordinate_to_directions(std::vector<std::pair<int,int>> &coordinates, int start_cell_x, int start_cell_y){
	for (int i = 0; i < coordinates.size(); ++i){
		if(start_cell_x - 1 == coordinates[i].first){
			start_cell_x--;
			std::cout << "Top ";
		}
		if(start_cell_y + 1 == coordinates[i].second){
			start_cell_y++;
			std::cout << "Right ";
		}
		if(start_cell_x + 1 == coordinates[i].first){
			start_cell_x++;
			std::cout << "Bottom ";
		}
		if(start_cell_y - 1 == coordinates[i].second){
			start_cell_y--;
			std::cout << "Left ";
		}
	}
	std::cout << std::endl << std::endl;
}

void clean_path(std::vector<std::pair<int,int>> &coordinates){
	std::cout << std::endl;
	for (int i = 0; i < coordinates.size(); ++i){
		int count = std::count(coordinates.begin(), coordinates.end(), coordinates[i]);
		if(count > 1){
			auto end_iterator = std::find(coordinates.rbegin(), coordinates.rend(), coordinates[i]);
			if(end_iterator != coordinates.rend()){
				auto idx = std::distance(begin(coordinates), end_iterator.base()) - 1;
				// std::cout << i + 1 << idx << std::endl;
				// std::cout << coordinates[i].first << coordinates[i].second << " " << idx << std::endl;
				coordinates.erase(coordinates.begin() + i, coordinates.begin() + idx);
			}
		}
	}
}

void run_astar(grid_cell **grid_cell_object,
				std::vector<int> &f_func_heap,
				std::vector<std::pair<int, int>> &closed_list,
				std::map<std::pair<int, int>, std::vector<int>> &blocked_list,
				std::multimap<int, std::vector<int>> &f_func_values_map,
				int grid_height, int grid_width,
				int start_cell_x, int start_cell_y,
				int curr_cell_x, int curr_cell_y,
				int target_cell_x, int target_cell_y,
				int mode_for_resolving_tie){
	// std::cout << "Into A*\n";
	// std::cout << curr_cell_x << curr_cell_y <<std::endl;

	bool is_movement_blocked;
	std::vector<int> temp_vector;
	std::vector<int> blocked_directions;
	std::pair<int, int> curr_cell_pair = {curr_cell_x, curr_cell_y};
	std::pair<int, int> next_cell_pair;
	std::map<std::pair<int, int>, std::vector<int>>::iterator iterator;

	closed_list.push_back(curr_cell_pair);
	grid_cell_object[curr_cell_x][curr_cell_y].set_visited_status(true);

	if(curr_cell_x == target_cell_x && curr_cell_y == target_cell_y){
		// std::cout << "GVAL " << grid_cell_object[curr_cell_x][curr_cell_y].get_g_val() << std::endl;
		return;
	}

	next_cell_pair = {curr_cell_x-1, curr_cell_y};
	iterator = blocked_list.find(curr_cell_pair);
	if(iterator == blocked_list.end()){
		is_movement_blocked = false;
	}
	else{
		blocked_directions = iterator->second;
		if (std::binary_search(blocked_directions.begin(), blocked_directions.end(), 1))
			is_movement_blocked = true;
		else
			is_movement_blocked = false;
	}
	if(curr_cell_x > 0 && (!grid_cell_object[curr_cell_x-1][curr_cell_y].get_visited_status()) &&
							(std::find(closed_list.begin(), closed_list.end(), next_cell_pair) == closed_list.end()) &&
							(!is_movement_blocked)){
		grid_cell_object[curr_cell_x-1][curr_cell_y].set_h_val(manhattan_distance(curr_cell_x - 1, curr_cell_y, target_cell_x, target_cell_y));
		grid_cell_object[curr_cell_x-1][curr_cell_y].set_g_val(grid_cell_object[curr_cell_x][curr_cell_y].get_g_val() + 1);
		grid_cell_object[curr_cell_x-1][curr_cell_y].set_f_val(grid_cell_object[curr_cell_x-1][curr_cell_y].get_h_val() +
																grid_cell_object[curr_cell_x-1][curr_cell_y].get_g_val());
		temp_vector = {};
		f_func_heap.push_back(grid_cell_object[curr_cell_x-1][curr_cell_y].get_f_val());
		temp_vector.push_back(grid_cell_object[curr_cell_x-1][curr_cell_y].get_h_val());
		temp_vector.push_back(grid_cell_object[curr_cell_x-1][curr_cell_y].get_g_val());
		temp_vector.push_back(curr_cell_x - 1);
		temp_vector.push_back(curr_cell_y);
		f_func_values_map.insert(std::pair<int,std::vector<int>> (grid_cell_object[curr_cell_x-1][curr_cell_y].get_f_val(), temp_vector));
		grid_cell_object[curr_cell_x-1][curr_cell_y].set_visited_status(true);
		grid_cell_object[curr_cell_x-1][curr_cell_y].set_parent_x(curr_cell_x);
		grid_cell_object[curr_cell_x-1][curr_cell_y].set_parent_y(curr_cell_y);
	}

	next_cell_pair = {curr_cell_x, curr_cell_y+1};
	iterator = blocked_list.find(curr_cell_pair);
	if(iterator == blocked_list.end()){
		is_movement_blocked = false;
	}
	else{
		blocked_directions = iterator->second;
		if (std::binary_search(blocked_directions.begin(), blocked_directions.end(), 2))
			is_movement_blocked = true;
		else
			is_movement_blocked = false;
	}
	if (curr_cell_y < grid_width - 1 && (!grid_cell_object[curr_cell_x][curr_cell_y+1].get_visited_status()) &&
										(std::find(closed_list.begin(), closed_list.end(), next_cell_pair) == closed_list.end()) &&
										(!is_movement_blocked)){
		grid_cell_object[curr_cell_x][curr_cell_y+1].set_h_val(manhattan_distance(curr_cell_x, curr_cell_y + 1, target_cell_x, target_cell_y));
		grid_cell_object[curr_cell_x][curr_cell_y+1].set_g_val(grid_cell_object[curr_cell_x][curr_cell_y].get_g_val() + 1);
		grid_cell_object[curr_cell_x][curr_cell_y+1].set_f_val(grid_cell_object[curr_cell_x][curr_cell_y+1].get_h_val() +
																grid_cell_object[curr_cell_x][curr_cell_y+1].get_g_val());
		temp_vector = {};
		f_func_heap.push_back(grid_cell_object[curr_cell_x][curr_cell_y+1].get_f_val());
		temp_vector.push_back(grid_cell_object[curr_cell_x][curr_cell_y+1].get_h_val());
		temp_vector.push_back(grid_cell_object[curr_cell_x][curr_cell_y+1].get_g_val());
		temp_vector.push_back(curr_cell_x);
		temp_vector.push_back(curr_cell_y + 1);
		f_func_values_map.insert(std::pair<int,std::vector<int>> (grid_cell_object[curr_cell_x][curr_cell_y+1].get_f_val(), temp_vector));
		grid_cell_object[curr_cell_x][curr_cell_y+1].set_visited_status(true);
		grid_cell_object[curr_cell_x][curr_cell_y+1].set_parent_x(curr_cell_x);
		grid_cell_object[curr_cell_x][curr_cell_y+1].set_parent_y(curr_cell_y);
	}

	next_cell_pair = {curr_cell_x+1, curr_cell_y};
	iterator = blocked_list.find(curr_cell_pair);
	if(iterator == blocked_list.end()){
		is_movement_blocked = false;
	}
	else{
		blocked_directions = iterator->second;
		if (std::binary_search(blocked_directions.begin(), blocked_directions.end(), 3))
			is_movement_blocked = true;
		else
			is_movement_blocked = false;
	}
	if (curr_cell_x < grid_height - 1 && (!grid_cell_object[curr_cell_x+1][curr_cell_y].get_visited_status()) &&
										(std::find(closed_list.begin(), closed_list.end(), next_cell_pair) == closed_list.end()) &&
										(!is_movement_blocked)){
		grid_cell_object[curr_cell_x+1][curr_cell_y].set_h_val(manhattan_distance(curr_cell_x+1, curr_cell_y, target_cell_x, target_cell_y));
		grid_cell_object[curr_cell_x+1][curr_cell_y].set_g_val(grid_cell_object[curr_cell_x][curr_cell_y].get_g_val() + 1);
		grid_cell_object[curr_cell_x+1][curr_cell_y].set_f_val(grid_cell_object[curr_cell_x+1][curr_cell_y].get_h_val() +
																grid_cell_object[curr_cell_x+1][curr_cell_y].get_g_val());
		temp_vector = {};
		f_func_heap.push_back(grid_cell_object[curr_cell_x+1][curr_cell_y].get_f_val());
		temp_vector.push_back(grid_cell_object[curr_cell_x+1][curr_cell_y].get_h_val());
		temp_vector.push_back(grid_cell_object[curr_cell_x+1][curr_cell_y].get_g_val());
		temp_vector.push_back(curr_cell_x+1);
		temp_vector.push_back(curr_cell_y);
		f_func_values_map.insert(std::pair<int,std::vector<int>> (grid_cell_object[curr_cell_x+1][curr_cell_y].get_f_val(), temp_vector));
		grid_cell_object[curr_cell_x+1][curr_cell_y].set_visited_status(true);
		grid_cell_object[curr_cell_x+1][curr_cell_y].set_parent_x(curr_cell_x);
		grid_cell_object[curr_cell_x+1][curr_cell_y].set_parent_y(curr_cell_y);
	}

	next_cell_pair = {curr_cell_x, curr_cell_y-1};
	iterator = blocked_list.find(curr_cell_pair);
	if(iterator == blocked_list.end()){
		is_movement_blocked = false;
	}
	else{
		blocked_directions = iterator->second;
		if (std::binary_search(blocked_directions.begin(), blocked_directions.end(), 4))
			is_movement_blocked = true;
		else
			is_movement_blocked = false;
	}

	if(curr_cell_y > 0 && (!grid_cell_object[curr_cell_x][curr_cell_y-1].get_visited_status()) &&
							(std::find(closed_list.begin(), closed_list.end(), next_cell_pair) == closed_list.end()) &&
							(!is_movement_blocked)){
		grid_cell_object[curr_cell_x][curr_cell_y-1].set_h_val(manhattan_distance(curr_cell_x, curr_cell_y-1, target_cell_x, target_cell_y));
		grid_cell_object[curr_cell_x][curr_cell_y-1].set_g_val(grid_cell_object[curr_cell_x][curr_cell_y].get_g_val() + 1);
		grid_cell_object[curr_cell_x][curr_cell_y-1].set_f_val(grid_cell_object[curr_cell_x][curr_cell_y-1].get_h_val() +
																grid_cell_object[curr_cell_x][curr_cell_y-1].get_g_val());
		temp_vector = {};
		f_func_heap.push_back(grid_cell_object[curr_cell_x][curr_cell_y-1].get_f_val());
		temp_vector.push_back(grid_cell_object[curr_cell_x][curr_cell_y-1].get_h_val());
		temp_vector.push_back(grid_cell_object[curr_cell_x][curr_cell_y-1].get_g_val());
		temp_vector.push_back(curr_cell_x);
		temp_vector.push_back(curr_cell_y-1);
		f_func_values_map.insert(std::pair<int,std::vector<int>> (grid_cell_object[curr_cell_x][curr_cell_y-1].get_f_val(), temp_vector));
		grid_cell_object[curr_cell_x][curr_cell_y-1].set_visited_status(true);
		grid_cell_object[curr_cell_x][curr_cell_y-1].set_parent_x(curr_cell_x);
		grid_cell_object[curr_cell_x][curr_cell_y-1].set_parent_y(curr_cell_y);
	}

	make_heap(f_func_heap.begin(), f_func_heap.end());
	sort_heap(f_func_heap.begin(), f_func_heap.end());

	int best_coord_x;
	int best_coord_y;

	bool tie = check_for_tie(f_func_heap.front(), f_func_values_map);
	if(tie){
		resolve_tie(f_func_heap.front(), f_func_values_map, &best_coord_x, &best_coord_y, mode_for_resolving_tie);
	}
	else{
		auto it = f_func_values_map.find(f_func_heap.front());
		best_coord_x = it->second[2];
		best_coord_y = it->second[3];
		f_func_values_map.erase(it);
	}
	f_func_heap.erase(f_func_heap.begin()+0);

	run_astar(grid_cell_object, f_func_heap,
				closed_list, blocked_list,
				f_func_values_map,
				grid_height, grid_width,
				start_cell_x, start_cell_y,
				best_coord_x, best_coord_y,
				target_cell_x, target_cell_y,
				mode_for_resolving_tie);
}
// void run_astar(grid_cell **grid_cell_object,
// 				std::vector<int> &f_func_heap,
// 				std::vector<std::pair<int, int>> &closed_list,
// 				std::multimap<int, std::vector<int>> &f_func_values_map,
// 				int grid_height, int grid_width,
// 				int start_cell_x, int start_cell_y,
// 				int curr_cell_x, int curr_cell_y,
// 				int target_cell_x, int target_cell_y,
// 				int mode_for_resolving_tie){
// 	std::cout << "Into A*\n";
// 	std::vector<int> temp_vector;

// 	std::cout << curr_cell_x << curr_cell_y <<std::endl;
// 	std::pair<int, int> curr_cell_pair = {curr_cell_x, curr_cell_y};
// 	std::pair<int, int> next_cell_pair;
// 	closed_list.push_back(curr_cell_pair);
// 	if(curr_cell_x == target_cell_x && curr_cell_y == target_cell_y){
// 		std::cout << "GVAL " << grid_cell_object[curr_cell_x][curr_cell_y].get_g_val() << std::endl;
// 		return;
// 	}

// 	next_cell_pair = {curr_cell_x-1, curr_cell_y};
// 	if(curr_cell_x > 0 && (!(std::find(closed_list.begin(), closed_list.end(), next_cell_pair) != closed_list.end())) &&
// 							(grid_cell_object[curr_cell_x][curr_cell_y].get_top_neighbour_status() == true ||
// 							grid_cell_object[curr_cell_x-1][curr_cell_y].get_bottom_neighbour_status() == true)){
// 		grid_cell_object[curr_cell_x-1][curr_cell_y].set_h_val(manhattan_distance(curr_cell_x - 1, curr_cell_y, target_cell_x, target_cell_y));
// 		grid_cell_object[curr_cell_x-1][curr_cell_y].set_g_val(grid_cell_object[curr_cell_x][curr_cell_y].get_g_val() + 1);
// 		grid_cell_object[curr_cell_x-1][curr_cell_y].set_f_val(grid_cell_object[curr_cell_x-1][curr_cell_y].get_h_val() +
// 																grid_cell_object[curr_cell_x-1][curr_cell_y].get_g_val());
// 		std::cout << "H&G "<< curr_cell_x-1 << curr_cell_y << " " << grid_cell_object[curr_cell_x-1][curr_cell_y].get_h_val()
// 																	<< grid_cell_object[curr_cell_x-1][curr_cell_y].get_g_val() << std::endl;
// 		temp_vector = {};
// 		f_func_heap.push_back(grid_cell_object[curr_cell_x-1][curr_cell_y].get_f_val());
// 		temp_vector.push_back(grid_cell_object[curr_cell_x-1][curr_cell_y].get_h_val());
// 		temp_vector.push_back(grid_cell_object[curr_cell_x-1][curr_cell_y].get_g_val());
// 		temp_vector.push_back(curr_cell_x - 1);
// 		temp_vector.push_back(curr_cell_y);
// 		f_func_values_map.insert(std::pair<int,std::vector<int>> (grid_cell_object[curr_cell_x-1][curr_cell_y].get_f_val(), temp_vector));
// 	}

// 	next_cell_pair = {curr_cell_x, curr_cell_y+1};
// 	if (curr_cell_y < grid_width - 1 && (!(std::find(closed_list.begin(), closed_list.end(), next_cell_pair) != closed_list.end())) &&
// 										(grid_cell_object[curr_cell_x][curr_cell_y].get_right_neighbour_status() == true ||
// 										grid_cell_object[curr_cell_x][curr_cell_y+1].get_left_neighbour_status() == true)){
// 		grid_cell_object[curr_cell_x][curr_cell_y+1].set_h_val(manhattan_distance(curr_cell_x, curr_cell_y + 1, target_cell_x, target_cell_y));
// 		grid_cell_object[curr_cell_x][curr_cell_y+1].set_g_val(grid_cell_object[curr_cell_x][curr_cell_y].get_g_val() + 1);
// 		grid_cell_object[curr_cell_x][curr_cell_y+1].set_f_val(grid_cell_object[curr_cell_x][curr_cell_y+1].get_h_val() +
// 																grid_cell_object[curr_cell_x][curr_cell_y+1].get_g_val());
// 		std::cout << "H&G "<< curr_cell_x << curr_cell_y << " " << grid_cell_object[curr_cell_x][curr_cell_y+1].get_h_val()
// 																	<< grid_cell_object[curr_cell_x][curr_cell_y+1].get_g_val() << std::endl;
// 		temp_vector = {};
// 		f_func_heap.push_back(grid_cell_object[curr_cell_x][curr_cell_y+1].get_f_val());
// 		temp_vector.push_back(grid_cell_object[curr_cell_x][curr_cell_y+1].get_h_val());
// 		temp_vector.push_back(grid_cell_object[curr_cell_x][curr_cell_y+1].get_g_val());
// 		temp_vector.push_back(curr_cell_x);
// 		temp_vector.push_back(curr_cell_y + 1);
// 		f_func_values_map.insert(std::pair<int,std::vector<int>> (grid_cell_object[curr_cell_x][curr_cell_y+1].get_f_val(), temp_vector));
// 	}

// 	next_cell_pair = {curr_cell_x+1, curr_cell_y};
// 	if (curr_cell_x < grid_height - 1 && (!(std::find(closed_list.begin(), closed_list.end(), next_cell_pair) != closed_list.end())) &&
// 										(grid_cell_object[curr_cell_x][curr_cell_y].get_bottom_neighbour_status() == true ||
// 										grid_cell_object[curr_cell_x+1][curr_cell_y].get_top_neighbour_status() == true)){
// 		grid_cell_object[curr_cell_x+1][curr_cell_y].set_h_val(manhattan_distance(curr_cell_x+1, curr_cell_y, target_cell_x, target_cell_y));
// 		grid_cell_object[curr_cell_x+1][curr_cell_y].set_g_val(grid_cell_object[curr_cell_x][curr_cell_y].get_g_val() + 1);
// 		grid_cell_object[curr_cell_x+1][curr_cell_y].set_f_val(grid_cell_object[curr_cell_x+1][curr_cell_y].get_h_val() +
// 																grid_cell_object[curr_cell_x+1][curr_cell_y].get_g_val());
// 		std::cout << "H&G "<< curr_cell_x+1 << curr_cell_y << " " << grid_cell_object[curr_cell_x+1][curr_cell_y].get_h_val()
// 																	<< grid_cell_object[curr_cell_x+1][curr_cell_y].get_g_val() << std::endl;
// 		temp_vector = {};
// 		f_func_heap.push_back(grid_cell_object[curr_cell_x+1][curr_cell_y].get_f_val());
// 		temp_vector.push_back(grid_cell_object[curr_cell_x+1][curr_cell_y].get_h_val());
// 		temp_vector.push_back(grid_cell_object[curr_cell_x+1][curr_cell_y].get_g_val());
// 		temp_vector.push_back(curr_cell_x+1);
// 		temp_vector.push_back(curr_cell_y);
// 		f_func_values_map.insert(std::pair<int,std::vector<int>> (grid_cell_object[curr_cell_x+1][curr_cell_y].get_f_val(), temp_vector));
// 	}

// 	next_cell_pair = {curr_cell_x, curr_cell_y-1};
// 	if(curr_cell_y > 0 && (!(std::find(closed_list.begin(), closed_list.end(), next_cell_pair) != closed_list.end())) &&
// 							(grid_cell_object[curr_cell_x][curr_cell_y].get_left_neighbour_status() == true ||
// 							grid_cell_object[curr_cell_x][curr_cell_y-1].get_right_neighbour_status() == true)){
// 		grid_cell_object[curr_cell_x][curr_cell_y-1].set_h_val(manhattan_distance(curr_cell_x, curr_cell_y-1, target_cell_x, target_cell_y));
// 		grid_cell_object[curr_cell_x][curr_cell_y-1].set_g_val(grid_cell_object[curr_cell_x][curr_cell_y].get_g_val() + 1);
// 		grid_cell_object[curr_cell_x][curr_cell_y-1].set_f_val(grid_cell_object[curr_cell_x][curr_cell_y-1].get_h_val() +
// 																grid_cell_object[curr_cell_x][curr_cell_y-1].get_g_val());
// 		std::cout << "H&G "<< curr_cell_x << curr_cell_y << " " << grid_cell_object[curr_cell_x][curr_cell_y-1].get_h_val()
// 																	<< grid_cell_object[curr_cell_x][curr_cell_y-1].get_g_val() << std::endl;
// 		temp_vector = {};
// 		f_func_heap.push_back(grid_cell_object[curr_cell_x][curr_cell_y-1].get_f_val());
// 		temp_vector.push_back(grid_cell_object[curr_cell_x][curr_cell_y-1].get_h_val());
// 		temp_vector.push_back(grid_cell_object[curr_cell_x][curr_cell_y-1].get_g_val());
// 		temp_vector.push_back(curr_cell_x);
// 		temp_vector.push_back(curr_cell_y-1);
// 		f_func_values_map.insert(std::pair<int,std::vector<int>> (grid_cell_object[curr_cell_x][curr_cell_y-1].get_f_val(), temp_vector));
// 	}

// 	// std::cout << "Before Make Heap " << curr_cell_x << curr_cell_y <<std::endl;
// 	// for (int i = 0; i < f_func_heap.size(); ++i){
// 	// 	std::cout << f_func_heap[i] << std::endl;
// 	// }
// 	make_heap(f_func_heap.begin(), f_func_heap.end());
// 	// std::cout << "After Make Heap " << curr_cell_x << curr_cell_y <<std::endl;
// 	// for (int i = 0; i < f_func_heap.size(); ++i){
// 	// 	std::cout << f_func_heap[i] << std::endl;
// 	// }

// 	// std::cout << "Before Sort Heap " << curr_cell_x << curr_cell_y <<std::endl;
// 	// for (int i = 0; i < f_func_heap.size(); ++i){
// 	// 	std::cout << f_func_heap[i] << std::endl;
// 	// }
// 	sort_heap(f_func_heap.begin(), f_func_heap.end());
// 	// std::cout << "After Sort Heap " << curr_cell_x << curr_cell_y <<std::endl;
// 	// for (int i = 0; i < f_func_heap.size(); ++i){
// 	// 	std::cout << f_func_heap[i] << std::endl;
// 	// }

// 	int best_coord_x;
// 	int best_coord_y;

// 	std::cout << "Before Tie Check " << curr_cell_x << curr_cell_y <<std::endl;
// 	bool tie = check_for_tie(f_func_heap.front(), f_func_values_map);
// 	std::cout << "Before Tie Resolve IF" << curr_cell_x << curr_cell_y <<std::endl;
// 	if(tie){
// 		std::cout << "Inside Tie Resolve IF" << curr_cell_x << curr_cell_y <<std::endl;
// 		resolve_tie(f_func_heap.front(), f_func_values_map, &best_coord_x, &best_coord_y, mode_for_resolving_tie);
// 		std::cout << "Inside Tie Resolve IF " << curr_cell_x << curr_cell_y <<std::endl;
// 		std::cout << "Inside Tie Resolve IF Best X, Best Y for expanding " << best_coord_x << best_coord_y <<std::endl;
// 	}
// 	else{
// 		std::cout << "Else of Ties Resolve " << curr_cell_x << curr_cell_y <<std::endl;
// 		auto it = f_func_values_map.find(f_func_heap.front());
// 		best_coord_x = it->second[2];
// 		best_coord_y = it->second[3];
// 		f_func_values_map.erase(it);
// 		std::cout << "Else of Tie Resolve " << curr_cell_x << curr_cell_y <<std::endl;
// 		std::cout << "Else of Tie Resolve Best X, Best Y for expanding " << best_coord_x << best_coord_y <<std::endl;
// 	}
// 	std::cout << "After removing the Least Element " << curr_cell_x << curr_cell_y <<std::endl;
// 	// pop_heap(f_func_heap.begin(), f_func_heap.end());
// 	f_func_heap.erase(f_func_heap.begin()+0);
// 	for (int i = 0; i < f_func_heap.size(); ++i){
// 		std::cout << f_func_heap[i] << std::endl;
// 	}
// 	// if(curr_cell_x ==0 && curr_cell_y ==2)
// 	// 	return;
// 	run_astar(grid_cell_object,
// 				f_func_heap,
// 				closed_list,
// 				f_func_values_map,
// 				grid_height, grid_width,
// 				start_cell_x, start_cell_y,
// 				best_coord_x, best_coord_y,
// 				target_cell_x, target_cell_y,
// 				mode_for_resolving_tie);
// }
