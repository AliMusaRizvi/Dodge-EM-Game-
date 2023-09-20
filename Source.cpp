#include<iostream>
#include<string>
#include<conio.h>
#include<Windows.h>
#include<cstdlib>
#include<ctime>
#include <fstream>

using namespace std;

string board[19][19];
const int NUM_HIGH_SCORES = 10;
int life = 3;
int score = 0;
int level = 1;
int choice;
fstream myhandler;


void displays_scores();
void scores();
void Board();
void game_operate();
void display_Board();
void help();
void menu()
{
	cout << "Select Your Option: \n";
	cout << "1. Start New Game \n";
	cout << "2. See High Scores \n";
	cout << "3. Help\n";
	cout << "4. Exit \n";

	cin >> choice;
	switch (choice)
	{
	case 1: {
		Board();
		game_operate();
		display_Board();
	}
		  break;
	case 2: {
		displays_scores();
		cout << endl;
		menu();
	}
		  break;

	case 3: {
		help();
	}
	case 4: exit(0);
		break;
	default: cout << "Invalid Option!"; menu(); break;
	}

}




int main()
{
	system("color 3E");
	menu();

}


// creating the game board
void Board() {
	int a1 = 0, a2 = 19;

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			board[i][j] = "  ";
		}
	}


	//triple nested for making 4 hollow squares after skipping 1 line
	for (int k = 0; k < 4; k++)
	{
		for (int i = a1; i < a2; i++)
		{
			for (int j = a1; j < a2; j++)
			{
				if (j == a1 || j == a2 - 1)
					board[i][j] = " || ";
				else if (i == a1 || i == a2 - 1)
					board[i][j] = "====";
				else
					board[i][j] = " ** ";

				if (i == 8 || i == 9 || i == 10)
					board[i][j] = "    ";
				else
					if (j == 8 || j == 9 || j == 10)
						board[i][j] = "    ";
			}
		}
		a1 += 2;

		a2 -= 2;

	}
}


void display_Board()
{
	cout << "\n\n\tLives: " << life << "\tScore: " << score << "\tLevel: " << level << "\n\n";
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}


