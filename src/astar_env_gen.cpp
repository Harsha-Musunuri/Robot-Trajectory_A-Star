//Direction 1-Top, 2-Right, 3-Down, 4-Left

#include <astar_env_gen.hpp>
using namespace std;
bool check_for_bounds(int grid_height, int grid_width, int point_x, int point_y, int direction){
    switch(direction){
    	case 1:
    		if ((point_x - 1) < 0)
    			return false;
    		return true;
    	case 2:
    		if ((point_y + 1) >= grid_width)
    			return false;
    		return true;
    	case 3:
    		if ((point_x + 1) >= grid_height)
    			return false;
    		return true;
    	case 4:
    		if ((point_y - 1) < 0)
    			return false;
    		return true;
    	default:
    		std::cout << "Direction is not possible" <<std::endl;
    		exit(1);
    }
}

grid_cell **init_env(int grid_height, int grid_width, int *starting_point_x, int *starting_point_y){
	grid_cell **grid_cell_object = (grid_cell**)malloc(grid_height * sizeof(grid_cell*));

	for(int index = 0; index < grid_width; index ++){
		grid_cell_object[index] = (grid_cell*)malloc(grid_width * sizeof(grid_cell));
	}

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> point_x(0,grid_width-1);
    std::uniform_int_distribution<std::mt19937::result_type> point_y(0,grid_height-1);
    *(starting_point_x) = point_x(rng);
    *(starting_point_y) = point_y(rng);

    return grid_cell_object;
}

bool are_neighbouring_cells_visited(grid_cell **grid_cell_object, int grid_height, int grid_width,
									int point_x, int point_y, std::set<int> &invalid_directions){
    bool return_cond = true;
    if(point_x >= 1){
        	if(grid_cell_object[point_x-1][point_y].get_visited_status() == false){
    		return_cond = false;
    	}
    	else{
    		invalid_directions.insert(1);
    	}
    }
    if(point_x < grid_width - 1){
    	if(grid_cell_object[point_x+1][point_y].get_visited_status() == false){
    		return_cond = false;
    	}
    	else{
	    	invalid_directions.insert(3);
    	}
    }
    if(point_y >= 1){
    	if(grid_cell_object[point_x][point_y-1].get_visited_status() == false){
    		return_cond = false;
    	}
    	else{
    		invalid_directions.insert(4);
    	}
    }
    if(point_y < grid_height - 1){
    	if(grid_cell_object[point_x][point_y+1].get_visited_status() == false){
    		return_cond = false;
    	}
    	else{
    		invalid_directions.insert(2);
    	}
    }
    return return_cond;
}

grid_cell **generate_astar_env(grid_cell **grid_cell_object, int grid_height, int grid_width, int point_x, int point_y){
	grid_cell_object[point_x][point_y].set_visited_status(1);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> direction(1,4);
    int curr_direction = direction(rng);
    bool return_cond = true;
    std::set<int> invalid_directions;

    return_cond = are_neighbouring_cells_visited(grid_cell_object, grid_height, grid_width, point_x, point_y, invalid_directions);

	if(return_cond == true)
		return grid_cell_object;

    bool is_direction_correct = false;
    while(!is_direction_correct){
    	is_direction_correct = check_for_bounds(grid_height, grid_width, point_x, point_y, curr_direction);
		std::set<int>::iterator it = invalid_directions.find(curr_direction);
		if(it == invalid_directions.end() && is_direction_correct == true)
			is_direction_correct = true;
		else
			is_direction_correct = false;
		if(is_direction_correct == false)
	    	curr_direction = direction(rng);
    }

	std::set<int> temp_invalid_dir;
	bool temp_return_cond;

    switch(curr_direction){
    	case 1:
			grid_cell_object[point_x][point_y].set_top_neighbour_status(true);
			grid_cell_object = generate_astar_env(grid_cell_object, grid_height, grid_width, point_x-1, point_y);
		    temp_return_cond = are_neighbouring_cells_visited(grid_cell_object, grid_height, grid_width, point_x, point_y, temp_invalid_dir);
		    temp_invalid_dir.clear();
		    if(temp_return_cond == false){
				grid_cell_object = generate_astar_env(grid_cell_object, grid_height, grid_width, point_x, point_y);
		    }
    		break;
    	case 2:
			grid_cell_object[point_x][point_y].set_right_neighbour_status(true);
			grid_cell_object = generate_astar_env(grid_cell_object, grid_height, grid_width, point_x, point_y+1);
    		temp_invalid_dir.clear();
		    temp_return_cond = are_neighbouring_cells_visited(grid_cell_object, grid_height, grid_width, point_x, point_y, temp_invalid_dir);
		    if(temp_return_cond == false){
				grid_cell_object = generate_astar_env(grid_cell_object, grid_height, grid_width, point_x, point_y);
		    }
    		break;
    	case 3:
			grid_cell_object[point_x][point_y].set_bottom_neighbour_status(true);
			grid_cell_object = generate_astar_env(grid_cell_object, grid_height, grid_width, point_x+1, point_y);
    		temp_invalid_dir.clear();
		    temp_return_cond = are_neighbouring_cells_visited(grid_cell_object, grid_height, grid_width, point_x, point_y, temp_invalid_dir);
		    if(temp_return_cond == false){
				grid_cell_object = generate_astar_env(grid_cell_object, grid_height, grid_width, point_x, point_y);
		    }
    		break;
    	case 4:
			grid_cell_object[point_x][point_y].set_left_neighbour_status(true);
			grid_cell_object = generate_astar_env(grid_cell_object, grid_height, grid_width, point_x, point_y-1);
    		temp_invalid_dir.clear();
		    temp_return_cond = are_neighbouring_cells_visited(grid_cell_object, grid_height, grid_width, point_x, point_y, temp_invalid_dir);
		    if(temp_return_cond == false){
				grid_cell_object = generate_astar_env(grid_cell_object, grid_height, grid_width, point_x, point_y);
		    }
    		break;
    	default:
    		std::cout << "default\n";
    		break;
    }
}

