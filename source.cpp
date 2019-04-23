#include "library.h"

struct coordinates
{
	int xvar, yvar;
};

coordinates count_and_read_how_many_strings(string row_of_maze[], int const predefined_size)		//count and reads from file
{
	int counter = 0;
	coordinates maze_dimensions;
	maze_dimensions.xvar = 0;
	maze_dimensions.yvar = 0;
	ifstream fin("treasure.txt");
	if (fin.fail())
	{
		cout << endl << "Error opening file\n";
		fin.close();
		return(maze_dimensions);
	}
	else
	{
		for (int i = 0; i < predefined_size; i++)
		{
			fin >> row_of_maze[i];
			if (fin.fail())
			{
				maze_dimensions.yvar = counter;
				maze_dimensions.xvar = row_of_maze[0].length();
				fin.close();
				return(maze_dimensions);
				break;
			}
			else
			{
				counter++;
			}
		}
	}
}

coordinates detection_of_plus(string row_of_maze[], coordinates maze_dimensions)		//starting point
{
	coordinates plus_pos;
	for (int j = 0; j < maze_dimensions.yvar; j++)										//the y coordinate
	{
		for (int i = 0; i<maze_dimensions.xvar; i++)									//the x coordinate
		{
			if (row_of_maze[j][i] == '+')
			{
				plus_pos.xvar = i;
				plus_pos.yvar = j;
				return(plus_pos);
				break;
			}
		}
	}
}

coordinates detection_of_money(string row_of_maze[], coordinates maze_dimensions)		//runs through stored maze 'row_of_maze' and find where the char '$' is found 
{    //end point
	coordinates money_pos;
	for (int j = 0; j<maze_dimensions.yvar; j++)
	{		 //the y coordinate
		for (int i = 0; i<maze_dimensions.xvar; i++)
		{    //the x coordinate
			if (row_of_maze[j][i] == '$')
			{
				money_pos.xvar = i;
				money_pos.yvar = j;
				return(money_pos);
				break;
			}
		}
	}
}

