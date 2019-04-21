#include "library.h"

struct coordinates{
	int xvar, yvar;
};


coordinates count_and_read_how_many_strings(string row_of_maze[], int const predefined_size){
	int counter = 0;
	coordinates maze_dimensions;
	maze_dimensions.xvar = 0;
	maze_dimensions.yvar = 0;
	ifstream fin("treasure.txt");
	if (fin.fail()){
		cout << endl << "Error opening file\n";
		fin.close();
		return(maze_dimensions);
	}
	else{
		for (int i = 0; i < predefined_size; i++){
			fin >> row_of_maze[i];
			if (fin.fail()){
				maze_dimensions.yvar = counter;
				maze_dimensions.xvar = row_of_maze[0].length();
				fin.close();
				return(maze_dimensions);
				break;
			}
			else{
				counter++;
			}
		}
	}
}

coordinates detection_of_plus(string row_of_maze[], coordinates maze_dimensions){     //starting point
	coordinates plus_pos;
	for (int j = 0; j < maze_dimensions.yvar; j++){      //the y coordinate
		for (int i = 0; i<maze_dimensions.xvar; i++){    //the x coordinate
			if (row_of_maze[j][i] == '+'){
				plus_pos.xvar = i+1;
				plus_pos.yvar = j+1;
				return(plus_pos);
				break;
			}
		}
	}
}

coordinates detection_of_money(string row_of_maze[], coordinates maze_dimensions){    //end point
	coordinates money_pos;
	for (int j = 0; j<maze_dimensions.yvar; j++){      //the y coordinate
		for (int i = 0; i<maze_dimensions.xvar; i++){    //the x coordinate
			if (row_of_maze[j][i] == '$'){
				money_pos.xvar = i+1;
				money_pos.yvar = j+1;
				return(money_pos);
				break;
			}
		}
	}
}

void draw_box(int i, int j, int const scale, double color[]){
	move_to(i*scale, j*scale);
	//cout << endl << color[0] << " " << color[1] << " " << color[2] << endl;
	set_pen_width(5);
	set_pen_color(color[0], color[1], color[2]);
	set_heading_degrees(90);
	start_shape();
	draw_distance(scale);	note_position();
	turn_right_by_degrees(90);
	draw_distance(scale);	note_position();
	turn_right_by_degrees(90);
	draw_distance(scale);	note_position();
	turn_right_by_degrees(90);
	draw_distance(scale);	note_position();
	fill_shape();
}

void print_maze(string row_of_maze[], coordinates maze_dimensions){
	int const scale = 50;


	//int counter = 0;
	set_pen_color(4);						//if ur having problems with window size, adjust accordingly
	double color[3] = { 100, 4, 6 };
	make_window(maze_dimensions.xvar * scale, maze_dimensions.yvar * scale);
	cout << endl << maze_dimensions.yvar << endl << maze_dimensions.xvar << endl;
	for (int j = 0; j < maze_dimensions.yvar; j++){
		for (int i = 0; i < maze_dimensions.xvar; i++){
			if (row_of_maze[j][i] == '$'){
				color[0] = .94;
				color[1] = .90;
				color[2] = .55;
			}
			else if (row_of_maze[j][i] == '+'){
				color[0] = 1;
				color[1] = 1;
				color[2] = 1;
			}
			else if (row_of_maze[j][i] == 'X'){
				color[0] = 0.08;
				color[1] = 0.28;
				color[2] = 0.20;
				//counter++;			testing if this if-else sequences worked, 148 X's total
			}
			else if (row_of_maze[j][i] == '-'){
				color[0] = 0.86;
				color[1] = 0.27;
				color[2] = 0.02;
			}
			draw_box(i, j, scale, color);
		}
	}
	//cout << endl << counter << endl;
}

void main(){
	coordinates maze_dimensions;
	coordinates plus_pos;
	coordinates money_pos;
	int const predefined_size = 1000;
	string row_of_maze[predefined_size];
	maze_dimensions = count_and_read_how_many_strings(row_of_maze, predefined_size);
	money_pos = detection_of_money(row_of_maze, maze_dimensions);
	plus_pos = detection_of_plus(row_of_maze, maze_dimensions);
	print_maze(row_of_maze, maze_dimensions);
	cout << "money sign: x = " << money_pos.xvar << " y = " << money_pos.yvar << endl;
	cout << "plus sign: x = " << plus_pos.xvar << " y = " << plus_pos.yvar << endl;
	cout << "maze size: x = " << maze_dimensions.xvar << " y = " << maze_dimensions.yvar << endl;
}
