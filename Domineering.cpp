//Made by Ajmal Sarif w1722688 ©2020
#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string>
#include<windows.h> //Used for sleep function
#include <stdlib.h> // Used for exit function
using namespace std;

int board_width;
int board_height;
int player1_pos_X;
int player1_pos_Y;
int player2_pos_X;
int player2_pos_Y;
int vertical_moves;
int horizontal_moves;
bool playerturn = true;
bool savegame_check = false;
bool loadgame_check = false;
bool ys = false;
bool quit_break = false;
int exit_msg;
string gap;
string player_win;



// General Input Validation
int cinput(string message) {
	char userin;

	while (true) {

		cout << message;
		cin >> userin;

		if (isdigit(userin)) {
			break;
		}
		else if (toupper(userin) == 'S') { //Save game
			savegame_check = true;
			return 0;
		}
		else if (toupper(userin) == 'L') { //Load Game
			loadgame_check = true;
			return 0;
		}

		// Accept Y and N if Q was pressed
		if (ys == true) {
			if (toupper(userin) == 'Y') {
				return 1;
			}
			else if (toupper(userin) == 'N') {
				return 0;
			}
		}

		else if (toupper(userin) == 'Q') { //Load Game
			ys = true;
			exit_msg = cinput("Are you sure you want to Quit? Y | N: ");
			
			if (exit_msg == 1) {
				exit(1);
			}
			else {
				ys = false;
				quit_break = true; // Used to keep players turn 
			}

			return 0;
		}
		

		else {

			cout << "Try again" << endl << endl;
		}
		cin.clear();
		cin.ignore(255, '\n');
	}

	return userin - '0';
}

// Take Board Size from Player
void board_size() {
	while (true) {
		
		board_width = cinput("Enter Board Size \nWIDTH: ");
		board_height = cinput("HEIGHT: ");

		if ((board_width > 1 && board_width < 16) && (board_height > 1 && board_height < 16)) {
			break;
		}
		else {
			cout << "\nValues between 2 - 15 for both WIDTH and HEIGHT\n\n";
		}
	}
}

// Top & bottom border for board
void border(int board_width) {
	cout << "    ";
	for (int i = 0; i < board_width + 2; i++) {

		int corner = board_width + 1; // displays + at the end

		if (i == 0 || i == corner) {
			cout << "+";
		}
		else {
			cout << "-";
		}
	}
	cout << endl;
}

// Check if board tile is empty
bool board_validation(vector<vector<int>>& vector_board, int& player_pos_Y, int& player_pos_X, bool player_type) {

	/*Check first if its horizontal or vertical
	  Otherwise, you will add +1 to x axis of
	  vertical dominoo which does not exist in the vector
	  */
	if (player_type == true) {
		if (vector_board[player_pos_Y][player_pos_X] == 0 && vector_board[player_pos_Y][player_pos_X + 1] == 0) {
			return true;
		}
		else {
			cout << "\n  Horizontal Tile already taken\n\n";
		}
	}
	else if (player_type == false) {
		if (vector_board[player_pos_Y][player_pos_X] == 0 && vector_board[player_pos_Y + 1][player_pos_X] == 0) {
			return true;
		}
		else {
			cout << "\nTile already taken\n\n";
			return false;
		}
	}


}