void destroy_astart_env(grid_cell **grid_cell_object, int grid_height, int grid_width){
	for(int index = 0; index < grid_width; index ++){
		free(grid_cell_object[index]);
	}
	free(grid_cell_object);
}

void visualize_maze_grid(grid_cell **grid_cell_object, int grid_height, int grid_width){
	int total = 5 * grid_width;
	char c;

	std::vector<std::pair<int, int>> horizontal_coord_pairs;
	std::vector<std::pair<int, int>> vertical_coord_pairs;

	for (int i = 0; i < grid_height; ++i){
		for (int j = 0; j < grid_width - 1; ++j){
			if(grid_cell_object[i][j].get_right_neighbour_status()){
				std::pair<int, int> temp_pair(i, j+1);
				horizontal_coord_pairs.push_back(temp_pair);
			}
		}
	}

	for (int i = 0; i < grid_height; ++i){
		for (int j = 1; j < grid_width; ++j){
			if(grid_cell_object[i][j].get_left_neighbour_status()){
				std::pair<int, int> temp_pair(i, j);
				horizontal_coord_pairs.push_back(temp_pair);
			}
		}
	}

	for (int i = 0; i < grid_height - 1; ++i){
		for (int j = 0; j < grid_width; ++j){
			if(grid_cell_object[i][j].get_bottom_neighbour_status()){
				std::pair<int, int> temp_pair(i+1, j);
				vertical_coord_pairs.push_back(temp_pair);
			}
		}
	}

	for (int i = 1; i < grid_height; ++i){
		for (int j = 0; j < grid_width; ++j){
			if(grid_cell_object[i][j].get_top_neighbour_status()){
				std::pair<int, int> temp_pair(i, j);
				vertical_coord_pairs.push_back(temp_pair);
			}
		}
	}

	total = 5 * grid_width;
	c = ' ';
	for (int i = 0; i <= total; ++i){
		for (int k = 0; k <= total; ++k){
			if(i % 5 == 0){
				int x = i/5;
				int y = k/5;
				std::pair<int,int> temp_pair(x,y);
				if(std::find(vertical_coord_pairs.begin(), vertical_coord_pairs.end(), temp_pair) != vertical_coord_pairs.end()){
					c = ' ';
				}
				else
					c = '*';
			}
			else if(k % 5 == 0){
				int x = i/5;
				int y = k/5;
				std::pair<int,int> temp_pair(x,y);
				if(std::find(horizontal_coord_pairs.begin(), horizontal_coord_pairs.end(), temp_pair) != horizontal_coord_pairs.end()){
					c = ' ';
				}
				else
					c = '*';
			}
			else {
				c = ' ';
			}
			std::cout << c;
		}
		std::cout << std::endl;
	}
}
