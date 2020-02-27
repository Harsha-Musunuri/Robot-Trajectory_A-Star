#include <iostream>

#include <astar_env_gen.hpp>
#include <a_star.hpp>
#include <forward_repetitive_astar.hpp>
#include <backward_repetitive_astar.hpp>

int main(int argc, char const *argv[])
{
	int num_grid_cells = 50;
	int grid_height = 101;
	int grid_width = 101;
	for(int index = 0; index < num_grid_cells; index++){
		int starting_point_x;
		int starting_point_y;
		grid_cell **grid_cell_object = init_env(grid_height, grid_width, &starting_point_x, &starting_point_y);
		grid_cell_object = generate_astar_env(grid_cell_object, grid_height, grid_width, 2, 2);
		visualize_maze_grid(grid_cell_object, grid_height, grid_width);
		// exit(1);

		int start_cell_x = 0;
		int start_cell_y = 0;
		int target_cell_x = 74;
		int target_cell_y = 74;
		int mode_for_resolving_tie = 0;

		forward_repetitive_astar(grid_cell_object,
								grid_height, grid_width,
								start_cell_x, start_cell_y,
								target_cell_x, target_cell_y,
								mode_for_resolving_tie);
		backward_repetitive_astar(grid_cell_object,
								grid_height, grid_width,
								target_cell_x, target_cell_y,
								start_cell_x, start_cell_y,
								mode_for_resolving_tie);

		exit(1);
		// destroy_astart_env(grid_cell_object, grid_height, grid_width);
		break;
	}
	return 0;
}
		// for(int i = 0; i < 5; i++){
		// 	for(int j = 0; j<5; j++){
		// 		grid_cell_object[i][j].set_top_neighbour_status(true);
		// 		grid_cell_object[i][j].set_right_neighbour_status(true);
		// 		grid_cell_object[i][j].set_bottom_neighbour_status(true);
		// 		grid_cell_object[i][j].set_left_neighbour_status(true);
		// 	}
		// }

		// grid_cell_object[0][1].set_bottom_neighbour_status(false);
		// grid_cell_object[1][1].set_top_neighbour_status(false);
		// grid_cell_object[0][2].set_bottom_neighbour_status(false);
		// grid_cell_object[1][2].set_top_neighbour_status(false);
		// grid_cell_object[0][3].set_bottom_neighbour_status(false);
		// grid_cell_object[1][3].set_top_neighbour_status(false);
		// grid_cell_object[0][4].set_bottom_neighbour_status(false);
		// grid_cell_object[1][4].set_top_neighbour_status(false);

		// grid_cell_object[0][0].set_right_neighbour_status(false);
		// grid_cell_object[0][1].set_left_neighbour_status(false);
		// grid_cell_object[0][2].set_right_neighbour_status(false);
		// grid_cell_object[0][3].set_left_neighbour_status(false);

		// grid_cell_object[1][0].set_right_neighbour_status(false);
		// grid_cell_object[1][1].set_left_neighbour_status(false);
		// grid_cell_object[1][1].set_right_neighbour_status(false);
		// grid_cell_object[1][2].set_left_neighbour_status(false);
		// grid_cell_object[1][3].set_right_neighbour_status(false);
		// grid_cell_object[1][4].set_left_neighbour_status(false);

		// grid_cell_object[2][1].set_right_neighbour_status(false);
		// grid_cell_object[2][2].set_left_neighbour_status(false);
		// grid_cell_object[2][2].set_right_neighbour_status(false);
		// grid_cell_object[2][3].set_left_neighbour_status(false);
		// grid_cell_object[2][3].set_right_neighbour_status(false);
		// grid_cell_object[2][4].set_left_neighbour_status(false);

		// grid_cell_object[3][1].set_right_neighbour_status(false);
		// grid_cell_object[3][2].set_left_neighbour_status(false);
		// grid_cell_object[3][2].set_right_neighbour_status(false);
		// grid_cell_object[3][3].set_left_neighbour_status(false);
		// grid_cell_object[3][3].set_right_neighbour_status(false);
		// grid_cell_object[3][4].set_left_neighbour_status(false);

		// grid_cell_object[4][1].set_right_neighbour_status(false);
		// grid_cell_object[4][2].set_left_neighbour_status(false);

		// grid_cell_object[1][2].set_bottom_neighbour_status(false);
		// grid_cell_object[2][2].set_top_neighbour_status(false);

		// grid_cell_object[2][1].set_bottom_neighbour_status(false);
		// grid_cell_object[3][1].set_top_neighbour_status(false);

		// grid_cell_object[3][0].set_bottom_neighbour_status(false);
		// grid_cell_object[4][0].set_top_neighbour_status(false);
		// grid_cell_object[3][3].set_bottom_neighbour_status(false);
		// grid_cell_object[4][3].set_top_neighbour_status(false);

		// grid_cell_object[1][0].set_right_neighbour_status(false);
		// grid_cell_object[1][1].set_left_neighbour_status(false);
		// grid_cell_object[1][2].set_right_neighbour_status(false);
		// grid_cell_object[1][3].set_left_neighbour_status(false);

		// grid_cell_object[2][1].set_right_neighbour_status(false);
		// grid_cell_object[2][2].set_left_neighbour_status(false);
		// grid_cell_object[2][3].set_right_neighbour_status(false);
		// grid_cell_object[2][4].set_left_neighbour_status(false);

		// grid_cell_object[3][0].set_right_neighbour_status(false);
		// grid_cell_object[3][1].set_left_neighbour_status(false);
		// grid_cell_object[3][2].set_right_neighbour_status(false);
		// grid_cell_object[3][3].set_left_neighbour_status(false);

		// grid_cell_object[1][0].set_bottom_neighbour_status(false);
		// grid_cell_object[2][0].set_top_neighbour_status(false);

		// grid_cell_object[0][1].set_bottom_neighbour_status(false);
		// grid_cell_object[1][1].set_top_neighbour_status(false);
		// grid_cell_object[3][1].set_bottom_neighbour_status(false);
		// grid_cell_object[4][1].set_top_neighbour_status(false);

		// grid_cell_object[1][2].set_bottom_neighbour_status(false);
		// grid_cell_object[2][2].set_top_neighbour_status(false);
		// grid_cell_object[2][2].set_bottom_neighbour_status(false);
		// grid_cell_object[3][2].set_top_neighbour_status(false);
		// grid_cell_object[3][2].set_bottom_neighbour_status(false);
		// grid_cell_object[4][2].set_top_neighbour_status(false);

		// grid_cell_object[0][3].set_bottom_neighbour_status(false);
		// grid_cell_object[1][3].set_top_neighbour_status(false);
		// grid_cell_object[1][3].set_bottom_neighbour_status(false);
		// grid_cell_object[2][3].set_top_neighbour_status(false);
		// grid_cell_object[3][3].set_bottom_neighbour_status(false);
		// grid_cell_object[4][3].set_top_neighbour_status(false);

		// grid_cell_object[2][4].set_bottom_neighbour_status(false);
		// grid_cell_object[3][4].set_top_neighbour_status(false);