// Take validated X,Y Coordinates from Player 
void player_validation(int& player_pos_Y, int& player_pos_X, bool player_type) {
	while (true) {
		int board_range_width = board_width;
		int board_range_height = board_height;

		
		// Cap placement of domino for p1 = width & p2 = height
		if (player_type == true) {
			board_range_width = board_width - 1;
			cout << "Player 1\n";
		}
		else if (player_type == false) {
			board_range_height = board_height - 1;
			cout << "Player 2\n";
		}

		
		
		player_pos_X = cinput("  | X |: ");
		// Check for SAVE GAME!
		if (savegame_check == true) {			
			return;
		}
		else if (loadgame_check == true) {
			return;
		}
		else if (quit_break == true) {
			return;
		}

		player_pos_Y = cinput("  | Y |: ");
		// Check for SAVE GAME!
		if (savegame_check == true) {		
			cout << "AAAAA\n";
			cout << savegame_check << endl;
			return;
		}
		else if (loadgame_check == true) {
			return;
		}
		else if (quit_break == true) {
			return;
		}
		
	
		if ((player_pos_Y > 0 && player_pos_Y <= board_range_height) && (player_pos_X > 0 && player_pos_X <= board_range_width)) {
			// If player enters 1 the vector needs 0
			player_pos_Y--;
			player_pos_X--;
			break;

		}
		else {

			cout << "\nValues between 1 - " << board_range_width << " for 'X' " << " AND 1 - " << board_range_height << " for 'Y' \n\n";
			/*How do I Remove the lines instead of CLR?*/

			//Resets back to zero so new input is taken
			player_pos_Y = 0;
			player_pos_X = 0;
		}

	

	}

}



// Players Section
void player1(vector<vector<int>>& vector_board) {
	while (true) {
		player_validation(player1_pos_Y, player1_pos_X, true);

		if (savegame_check == false && loadgame_check == false && quit_break == false) {								// Prevents writing to board
			if (board_validation(vector_board, player1_pos_Y, player1_pos_X, true) == true) {
				vector_board[player1_pos_Y][player1_pos_X] = 1;  // Assign player 1 coordinates
				vector_board[player1_pos_Y][player1_pos_X + 1] = 1;  // Add second half of horizontal domino 
				break;
			}
		}
		else {
			break;
		}
		
	}
}

void player2(vector<vector<int>>& vector_board) {
	while (true) {
		player_validation(player2_pos_Y, player2_pos_X, false);
		if (savegame_check == false && loadgame_check == false && quit_break == false) {						// Prevents writing to board
			if (board_validation(vector_board, player2_pos_Y, player2_pos_X, false) == true) {
				vector_board[player2_pos_Y][player2_pos_X] = 2;  // Assign player 1 coordinates
				vector_board[player2_pos_Y + 1][player2_pos_X] = 2;  // Add second half of horizontal domino 
				break;
			}
		}
		else {
			break;
		}

	}
}

// Save Load Section
void savegame(vector<vector <int>>& board) {
	ofstream savegame("savegame.txt");			// Create and open new txt file

	if (savegame.is_open()) {					// Checks whether the file could be opened
		savegame << "W" << board_width << "H" << board_height << "X" << endl;
		for (int i = 0; i < board_height; i++) {
			for (int x = 0; x < board_width; x++) {
				savegame << board[i][x];

			}

		}
	}
	savegame.close();

}

void loadgame(vector<vector <int>>& board) {

	char i;
	string board_data;
	int check_width = board_width;
	int check_height = board_height;
	int _board_width;
	int _board_height;
	bool width_check = false;
	bool height_check = false;
	bool input_vector = false;

	ifstream savegame_load("savegame.txt");			// Create object savegame & open existing savegame file

	if (savegame_load.is_open()) {					// checks whether the file could be opened
		while (!savegame_load.eof()) {				// as long as end of file not reached... !fs.eof

			savegame_load >> i;						// Save each char in variabel i

			if (i == 'W') {
				width_check = true;
			}
			else if (i == 'H') {
				height_check = true;
			}

			// Take Number after 'W' as width value
			if (width_check == true && i != 'W') {
				_board_width = i - '0';				// -'0' Converts Char to Int
				width_check = false;
			}
			else if (height_check == true && i != 'H') {
				_board_height = i - '0';
				height_check = false;
			}


			

			// Input chars to string
			if (input_vector == true) {
				board_data += i;
			}
			if (i == 'X') {			   //Input all chars after X into string

				if (_board_width == check_width && _board_height == check_height) {
					cout << "";
				}
				else {
					cout << "\n-------- WRONG BOARD SIZE! --------\n     BOARD NEEDS TO BE = H: " << _board_height << " x W: " << _board_width << endl;
					Sleep(4000);
					return;
				}

				input_vector = true;
			}

		}
	}
	else {
		cout << "-------- NO FILE --------";
		Sleep(1000);
		return;
	}
	savegame_load.close();



	//Input Values to Array
	int count = 0;
	for (int i = 0; i < board_height; i++) {
		for (int x = 0; x < board_width; x++) {
			board[i][x] = board_data[count] - '0'; //Convert Char -'0' to int
			count++;
		}
	}

}