void game_operate()
{
	//X,Y are current coordinates of player's car.eX,eY are coordinates of end path
	//similarly ax,ay are for opponent's
	int X = 0, Y = 0, eX, eY;
	int ax = 0, ay = 0, aEx, aEy;
	int path; // path of user player car
	int path_o; // path of enemy car

	// variables control current direction of movement for both player and enemy
	int pl = 0, pr = 0, pu = 0, pd = 0;
	int ol = 0, ori = 0, ou = 0, od = 0;
	//reset positions when 1


	X = 9; eX = 1; // of user column
	Y = 1; eY = 1; // of opponent row
	pl = 1;
	ax = 12; aEx = 17;
	ay = 1; aEy = 1;
	ori = 1;


	//temporary strings to store and swap values when cars move
	string temp = "    ", temp2 = " ** ";

	//game operation
	while (life)
	{
		//moving player's car and calculating score
		if (pl)  //player car will move left until end_x, end_y coordinates
		{
			path = Y; //tracking path 1,2,3,4 of player's car
			eX = Y; //determing end coordinate based on direction

			board[Y][X] = temp;//after car has moved, board value will become temp

			X--;
			if (board[Y][X] == " ** ")
			{
				score++;
			}
			else
			{
				temp = board[Y][X];
			}

			board[Y][X] = "~##~";

			if (X == eX)
			{
				pl = 0;
				pd = 1;
			}
		}
		else if (pd)   //move downwards similarly
		{
			path = X; //1
			eX = X;//1
			eY = 19 - 1 - X;
			board[Y][X] = temp;
			Y++;
			if (board[Y][X] == " ** ")
			{
				temp = "    ";
				score++;
			}
			else
				temp = board[Y][X];
			board[Y][X] = "~##~";

			if (Y == eY)   //after downwards we will move right
			{
				pd = 0;
				pr = 1;
			}
		}
		else if (pr)    //moving right
		{
			path = (19 - 1 - Y);
			eY = Y;
			eX = Y;
			board[Y][X] = temp;

			X++;
			if (board[Y][X] == " ** ")
			{
				temp = "    ";
				score++;
			}
			else
				temp = board[Y][X];
			board[Y][X] = "~##~";

			if (X == eX)  //upwards 1 after reaching right corner
			{
				pr = 0;
				pu = 1;
			}
		}
		else
			if (pu)
			{
				path = (19-1 - X);
				eY = 19 - 1 - X;
				eX = X;
				board[Y][X] = temp;
				Y--;
				if (board[Y][X] == " ** ")
				{
					temp = "    ";
					score++;
				}
				else
					temp = board[Y][X];
				board[Y][X] = "~##~";

				if (Y == eY)  //upper corner reached, move left now
				{
					pu = 0;
					pl = 1;
				}
			}

		if (ol)
		{
			path_o = (19-1 - ay); // ay =1
			aEx = 19 -1 - ay;
			board[ay][ax] = temp2;
			ax--;				//ax=12
			temp2 = board[ay][ax]; //oppponent cannot eat food, board will replaced same value
			//after movement of opponent
			board[ay][ax] = "(--)";

			if (ax == aEx)
			{
				ol = 0;
				ou = 1;
			}
		}
		else if (od)
		{
			path_o = (19-1 - ax);
			aEx = ax;
			aEy = ax;
			board[ay][ax] = temp2;
			ay++;
			temp2 = board[ay][ax];
			board[ay][ax] = "(--)";

			if (ay == aEy)
			{
				od = 0;
				ol = 1;
			}
		}
		else if (ori)
		{
			path_o = ay;
			aEy = ay;
			aEx = 18 - ay;
			board[ay][ax] = temp2;
			ax++;
			temp2 = board[ay][ax];
			board[ay][ax] = "(--)";

			if (ax == aEx)
			{
				ori = 0;
				od = 1;
			}
		}
		else
			if (ou)
			{
				path_o = ax;
				aEy = ax;
				aEx = ax;
				board[ay][ax] = temp2;
				ay--;
				temp2 = board[ay][ax];
				board[ay][ax] = "(--)";

				if (ay == aEy)
				{
					ou = 0;
					ori = 1;
				}
			}
		//loses life when player's car and opponent's car collide
		//collision occurs when opp car and player car pass through each other
		if (board[Y][X - 1] == "(--)" || board[Y - 1][X] == "(--)")
		{
			life--;
		}
		//clear the temp after collision
		if (temp == "(--)")
		{
			temp = "    ";
		}

		//opponent movement and chasing the player car
		//if the level is one then the opponent won't in horizontal directions

		static int oMoveL = 0; //decrease limit to make opponent move freely
		static int oMove = 0;
		bool can_move = 4;
		oMove++;
		if (oMove == oMoveL)
		{
			oMove = 0;
			can_move = 1;
		}

		//vertical movement 
		if ((ax >= 8 && ax <= 10) && can_move)
		{
			if (ol)
			{
				if (path - path_o < 0)
				{
					board[ay][ax] = "    ";
					ay += 2;
					can_move = 0;
				}
				else
					if (path - path_o > 0)
					{
						board[ay][ax] = "    ";
						ay -= 2;
						can_move = 0;
					}
			}
			else
				if (ori)
				{
					if (path - path_o < 0)
					{
						board[ay][ax] = "    ";
						ay -= 2;
						can_move = 0;
					}
					else
						if (path - path_o > 0)
						{
							board[ay][ax] = "    ";
							ay += 2;
							can_move = 0;
						}
				}

		}
		//horizontal movement
		//horizontal movement is disabled for level 1
		else
			if ((ay >= 8 && ay <= 10) && can_move && level != 1)
			{
				if (ou)
				{
					if (path - path_o < 0)
					{
						board[ay][ax] = "    ";
						ax -= 2;
						can_move = 0;
					}
					else
						if (path - path_o > 0)
						{
							board[ay][ax] = "    ";
							ax += 2;
							can_move = 0;
						}
				}
				else
					if (od)
					{
						if (path - path_o < 0)
						{
							board[ay][ax] = "    ";
							ax += 2;
							can_move = 0;
						}
						else
							if (path - path_o > 0)
							{
								board[ay][ax] = "    ";
								ax -= 2;
								can_move = 0;
							}
					}

			}
		//getting input for player's controls
		char key;
		char key2 = '0';
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
				/*case 'p': menu();  YOU KNOW BETTER HOW TO PUT PAUSE BUTTON HERE*/

				break;
			case 'w':
				if (X >= 8 && X <= 10)
				{
					if (Y != 1 && Y != 11)
					{
						board[Y][X] = "    ";
						Y -= 2;

					}
				}
				break;
			case 'a':
				if (Y >= 8 && Y <= 10)
				{
					if (X != 1 && X != 11)
					{
						board[Y][X] = "    ";
						X -= 2;
					}
				}
				break;
			case 's':
				if (X >= 8 && X <= 10)
				{
					if (Y != 7 && Y != 17)
					{
						board[Y][X] = "    ";
						Y += 2;
					}
				}
				break;
			case 'd':
				if (Y >= 8 && Y <= 10)
				{
					if (X != 7 && X != 17)
					{
						board[Y][X] = "    ";
						X += 2;
					}
				}
				break;
			}

		}

		display_Board();
		if (level != 3)
		{
			Sleep(100);

		}
		else
		{
			oMoveL = 0;
		}
		
		system("cls");
		if (score >= 110)
		{
			level++;
			score = 0;
			Board();
			X = 9; eX = 1;
			Y = 1; eY = 1;
			pl = 1;
			ax = 12; aEx = 17;
			ay = 1; aEy = 1;
			ori = 1;

			life = 3;
		}




	}
	system("color 0C");
	Beep(523,500)
	cout << "G A M E		O V E R";
	scores();

}
void help()
{
	string line;
	myhandler.open("help.txt");
	if (myhandler.is_open())
	{
		while (getline(myhandler, line))
		{
			cout << line << '\n';
		}
		myhandler.close();
	}
	else cout << "Unable to open file";

	menu();
}


