#include <iostream>
#include <cstdlib>
#include <ctime>
#include <jni.h>
//#include "jni.h"

using namespace std;

//---------------here is the AI move-------------------------------------------
int ai_move (char board[5][5])
{	
	 int row, col, char_count, emptyrow, emptycol, char_countv, node;

	//Check if AI can win in current move horizontally and vertically
	for (int i=0; i<5; i++) {

		char_count = 0;
		emptycol = -1;
		char_countv =0;
		emptyrow = -1;
		int j;
		for (j=0; j<5; j++) {
			if (board[i][j] == 'X') {
				char_count++;
			}
			else if (board[i][j] == ' ') {
				emptycol = j;
			}

			if (board[j][i] == 'X') {
				char_countv++;
			}
			else if (board[j][i] == ' ') {
				emptyrow = i;
			}
		}
		//put X in winning position or blocking position
		if (char_count == 4 && emptycol != -1) {
			row = i;
			col = emptycol;
			node = (row)*5 + col;
			return node;
		}
		if (char_countv == 4 && emptyrow != -1) {
			row = j;
			col = emptyrow ;
			node = (row)*5 + col;
			return node;
		}		
	}

	//Check if AI can win diagonally and anti diagonally
	char_count = 0;
	emptyrow = -1;
	emptycol = -1;
	char_countv=0;
	for (int i=0; i<5; i++) {
		if (board[i][i] == 'X') {
			char_count ++;
		}
		else if (board[i][i] == ' ') {
			emptyrow = emptycol = i;
		}

		if (board[i][4-i] == 'X') {
			char_countv ++;
		}
		else if (board[i][4-i] == ' ') {
			emptyrow = i;
			emptycol = 4 - i;
		}
	}
	if (char_count == 4 && emptyrow != -1 && emptycol != -1) {
		row = emptyrow;
		col = emptycol;
		node = (row)*5 + col;
		return node;
	}

	if (char_countv == 4 && emptyrow != -1 && emptycol != -1){
		row = emptyrow;
		col = emptycol;
		node = (row)*5 + col;
		return node;
	}
	char_count = 0;
	emptyrow = -1;
	emptycol = -1;
	char_countv =0;

	//check if user is winning in next move and block it
	for (int i=0; i<5; i++) {

		char_count = 0;
		emptycol = -1;
		char_countv=0;
		int j;
		//for loop through columns 
		for (j=0; j<5; j++) {
			// If the user is occupying the block, increment char count
			if (board[i][j] == 'O') {
				char_count++;
			}
			// If specified block is blank then column as empty
			else if (board[i][j] == ' ') {
				emptycol = j;
			}

			if (board[j][i] == 'O') {
				char_countv++;
			}
			else if (board[j][i] == ' ') {
				emptyrow = i;
			}
		}
		//If there are two user O in the row and there is a blank, then the 
		//blank is the winning position
		if (char_count == 4 && emptycol != -1) {
			row = i;
			col = emptycol;
			node = (row)*5 + col;
			return node;
		}

		if (char_countv == 4 && emptyrow != -1) {
			row = j;
			col = emptyrow;
			node = (row)*5 + col;
			return node;
		}			
	}

	//Check if user can win diagonally and anti diagonally
	char_count = 0;
	emptyrow = -1;
	emptycol = -1;
	char_countv =0;

	//for loop through the diagonal
	for (int i=0; i<5; i++) {
		if (board[i][i] == 'O') {
			char_count ++;
		}
		else if (board[i][i] == ' ') {
			emptyrow = emptycol = i;
		}

		if (board[i][4-i] == 'O') {
			char_countv ++;
		}
		else if (board[i][4-i] == ' ') {
			emptyrow = i;
			emptycol = 4 - i;
		}
	}
	if (char_count == 4 && emptyrow != -1 && emptycol != -1) {
		row = emptyrow;
		col = emptycol;
		node = (row)*5 + col;
		return node;
	}
	if (char_countv == 4 && emptyrow != -1 && emptycol != -1){
		row = emptyrow;
		col = emptycol;
		node = (row)*5 + col;
		return node;
	}

	//find best move for ai if none of above is true
	//horizontal check
	int counter_blank=0, counter_x=0, pre_counter_blank=0, pre_counter_x=0, counter_xy=0, counter_blanky=0;
	int pre_counter_blankv=0, counter_blankv, pre_counter_xv, counter_xv; 
	int a,b,c,d,e,f;
	//find best move for ai if none of above is true
	//horizontal check
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if (board[i][j] == 'X') {
				counter_x++;
				if (pre_counter_x <= counter_x) {
					pre_counter_x = counter_x;
				}
			}
			if (board[i][j] == ' ') { 
				counter_blank++;
				if (pre_counter_blank <= counter_blank) {
					pre_counter_blank = counter_blank;
				}
				a = i;
				b = j;
			}

			if (board[j][i] == 'X') {
				counter_xv++;
				if (pre_counter_xv <= counter_xv) {
					pre_counter_xv = counter_xv;
				}
			}
			if (board[j][i] == ' ') {
				counter_blankv++;
				if (pre_counter_blankv <= counter_blankv) {
					pre_counter_blankv = counter_blankv;
				}
				e = j;
				f = i;
			}
		}
		if (pre_counter_x == 3 && pre_counter_blank == 2) {
			node = (a)*5 + b;
			return node;
		}
		if (pre_counter_x == 2 && pre_counter_blank == 3) {
			node = (a)*5 + b;
			return node; 
		}
		if (pre_counter_x == 1 && pre_counter_blank == 4) {
			node = (a)*5 + b;
			return node;
		}

		if (pre_counter_xv == 3 && pre_counter_blankv == 2) {
			node = (e)*5 + f;
			return node;
		}
		if (pre_counter_xv == 2 && pre_counter_blankv == 3) {
			node = (e)*5 + f;
			return node;
		}
		if (pre_counter_xv == 1 && pre_counter_blankv == 4) {
			node = (e)*5 + f;
			return node;
		}

		counter_blank=0;
		counter_x=0;
		pre_counter_blank=0;
		pre_counter_x=0;
		counter_xv=0;
		counter_blankv=0;
		pre_counter_blankv=0;
		pre_counter_xv=0;
	}
	
	//diagonal and anti diagonal check
	 for(int i=0; i<5; i++){
		if(board[i][i] == 'X') {
			counter_x++;
		}
		if(board[i][i] == ' ') {
			counter_blank++;
			a =i; 
		}

		if (board[i][4-i] == 'X') {
			counter_xy++;
		}
		if (board[i][4-i] == ' ') {
			counter_blanky++;
			c = i; 				
			d = 4-i;
		}

		if(counter_x == 3 && counter_blank ==2 ) {
			node = (a)*5 + a;
			return node;
		}
		if(counter_x ==2 && counter_blank ==3) {
			node = (a)*5 + a;
			return node;
		}
		if(counter_x ==1 && counter_blank ==4) {
			node = (a)*5 + a;
			return node;
		}

		if (counter_xy == 3 && counter_blanky ==2 ) {
			node = (c)*5 + d;
			return node;
		}
		if (counter_xy ==2 && counter_blanky ==3) {
			node = (c)*5 + d;
			return node;
		}
		if (counter_xy ==1 && counter_blanky ==4) {
			node = (c)*5 + d;
			return node;
		}
	}
		counter_x =0;
		counter_blank=0;
		counter_xy=0;
		counter_blanky=0;

		int i =0,j =0;
 		i = row;
 		j =col;
 		while(board[row][col] != ' ') {
 			row = rand()%4+0;
 			col = rand()%4+0;
 		}		
 		node = (row)*5 + col;
 		return node;
}


