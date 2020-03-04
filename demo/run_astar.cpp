#include <iostream>
#include <chrono>
#include <fstream>

#include <astar_env_gen.hpp>
#include <a_star.hpp>
#include <forward_repetitive_astar.hpp>
#include <backward_repetitive_astar.hpp>
#include <adaptive_astar.hpp>

int main(int argc, char const *argv[])
{
	int num_grid_cells = 50;
	int grid_height = 10;
	int grid_width = 10;
	int starting_point_x;
	int starting_point_y;
	grid_cell **grid_cell_object = init_env(grid_height, grid_width, &starting_point_x, &starting_point_y);
	grid_cell_object = generate_astar_env(grid_cell_object, grid_height, grid_width, 0, 0);
	// std::ofstream file_obj;
	// file_obj.open("file.dat",std::ios_base::out | std::ios_base::binary);
	// grid_cell_object->serialize(file_obj, true);
	// file_obj.close();
	// exit(1);
    // Opening file in append mode
    // file_obj.open("Input.txt", ios::app);
    // file_obj.write((char*)&grid_cell_object, sizeof(grid_cell_object));
	for(int index = 0; index < num_grid_cells; index++){
		visualize_maze_grid(grid_cell_object, grid_height, grid_width);
		// exit(1);

		int start_cell_x = 0;
		int start_cell_y = 0;
		int target_cell_x = 9;
		int target_cell_y = 9;
		int mode_for_resolving_tie = 1;

		// auto bwd_start = std::chrono::high_resolution_clock::now();
		// backward_repetitive_astar(grid_cell_object,
		// 						grid_height, grid_width,
		// 						target_cell_x, target_cell_y,
		// 						start_cell_x, start_cell_y,
		// 						mode_for_resolving_tie);
		// auto bwd_stop = std::chrono::high_resolution_clock::now();
		// auto bwd_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(bwd_stop - bwd_start);
		// std::cout << "Backward repititve A star " << bwd_duration.count()/1000 << std::endl;

		auto fwd_start = std::chrono::high_resolution_clock::now();
		forward_repetitive_astar(grid_cell_object,
								grid_height, grid_width,
								start_cell_x, start_cell_y,
								target_cell_x, target_cell_y,
								mode_for_resolving_tie);
		auto fwd_stop = std::chrono::high_resolution_clock::now();
		auto fwd_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(fwd_stop - fwd_start);
		std::cout << "Forward repititve A star " << fwd_duration.count()/1000 << std::endl;
		// mode_for_resolving_tie = 0;

		// auto bwd_start = std::chrono::high_resolution_clock::now();
		// backward_repetitive_astar(grid_cell_object,
		// 						grid_height, grid_width,
		// 						target_cell_x, target_cell_y,
		// 						start_cell_x, start_cell_y,
		// 						mode_for_resolving_tie);
		// auto bwd_stop = std::chrono::high_resolution_clock::now();
		// auto bwd_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(bwd_stop - bwd_start);
		// std::cout << "Backward repititve A star " << bwd_duration.count()/1000 << std::endl;

		// auto fwd1_start = std::chrono::high_resolution_clock::now();
		// forward_repetitive_astar(grid_cell_object,
		// 						grid_height, grid_width,
		// 						start_cell_x, start_cell_y,
		// 						target_cell_x, target_cell_y,
		// 						mode_for_resolving_tie);
		// auto fwd1_stop = std::chrono::high_resolution_clock::now();
		// auto fwd1_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(fwd1_stop - fwd1_start);
		// std::cout << "Forward repititve A star " << fwd1_duration.count()/1000 << std::endl;

		// auto adap_start = std::chrono::high_resolution_clock::now();
		// adaptive_astar(grid_cell_object,
		// 						grid_height, grid_width,
		// 						start_cell_x, start_cell_y,
		// 						target_cell_x, target_cell_y,
		// 						mode_for_resolving_tie);
		// auto adap_stop = std::chrono::high_resolution_clock::now();
		// auto adap_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(adap_stop - adap_start);
		// std::cout << "Adaptive A star " << adap_duration.count()/1000 << std::endl;

		exit(1);
		// break;
	}
		destroy_astart_env(grid_cell_object, grid_height, grid_width);
	return 0;
}
