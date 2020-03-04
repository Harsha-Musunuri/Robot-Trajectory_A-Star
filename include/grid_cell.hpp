#ifndef __GRID_CELL_HPP__
#define __GRID_CELL_HPP__

#include <iostream>

class grid_cell
{
private:
	bool top=false, bottom=false, left=false, right=false;
	int visited_status = 0; //0 if blocked, 1 if unblocked
	int h_val;
	int g_val;
	int g_prev;
	int f_val;
	int parent_x, parent_y;
public:
	grid_cell();
	~grid_cell();

	int get_visited_status(){
		return this->visited_status;
	}
	void set_visited_status(int visited_status){
		this->visited_status = visited_status;
	}

	bool get_top_neighbour_status(){
		return this->top;
	}
	bool get_right_neighbour_status(){
		return this->right;
	}
	bool get_bottom_neighbour_status(){
		return this->bottom;
	}
	bool get_left_neighbour_status(){
		return this->left;
	}
	void set_top_neighbour_status(bool status){
		this->top = status;
	}
	void set_right_neighbour_status(bool status){
		this->right = status;
	}
	void set_bottom_neighbour_status(bool status){
		this->bottom = status;
	}
	void set_left_neighbour_status(bool status){
		this->left = status;
	}

	int get_h_val(){
		return this->h_val;
	}
	int get_g_val(){
		return this->g_val;
	}
	int get_f_val(){
		return this->f_val;
	}
	void set_h_val(int h_val){
		this->h_val = h_val;
	}
	void set_g_val(int g_val){
		this->g_val = g_val;
	}
	void set_f_val(int f_val){
		this->f_val = f_val;
	}

	int get_parent_x(){
		return this->parent_x;
	}
	int get_parent_y(){
		return this->parent_y;
	}
	void set_parent_x(int parent_x){
		this->parent_x = parent_x;
	}
	void set_parent_y(int parent_y){
		this->parent_y = parent_y;
	}

	int get_g_prev(){
		return this->g_prev;
	}
	void set_g_prev(int g_prev){
		this->g_prev = g_prev;
	}


};


#endif
