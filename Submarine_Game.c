/* Assignment: 3
Author: Patrick lugassi, ID: 319266177
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>                  // including the Libraries//
#include <math.h>
typedef enum { TRUE, FALSE }boolean;    // create typedef of true or false for the function(boolean) in the program//


#define ROWS 10      //  create define to the number of rows (of the board game) //
#define COLS 10       // create define to the number of cols (of the board game)//
#define max_sub 5     //  create define to the numbers of submarine in the game //
#define MAX_VALUE 9    // create define to the maximum value of the board//  
#define MIN_VALUE 0     // create define to the minimum value of the board //
#define Direction_balanced 0  // create define to the direction of the sub //
#define Direction_vertical 1    // create define to the direction of the sub //


boolean board_game(int matrix[][COLS]);                 // function create the board game //
boolean print_board_game(int matrix[][COLS]);          // function that print the board game //
int randoom_submarine(int matrix[][COLS], int sizes[], int size);    // function that select random numbers  of colom and rows and direction of the sub //
boolean check_place_for_sub(int matrix[][COLS], int row, int col, int direction, int size_of_sub);    // This function selects a place for the submarine and if the place is normal in terms of size and other parameters//
int put_submarine(int matrix[][COLS], int row, int col, int direction, int size_of_sub);  // this function put the sub in the place she find ok//
int play_game_sub(int matrix[][COLS], int sizes[], int size);  // this function run the game and lett the user play//


int main() {
	srand(time(NULL));               //Initialization of random//
	int matrix[ROWS][COLS] = { 0 };  // create matrix with all element is zero //
	int sizes[5] = { 5,4,3,3,2 };    // creat array withe the size of the submarine//
	board_game(matrix);  // call function of the board game //
	randoom_submarine(matrix, sizes, 5);  // call function of the rendoom submarine with the matrix of zreo the sizes of the subs //


	if (play_game_sub(matrix, sizes, 5)) {      // this condition check if the function that play the game return 1 is mean that the user won the game //
		printf("you won the game! \n");    // print to the screen that the user won //
	}

	return TRUE;

}

boolean board_game(int matrix[][COLS]) {    // this function create the board game // 
	int i, j;   // create variables //

	for (i = 0; i < ROWS; ++i)     // loop run from zero untill 10 the size of the row//
	{
		for (j = 0; j < COLS; ++j)  // loop run from zero untill 10 the size of the colom//
		{
			matrix[i][j] = 0;     // in all the place in the mtrix it will be zero //

		}
	}
	return TRUE;
}


boolean print_board_game(int matrix[][COLS])      // function that print the board game  for us not for the user ! //
{
	int row_index = 0, col_index = 0;     // creat variables //

	printf("   %d %d %d %d %d %d %d %d %d %d \n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);    // print the number of the top of the table //

	for (row_index = 0; row_index < ROWS; ++row_index)  // loop from the index of row mean zero untill 10 the end of the board //
	{
		printf("%d  ", row_index);           // print the number of the row index //
		for (col_index = 0; col_index <= COLS - 1; ++col_index)   // loop from the first index of col mean zero untill 10 the end of the board //
		{
			printf("%d ", matrix[row_index][col_index]);   // print the number of th colom index //

		}

		printf("\n");  // Descending row //
	}
	printf("\n");
	return TRUE;
}

boolean print_board_user(int matrix[][COLS])    // this function print the board to the user ! (the blank board) //
{
	int row_index = 0, col_index = 0;    // create variables //

	printf("   %d  %d  %d  %d  %d  %d  %d  %d  %d  %d \n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);   // print the number of the top of the table //

	for (row_index = 0; row_index < ROWS; ++row_index)       // loop from the index of row mean zero untill 10 the end of the board //
	{
		printf("%d", row_index);      // print the number of the row index //
		for (col_index = 0; col_index <= COLS - 1; ++col_index)   // loop from the first index of col mean zero untill 10 the end of the board //
		{
			if (matrix[row_index][col_index] == 'x') {
				printf("  x");                                        // if the user hit it will print x to the board //
			}
			else if (matrix[row_index][col_index] == '~') {    // if the user hit nothing it will print ~  to the board //
				printf("  ~");
			}
			else
			{
				printf("   ");     // else it will print nothing //
			}
		}

		printf("\n");
	}
	printf("\n");
	return TRUE;
}


int randoom_submarine(int matrix[][COLS], int sizes[], int size) {           // this function choose a randoom number for row col and direction for a submarine //
	srand(time(NULL));
	int i, row, col, direction;    // create variables //

	row = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;  // choose a random number for row between 0-9 //
	col = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;  // choose a random number for col between 0-9 //
	direction = rand() % 2; // choose a random number between 0-1 //

	for (i = 0; i < size; ++i)  // loop that check place for the sub and get randoom numbers for coll, row,direction //
	{
		while (check_place_for_sub(matrix, row, col, direction, sizes[i]) == FALSE) {   // if the function that check place for the submarine is false it will choose a random numbers again //
			row = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
			col = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;                                        // choose number for col,row,direction//
			direction = (rand() % (Direction_vertical - Direction_balanced + 1)) + Direction_balanced;
		}
		put_submarine(matrix, row, col, direction, sizes[i]);  // call the function that  put submarine and  give her the matrix the row,col,direction that choosen. after choose randoom numbers it will put the matrix in her place // 
	}
	return TRUE;
}

int put_submarine(int matrix[][COLS], int row, int col, int direction, int size_of_sub) {    // this function put the submarine in the place //

	int i;        // create variables //
				  //vertical
	if (direction)
	{
		for (i = row; i < row + size_of_sub; ++i) // loop from row choosen randoomly  untill the number row + size of the sub //
		{
			matrix[i][col] = 1;           // put the number 1 in board //
		}
	}
	//horizon
	else
	{
		for (i = col; i < col + size_of_sub; ++i)   // if the sub direction choosen horizontal it will loop from the col choose randoom untill the number of the col +size of the submarine //
		{
			matrix[row][i] = 1;  // put the number 1 in all the places of the sub //
		}
	}
	return TRUE;
}
boolean check_place_for_sub(int matrix[][COLS], int row, int col, int direction, int size_of_sub) {  // this function check the place for the submarine we send her row,col,direction that choosen randoom //


																									 //True when direction = vertical //
	if (direction)
	{
		if (row + size_of_sub > ROWS || matrix[row - 1][col] != 0 || matrix[row + size_of_sub][col] != 0)
			return FALSE;                                                                                   // Checking at this point if I did not get off the board and if the sides of the submarine from above and below are normal and there is an empty space there //
		for (int i = 0; i < size_of_sub; ++i) // loop from the zero untill the size of the submarine //
		{
			if (matrix[row + i][col] != 0 || matrix[row + i][col + 1] != 0 || matrix[row + i][col - 1] != 0)   // Checking at this stage that both sides of the submarine to the right and left all places are available //
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	//when direction = horizon   //
	else {
		// check if the place around the sub is free //
		if (col + size_of_sub > COLS || matrix[row][col - 1] != 0 || matrix[row][col + size_of_sub] != 0)
			return FALSE;
		for (int i = 0; i < size_of_sub; ++i)
		{
			if (matrix[row][col + i] != 0 || matrix[row + 1][col + i] != 0 || matrix[row - 1][col + i] != 0)  // check if the places in the side of the sub is free //
			{
				return FALSE;
			}
		}
		return TRUE;
	}


}
int sum_of_arr(int arr[], int size) {   // this function is for summ al the size of the all sub // 
	int i, result = 0;  // create variables //
	for (i = 0; i <size; ++i)   // from i=0 untill the size of the sub //
	{
		result = result + arr[i];   // sum all the sizes of all the submarin and put it in the varable result //
	}
	return result;    // return the result of the sum //
}


int play_game_sub(int matrix[][COLS], int sizes[], int size) {   // function that play the game of submarine //
	int coordinate_row, coordinate_col;  // create variables //
	int i, j;   // create variables //
	int counter_of_sub = sum_of_arr(sizes, size);  // create variables  and put into the result that return from the summ of arr function //
	char miss = '~'; // create variables //
	char hit = 'x';  // create variables //

	print_board_user(matrix);  // function print the board clear to the user //
	do   // do whille loop //
	{

		printf("Please enter coordinate of row: ");   // ask the user to put coordinate of row //
		scanf("%d", &coordinate_row);  // scan the number from the user //
		getchar();  // clear the Enter from buffer //
		printf("Please enter coordinate of colom: ");  // ask the user to put coordinate of colom //
		scanf("%d", &coordinate_col);   // scan the number from the user //
		getchar();  // clear the Enter from buffer //

		if (coordinate_row == -1 && coordinate_col == -1)  // check if the user put -1 in the coordinate_row  and  check if the user put -1 in the coordinate_col //
		{
			printf("you choose to get out from the game...\n"); // print to screen that the user choose to get out from the game //
			return 0; // player asked to leave //
		}
		else if (coordinate_row > 9 || coordinate_row < 0)  // check if  check if the coordinate_row is bigger from 9 or coordinate_row small than 0 //
		{
			printf("Illegal values, please try again.\n");  // print to screen that is illegal value and give another try to the user //
		}

		else if (coordinate_col > 9 || coordinate_col < 0)   // check if coordinate_col is bigger than 9 or coordinate_col smaal from 0 //
		{
			printf("Illegal values, please try again. \n"); // print to the screen  is illegal value and give another try to the user //
		}

		else if (matrix[coordinate_row][coordinate_col] == 1)   // check if the place the user choose (the coordinate_row and the coordinate_col ) is 1 //
		{
			matrix[coordinate_row][coordinate_col] = hit;  // it mean that is a hit // 
			printf("HIT!\n");   // print to the screen that is a hit //
			--counter_of_sub;   // Missing one from the counter of the subs (from 17) //
		}

		else if (matrix[coordinate_row][coordinate_col] == hit)  //  check if the place the user choose (the coordinate_row and the coordinate_col ) is a hit //
		{
			printf("This location has already been hit! \n");  // print to the screen that This location has already been hit! //
		}

		else if (matrix[coordinate_row][coordinate_col] == 0) // check  if the place the user choose (the coordinate_row and the coordinate_col ) is 0 //
		{
			matrix[coordinate_row][coordinate_col] = miss;  // it mean that is a miss // 
			printf("MISS!\n");  // print to the screen  that the user miss //

		}

		else if (matrix[coordinate_row][coordinate_col] = miss)  // check if the place the user choose (the coordinate_row and the coordinate_col ) is a miss //
		{
			printf("This location has already found empty! \n"); // print to the screen that This location has already found empty! //
		}

		print_board_user(matrix);  // function print the board of the user //
	} while (counter_of_sub != 0); // this loop run untill the counter of the sub is not 0 //

	return 1; // player won the game //
}