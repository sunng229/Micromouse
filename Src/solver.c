#include "solver.h"
//#include "API.h"
//#include "stdio.h"
#include "irs.h"
#include "main.h"
#include "encoders.h"
#include "controller.h"
	int a = 15;
	int b = 0;
	int runNum = 1;
	int srt = 0;
	char direc = 'N';
	int 	ManHatDist[16][16] =
	{{14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
	{13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
	{12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
	{11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
	{10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
	{9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
	{8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8},
	{7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},
	{7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},
	{8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8},
	{9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
	{10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
	{11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
	{12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
	{13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
	{14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14}};

	int 	ManHatDist2[16][16] =
			{{15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
			{14, 15, 16, 17, 18, 19 ,20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
			{13, 14, 15, 16, 17, 18, 19 ,20, 21, 22, 23, 24, 25, 26, 27, 28},
			{12, 13, 14, 15, 16, 17, 18, 19 ,20, 21, 22, 23, 24, 25, 26, 27},
			{11, 12, 13, 14, 15, 16, 17, 18, 19 ,20, 21, 22, 23, 24, 25, 26},
			{10, 11, 12, 13, 14, 15, 16, 17, 18, 19 ,20, 21, 22, 23, 24, 25},
			{9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 ,20, 21, 22, 23, 24},
			{8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 ,20, 21, 22, 23},
			{7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 ,20, 21, 22},
			{6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 ,20, 21},
			{5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 ,20},
			{4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
			{3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18},
			{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17},
			{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
			{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}};

	typedef struct Cell {
	int row;
	int col;
	int MD;
	} Cell;
	//create maze matrix
	int horizontalWall[17][16] = {0};
	int verticalWall[16][17] = {0};

	int16_t left_count = 0;
	int16_t right_count = 0;
	uint16_t front_left_receivers = 0;
	uint16_t front_right_receivers  = 0;
	uint16_t right_receivers  = 0;
	uint16_t left_receivers = 0;

//initialize Cells to have coordinates and Manhattan distance value
struct Cell blocks[16][16] = {0};
void initializeMD(){



	//initialize vertical walls of maze
	for(int i = 0; i <= 16; i++) {
		verticalWall[i][0] = 1;
		verticalWall[i][16] = 1;
	}

	//initialize horizontal walls of maze
	for(int i = 0; i < 16; i++) {
		horizontalWall[0][i] = 1;
		horizontalWall[16][i] = 1;
	}


	// initializing the Manhattan distance array
	/*int MAZE_SIZE = 16;
	int ManHatDist[16][16] ={};

	for( int i = 1; i <= MAZE_SIZE; i++){
		for( int j = 1; j <= MAZE_SIZE; j++)
		{
			if(j > MAZE_SIZE/2){
				ManHatDist[i-1][j-1]= ManHatDist[i-1][MAZE_SIZE + 1 - j];
			}
			else if(i > MAZE_SIZE/2){
				ManHatDist[i-1][j-1] = ManHatDist[MAZE_SIZE + 1 - i][j-1];
			}
			else ManHatDist[i-1][j-1] = MAZE_SIZE - i - j;
		}
	};*/


	//initialize Cells to have coordinates and Manhattan distance value



}



Action notLeftWallFollower() {
	if(blocks[a][b].MD == 0)
	{
		srt = 0;
		runNum++;
	}
	if(srt == 0){
		if(runNum%2 == 0)
		{
			for(int i = 0; i < 16; i++) {
				for (int j = 0; j < 16; j++) {
					blocks[i][j].row = i;
					blocks[i][j].col = j;
					blocks[i][j].MD = ManHatDist[i][j];
				}
			}
				srt++;
				//return floodFill();
		}
		if(runNum%2 != 0)
			{
			for(int i = 0; i < 16; i++) {
				for (int j = 0; j < 16; j++) {
					blocks[i][j].row = i;
					blocks[i][j].col = j;
					blocks[i][j].MD = ManHatDist2[i][j];
				}

			}
				srt++;
				//return floodFill();
			}
	}

	  left_count = -getLeftEncoderCounts();
	  right_count = -getRightEncoderCounts();
	 /* right_receivers  = readLeftIR();
	  left_receivers = readRightIR();*/
	  front_left_receivers  = readFrontLeftIR();
	  front_right_receivers  = readFrontRightIR();
	    right_receivers = readLeftIR();
		left_receivers  = readRightIR();

	switch (direc)
	 {
	//if(direc == "N")
		case 'N' :
			if(front_left_receivers  > 800 || front_right_receivers  >800 )
				horizontalWall[a][b] = 1;
			if(left_receivers  > 800  )
				verticalWall[a][b] = 1;
			if(right_receivers > 800  )
				verticalWall[a][b+1] = 1;
			if(front_left_receivers  < 800 && front_right_receivers  <800)
			{
				if(blocks[a][b].MD > blocks[a-1][b].MD)
				{
					a--;
					direc = 'N';
					return FORWARD;
				}
			}
			if(right_receivers < 800)
			{
				if(blocks[a][b].MD > blocks[a][b+1].MD)
				{
					direc = 'E';
					return RIGHT;
				}
			}
			if(left_receivers  < 800)
			{
				if(blocks[a][b].MD > blocks[a][b-1].MD)
				{
					direc = 'W';
					return LEFT;
				}
			}
		if(blocks[a][b].MD > blocks[a+1][b].MD)
		{
		direc = 'S';
		return TURNAROUND;
		}
				return floodFill();

	//if( direc == "W")
	case 'W' :
		if(front_left_receivers  > 800 || front_right_receivers  >800  )
			verticalWall[a][b] = 1; //west
		if(left_receivers  > 800  )
			horizontalWall[a+ 1][b] = 1; //south
		if(right_receivers > 800  )
			horizontalWall[a][b] = 1; //north

		if(front_left_receivers  < 800 && front_right_receivers  <800)
		{
			if(blocks[a][b].MD > blocks[a][b-1].MD)
			{
				b--;
				return FORWARD;
			}
		}

		if(right_receivers < 800)
		{
			if(blocks[a][b].MD > blocks[a- 1][b].MD)
			{
				direc = 'N';
				return RIGHT;
			}
		}

		if(left_receivers  < 800)
		{
			if(blocks[a][b].MD > blocks[a+1][b].MD)
			{
				direc = 'S';
				return LEFT;
			}
		}

		if(blocks[a][b].MD > blocks[a][b+1].MD)
		{
			direc = 'E';
			return TURNAROUND;
		}
		return floodFill();


	//if(direc == "E")
	case 'E' :
		if(front_left_receivers  > 800 || front_right_receivers  >800)
			verticalWall[a][b+1] = 1; //east
		if(left_receivers  > 800)
			horizontalWall[a][b] = 1; //north
		if(right_receivers > 800)
			horizontalWall[a+1][b] = 1; //south

		if(front_left_receivers  < 800 && front_right_receivers  <800)
			{
				if(blocks[a][b].MD > blocks[a][b+1].MD)
				{
					b++;
					direc = 'E';
					return FORWARD;
				}
			}

		if(right_receivers < 800)
		{
			if(blocks[a][b].MD > blocks[a+1][b].MD)
			{
				direc = 'S';
				return RIGHT;
			}
		}
		if(left_receivers  < 800)
		{
			if(blocks[a][b].MD >= blocks[a-1][b].MD)
			{
				direc = 'N';
				return LEFT;
			}
		}

		if(blocks[a][b].MD > blocks[a][b-1].MD)
		{
			direc = 'W';
			return TURNAROUND;
		}
		return floodFill();


	//if(direc == "S")
	case 'S' :
		if(front_left_receivers  > 800 || front_right_receivers >800  )
			horizontalWall[a+ 1][b] = 1;  //south
		if(left_receivers  > 800  )
			verticalWall[a][b+1] = 1;  //east
		if(right_receivers > 800  )
			verticalWall[a][b] = 1;  //west

		if(front_left_receivers  < 800 && front_right_receivers  < 800)
		{
			if(blocks[a][b].MD > blocks[a+1][b].MD)
			{
				a++;
				direc = 'S';
				return FORWARD;
			}
		}

		if(right_receivers < 800)
		{
			if(blocks[a][b].MD > blocks[a][b-1].MD)
			{
				direc = 'W';
				return RIGHT;
		}
			}

		if(left_receivers  < 800){
		if(blocks[a][b].MD > blocks[a][b+1].MD){

			direc = 'E';
			return LEFT;
			}}

		if(blocks[a][b].MD > blocks[a-1][b].MD)
		{
		direc = 'N';
		return TURNAROUND;
		}
		return floodFill();
			}
			return floodFill();

}


int minimumDistance(int x, int y) {

	int minAway = 100;
	//if (a > 0 )
	//{
		if(horizontalWall[x][y] == 0)
		{
			if(minAway > blocks[x- 1][y].MD)
				{								//north
				minAway = blocks[x- 1][y].MD;
				}
		}
	//}
	//if (b < 15)
	//{
		if(verticalWall[x][y+1] == 0)
		{
			if(minAway > blocks[x][y+1].MD)
			{									//east
				minAway = blocks[x][y+1].MD;
			}
		}
	//}
	//if (a > 0)
	//{
			if(horizontalWall[x+1][y] == 0)
		{

			if(minAway > blocks[x+1][y].MD)
			{									//south
				minAway = blocks[x+1][y].MD;
			}
		}
	//}
	//if (b > 0)
	//{
		if(verticalWall[x][y] == 0)
		{
			if(minAway > blocks[x][y-1].MD)
			{										//west
				minAway = blocks[x][y-1].MD;
			}
		}
	//}
	return minAway;
}

Cell Queue[512] = {0};
int n = 0;
int start = 0;
int end = 0;


void push(struct Cell num) {

		Queue[end] = num;
		if(end == 511){
		end = 0;}
		else
		end++;
}

void pop() {
		if(start == 511){
		start = 0;}
		else
		 start++;
}
int length()
{	if(end >= start){
	return end-start;}
	else return (511 + end - start);

}


Action floodFill() {
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

	//Add current cell to queue
	//While queue is not empty:
	//Take front cell in queue “out of line” for consideration
	//Get the front cell’s minimum value amongst accessible neighbors.
	//If the front cell’s value ≤ minimum of its neighbors, set the front cell’s value to minimum + 1 and add all accessible neighbors to the queue.
	//Else, continue!
	int minimum;
	struct Cell frontCell;

	push((blocks[a][b]));
	while (length() != 0) {
		frontCell = Queue[start];

		pop(); //front cell taken out

		minimum = minimumDistance(frontCell.row, frontCell.col);
		if(frontCell.MD <= minimum)
		{
			frontCell.MD = minimum + 1;

			blocks[frontCell.row][frontCell.col].MD = frontCell.MD;
			if (horizontalWall[frontCell.row][frontCell.col] == 0) { //north
				push((blocks[frontCell.row - 1][frontCell.col]));
			}
			if (horizontalWall[frontCell.row+ 1][frontCell.col] == 0){ //south
				push((blocks[frontCell.row+1][frontCell.col]));

			}
			if (verticalWall[frontCell.row][frontCell.col] == 0) {	//west
				push((blocks[frontCell.row][frontCell.col-1]));

			}
			if (verticalWall[frontCell.row][frontCell.col+1] == 0) {   //east
				push((blocks[frontCell.row][frontCell.col+1]));

			}
		}

	}
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    	return IDLE;

}

	   int init = 0;

Action solver() {

	if(init == 0){
		init= 1;
	initializeMD();}

	return notLeftWallFollower();
}