void draw_box(int i, int j, int const scale, double color[])							//draws the box for the particular row and column within 'row_of_maze' according to scale defined in start_game()
{
	move_to(i*scale, j*scale);
	set_pen_width(5);
	set_pen_color(color[0],color[1], color[2]);
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

void print_maze(string row_of_maze[], coordinates maze_dimensions, int const scale)					//prints the intial maze
{
	double color[3];
	for (int j = 0; j < maze_dimensions.yvar; j++)
	{
		for (int i = 0; i < maze_dimensions.xvar; i++)
		{
			if (row_of_maze[j][i] == '$')
			{
				color[0] = .94;
				color[1] = .90;
				color[2] = .55;
				//color = color::sodium_d;
			}
			else if (row_of_maze[j][i] == '+')
			{
				color[0] = 1;
				color[1] = 1;
				color[2] = 1;
				//color = color::white;
			}
			else if (row_of_maze[j][i] == 'X')
			{
				color[0] = 0.08;
				color[1] = 0.28;
				color[2] = 0.20;
				//color = color::dark_green;
			}
			else
			{
				color[0] = 0.86;
				color[1] = 0.27;
				color[2] = 0.02;
				//color = color::orange;
			}
			draw_box(i, j, scale, color);
		}
	}
}

void swap(string row_of_maze[], coordinates plus_pos, coordinates money_pos, int temp_pos_y, int temp_pos_x)		//swaps char '+' and '-' for the move
{
	char temp = row_of_maze[plus_pos.yvar][plus_pos.xvar];
	row_of_maze[plus_pos.yvar][plus_pos.xvar] = row_of_maze[temp_pos_y][temp_pos_x];
	row_of_maze[temp_pos_y][temp_pos_x] = temp;
}

void start_game(string row_of_maze[], coordinates plus_pos, coordinates money_pos, coordinates maze_dimensions)		//initializes the game
{
	int const scale = 50;
	make_window(maze_dimensions.xvar * scale, maze_dimensions.yvar * scale);
	print_maze(row_of_maze, maze_dimensions, scale);
	double color[3];
	while (true)
	{
		char c = wait_for_key_typed();
		if (c == 'w' || c == -90 )																					//move up								
		{
			int new_pos_x = plus_pos.xvar;
			int new_pos_y = plus_pos.yvar - 1;
			if (row_of_maze[new_pos_y][new_pos_x] == '-' && new_pos_y <= maze_dimensions.yvar && new_pos_y > 0)
			{
				swap(row_of_maze, plus_pos, money_pos, new_pos_y, new_pos_x);
				color[0] = 1; color[1] = 1; color[2] = 1;
				draw_box(new_pos_x, new_pos_y, scale, color);
				color[0] = 0.86; color[1] = 0.27; color[2] = 0.02;
				draw_box(plus_pos.xvar, plus_pos.yvar, scale, color);
				plus_pos.xvar = new_pos_x;
				plus_pos.yvar = new_pos_y;
			}
			else if (row_of_maze[new_pos_y][new_pos_x] == '$')
			{
				swap(row_of_maze, plus_pos, money_pos, new_pos_y, new_pos_x);
				color[0] = 1; color[1] = 1; color[2] = 1;
				draw_box(new_pos_x, new_pos_y, scale, color);
				color[0] = 0.86; color[1] = 0.27; color[2] = 0.02;
				draw_box(plus_pos.xvar, plus_pos.yvar, scale, color);
				plus_pos.xvar = new_pos_x;
				plus_pos.yvar = new_pos_y;
				wait(.5);
				cout << endl << "You won!" << endl;
				break;
			}
		}
		else if (c == 's' || c == -88)																				//move down
		{
			int new_pos_x = plus_pos.xvar;
			int new_pos_y = plus_pos.yvar + 1;
			if (row_of_maze[new_pos_y][new_pos_x] == '-' && new_pos_y <= maze_dimensions.yvar && new_pos_y > 0)
			{
				swap(row_of_maze, plus_pos, money_pos, new_pos_y, new_pos_x);
				color[0] = 1; color[1] = 1; color[2] = 1;
				draw_box(new_pos_x, new_pos_y, scale, color);
				color[0] = 0.86; color[1] = 0.27; color[2] = 0.02;
				draw_box(plus_pos.xvar, plus_pos.yvar, scale, color);
				plus_pos.xvar = new_pos_x;
				plus_pos.yvar = new_pos_y;
			}
			else if (row_of_maze[new_pos_y][new_pos_x] == '$')
			{
				swap(row_of_maze, plus_pos, money_pos, new_pos_y, new_pos_x);
				color[0] = 1; color[1] = 1; color[2] = 1;
				draw_box(new_pos_x, new_pos_y, scale, color);
				color[0] = 0.86; color[1] = 0.27; color[2] = 0.02;
				draw_box(plus_pos.xvar, plus_pos.yvar, scale, color);
				plus_pos.xvar = new_pos_x;
				plus_pos.yvar = new_pos_y;
				wait(.5);
				cout << endl << "You won!" << endl;
				break;
			}
		}
		else if (c == 'a' || c == -91)																				//move left
		{
			int new_pos_x = plus_pos.xvar - 1;
			int new_pos_y = plus_pos.yvar;
			if (row_of_maze[new_pos_y][new_pos_x] == '-' && new_pos_x  <= maze_dimensions.xvar && new_pos_x > 0)
			{
				swap(row_of_maze, plus_pos, money_pos, new_pos_y, new_pos_x);
				color[0] = 1; color[1] = 1; color[2] = 1;
				draw_box(new_pos_x, new_pos_y, scale, color);
				color[0] = 0.86; color[1] = 0.27; color[2] = 0.02;
				draw_box(plus_pos.xvar, plus_pos.yvar, scale, color);
				plus_pos.xvar = new_pos_x;
				plus_pos.yvar = new_pos_y;
			}
			else if (row_of_maze[new_pos_y][new_pos_x] == '$')
			{
				swap(row_of_maze, plus_pos, money_pos, new_pos_y, new_pos_x);
				color[0] = 1; color[1] = 1; color[2] = 1;
				draw_box(new_pos_x, new_pos_y, scale, color);
				color[0] = 0.86; color[1] = 0.27; color[2] = 0.02;
				draw_box(plus_pos.xvar, plus_pos.yvar, scale, color);
				plus_pos.xvar = new_pos_x;
				plus_pos.yvar = new_pos_y;
				wait(.5);
				cout << endl << "You won!" << endl;
				break;
			}
		}
		else if (c == 'd' || c == -89)																				//move right
		{	
			int new_pos_x = plus_pos.xvar + 1;
			int new_pos_y = plus_pos.yvar;
			if (row_of_maze[new_pos_y][new_pos_x] == '-' && new_pos_x <= maze_dimensions.xvar && new_pos_x > 0)
			{
				swap(row_of_maze, plus_pos, money_pos, new_pos_y, new_pos_x);
				color[0] = 1; color[1] = 1; color[2] = 1;
				draw_box(new_pos_x, new_pos_y, scale, color);
				color[0] = 0.86; color[1] = 0.27; color[2] = 0.02;
				draw_box(plus_pos.xvar, plus_pos.yvar, scale, color);
				plus_pos.xvar = new_pos_x;
				plus_pos.yvar = new_pos_y;
			}
			else if (row_of_maze[new_pos_y][new_pos_x] == '$')
			{
				swap(row_of_maze, plus_pos, money_pos, new_pos_y, new_pos_x);
				color[0] = 1; color[1] = 1; color[2] = 1;
				draw_box(new_pos_x, new_pos_y, scale, color);
				color[0] = 0.86; color[1] = 0.27; color[2] = 0.02;
				draw_box(plus_pos.xvar, plus_pos.yvar, scale, color);
				plus_pos.xvar = new_pos_x;
				plus_pos.yvar = new_pos_y;
				wait(.5);
				cout << endl << "You won!" << endl;
				break;
			}

		}
		else if (c == 'q'){																							//quit game                -need to add more
			break;
		}
	}
}

void main()
{
	coordinates maze_dimensions;
	coordinates plus_pos;
	coordinates money_pos;
	int const predefined_size = 10000;
	string row_of_maze[predefined_size];
	maze_dimensions = count_and_read_how_many_strings(row_of_maze, predefined_size);
	money_pos = detection_of_money(row_of_maze, maze_dimensions);
	plus_pos = detection_of_plus(row_of_maze, maze_dimensions);
	start_game(row_of_maze, plus_pos, money_pos, maze_dimensions);
}