void scores()
{

	int highScores[NUM_HIGH_SCORES];
	// initialize high scores to 0
	for (int i = 0; i < NUM_HIGH_SCORES; i++) {
		highScores[i] = 0;
	}
	// read high scores from file
	ifstream input("highscores.txt");
	if (input) {
		// read high scores from file and store them in array
		int score;
		int index = 0;
		while (input >> score && index < NUM_HIGH_SCORES) {
			highScores[index] = score;
			index++;
		}
	}

	// check if current score should be added to high scores
	int minScore = highScores[0];
	int minScoreIndex = 0;
	for (int i = 0; i < NUM_HIGH_SCORES; i++) {
		if (highScores[i] < minScore) {
			minScore = highScores[i];
			minScoreIndex = i;
		}
	}
	if (score > minScore) {
		// current score is a high score, so update the array
		highScores[minScoreIndex] = score;
	}
	// write high scores back to file
	ofstream output("highscores.txt");
	for (int i = 0; i < NUM_HIGH_SCORES; i++) {
		output << highScores[i] << endl;
	}
}

void displays_scores() {

	const int MAX_SIZE = 100; // maximum number of numbers that can be stored
	int highScores[MAX_SIZE]; // create an array to store the numbers
	int count = 0; // number of numbers read so far

	std::ifstream input_file("highscores.txt"); // open the file for reading
	int number;
	while (input_file >> number) { // read one number from the file at a time
		if (count < MAX_SIZE) { // check if there is space in the array
			highScores[count] = number; // store the number in the array
			++count; // increment the count of numbers read
		}
	}

	//sorting the scores for displaying
	for (int i = 0; i < count - 1; i++) {			// bubble sort
		for (int j = 0; j < count - i - 1; j++) {
			if (highScores[j] > highScores[j + 1]) {
				int temp = highScores[j];
				highScores[j] = highScores[j + 1];
				highScores[j + 1] = temp;
			}
		}
	}

	// print out the numbers that were read from the file
	for (int i = 0; i < count; ++i) {

		if (highScores[i] != 0)
			cout << highScores[i] << " ";
	}
}