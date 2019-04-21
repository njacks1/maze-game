#include "library.h"
/*
void read_maze(){
ifstream fin("treasure.txt");
if(fin.fail()){
cout << endl << "Error opening file\n";
}
else{
for(int j = 0; j<size; j++){
for(int i = 0; i<size; i++){
fin >> string[j][i];
}
}
}
}
*/

struct coordinates{
	int xvar, yvar;
};


coordinates count_and_read_how_many_strings(string row_of_maze[], int const predefined_size){
	int counter = 0;
	int counter_2 = 0;
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
				fin.close();
				break;
			}
			else{
				counter++;
			}
		}
		for (int j = 0; j < predefined_size; j++){		//issue here
			if (row_of_maze[0][j] != ' '){
				counter_2++;
			}
			else{
				maze_dimensions.xvar = counter;
				return(maze_dimensions);
				break;
			}
		}
	}
}

coordinates detection_of_plus(string row_of_maze[], coordinates maze_dimensions){     //starting point
	coordinates plus_pos;
	for (int j = 0; j < maze_dimensions.yvar; j++){      //the y coordinate
		for (int i = 0; i<maze_dimensions.xvar; i++){    //the x coordinate
			if (row_of_maze[j][i] == '+'){
				plus_pos.xvar = i;
				plus_pos.yvar = j;
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
				money_pos.xvar = i;
				money_pos.yvar = j;
				return(money_pos);
				break;
			}
		}
	}
}

void print_maze(string row_of_maze[], int const size){
	for (int i = 0; i<size; i++){
		cout << row_of_maze[i] << endl;
	}
}

void main(){
	coordinates maze_dimensions;
	coordinates plus_pos;
	coordinates money_pos;
	int const predefined_size = 1000;
	string row_of_maze[predefined_size];
	maze_dimensions = count_and_read_how_many_strings(row_of_maze, predefined_size); //need to count how many strings there are
	money_pos = detection_of_money(row_of_maze, maze_dimensions);
	plus_pos = detection_of_plus(row_of_maze, maze_dimensions);
	//using a matrix to define the strings by character
}