extern "C" {
	JNIEXPORT jint JNICALL
	Java_com_example_ray_a5tac2_MainActivity_aStar(JNIEnv *env, jobject instance, jintArray board);
}

JNIEXPORT jint JNICALL
Java_com_example_ray_a5tac2_MainActivity_aStar(JNIEnv *env, jobject instance, jintArray board)
{
	jint newMove = 0;
	int boardcpp[25];
	jint* boardjava = env->GetIntArrayElements(board, NULL);
	if(boardjava == NULL) {
		return 0; //exception has occurred
	}
	for(int i = 0; i < 25; ++i) {
		boardcpp[i] = boardjava[i];
	}

	char charboard[5][5];
	int k =0;
	for(int i = 0; i < 5; ++i) {
		for(int j = 0; j < 5; ++j) {
			//char[j][i] charboard;
			if(boardcpp[k] == 0) {
				charboard[i][j] = ' ';
			}
			else if(boardcpp[k] == -1) {
				charboard[i][j] = 'X';
			}
			else if(boardcpp[k] == 1) {
				charboard[i][j] = 'O';
			}
			++k;
		}
	}

	//TicTacToe* tictactoe = new TicTacToe();
	//newMove = tictactoe->ai_move(charboard);
	newMove = ai_move(charboard);
	//delete tictactoe;
	return newMove;
}

//int main () {return 0;}