int main()
{

	board_size();
	// Vector of numbers
	vector<vector<int> > board(board_height, vector<int>(board_width, 0));


	while (true) {
		system("cls");
		// Display Grid
		cout << "---- Instructions ----\t---- Inputs ----\nPlayer 1 - Horizontal \tL-Load\tQ-Quit\nPlayer 2 - Vertical\tS-Save" << endl;
		cout << string(40, '-') << endl << endl;


		// Show Column Numbers
		cout << "   X ";
		for (int i = 0; i < board_width; i++) {

			cout << i + 1 << "";

		}
		cout << endl << " Y" << endl;
		border(board_width);

		for (int i = 0; i < board_height; i++) {
			if (i >= 9) {
				gap = " ";
			}
			else {
				gap = "  ";
			}
			cout << " " << i + 1 << gap << "|";	 // Show Row Numbers

			for (int x = 0; x < board_width; x++) {

				switch (board[i][x]) {
				case 0:
					cout << ".";
					break;
				case 1:
					cout << "X";
					break;
				case 2:
					cout << "Y";
					break;
				}
			}
			cout << "|" << endl;

		}
		border(board_width);
		cout << endl << endl;


		//Reset Moves
		vertical_moves = 0;
		horizontal_moves = 0;
		// Check how many moves left
		for (int v = 0; v < board_height; v++) {
			for (int w = 0; w < board_width; w++) {
				if (w == board_width - 1) { continue; }

				if (board[v][w] == 0 && board[v][w + 1] == 0) {

					horizontal_moves += 1;

				}

			}

		}
		// Check how many moves left
		for (int y = 0; y < board_height; y++) {
			for (int h = 0; h < board_width; h++) {
				if (y == board_height - 1) { continue; }

				if (board[y][h] == 0 && board[y + 1][h] == 0) {

					vertical_moves += 1;
				}

			}

		}

		//cout << "Player 1 Moves Left: " << horizontal_moves << "\nPlayer 2 Moves Left: " << vertical_moves << endl << endl;

		if (vertical_moves == 0) {
			cout << "-------- END OF GAME! --------\n\n";
			cout << "    Player 1 WON!\n\n"; break;
		}

		else if (horizontal_moves == 0) {
			cout << "-------- END OF GAME! --------\n\n";
			cout << "    Player 2 WON!\n\n"; break;
		}

		
		if (playerturn == true) {
			//Take Player 1 Move
			player1(board);
			playerturn = false;

		}
		else {
			//Take Player 2 Move
			player2(board);
			playerturn = true;

		}
		
		if (quit_break == true) {
			//Keeps turn of player
			(playerturn == false) ? playerturn = true : playerturn = false;
			quit_break = false;
		}
		

		if (savegame_check == true) {
			cout << "\n -------- GAME SAVED! --------" << endl;
			Sleep(1000);

			//Save game
			savegame(board);

			//Keeps turn of player
			(playerturn == false) ? playerturn = true :  playerturn = false;

			// Set to false otherwise keeps saving
			savegame_check = false; 
		}

		if (loadgame_check == true) {
			cout << "\n -------- GAME LOAD! --------" << endl;
			Sleep(1000);

			//Load Game
			loadgame(board);

			//Keeps turn of player
			(playerturn == false) ? playerturn = true : playerturn = false;

			// Set to false otherwise keeps saving
			loadgame_check = false;
		}

	}
}












