/*

	Legend for in game:
	# is a wall
	. is a floor
	$ is a gold coin
	x is a trap
	s is the start of the level
	f is the end of the game
	@ is the player
	2-5 is a level transition to the next level (indicated by the number)

	Controls:
	W forward
	A left
	S down
	D right

	(not case sens)

// NOTE TO SELF

	Understand my logic in the future. I have created this application to test out arrays and specifically the multidimensional arrays.
	SO problems I have encountered in this program is: passing arrays as parameters, returning arrays and parsing data from files.
	Ways I have went to solve these issues started with using stringstream to parse the ints from the file (data on 1st line).
	Next, I passed single dimension arrays to capture the entire data in one large array -- line by line, and then making a 2D array 
	and setting each character of the single array equal to the 2D array by using substring on each line of the 1D array.

	Cool stuff to look at: ParseFile Function, copying data from single array to 2D array and the commented part in the main(), 
	specifically, the cycling through array using sizeof() to find the size of a 2D array, helps you determine the rows and cols size.

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void parseFile(string name, int intArray[]);
void mapToArray(string name, string map[]);
void clearScreen();

int main()
{
	/*
	NOTES: 

	string array[3][2] = {{"a", "b",} , {"c", "d"} , {"e", "f"}};

	// CYCLE THROUGH ARRAY
	for (int r = 0; r < sizeof(array) / sizeof(*array); r++) // ROWS
	{
		for (int c = 0; c < sizeof(array[0]) / sizeof(*array[0]); c++) // COLS
		{
			cout << array[r][c];
		}
		cout << endl;
	}
	//cout << endl;
	//cout << sizeof(array) / sizeof(*array) << endl; // PRINTS ROWS.
	//cout << sizeof(array[0]) / sizeof(*array[0]) << endl; // PRINTS COLS
	*/

	int intArray[2];
	int currentLevel = 1;
	int score = 0;
	int health = 100;
	int startLocationRow, startLocationCol;
	string playerMovementFull;
	bool gameEnd = false; // Game is ended when reach end of level 5.
	
	while(currentLevel < 6)
	{

	stringstream loadMap;
	loadMap << currentLevel;
	string currentLevelPartOne = loadMap.str();

	string currentLevelStr = "map" + currentLevelPartOne + ".txt";


	parseFile(currentLevelStr, intArray);

	string map[intArray[1] + 1];

	mapToArray(currentLevelStr, map);

	string map2D[intArray[1]][intArray[0]];
	for (int row = 0; row < intArray[1]; row++)
{
	for (int col = 0; col < intArray[0]; col++) // MAP
	{
		map2D[row][col] = map[row+1].substr(col,1);
		//cout << map2D[row][col];
		if (map[row+1].substr(col,1) == "s") 
		{
			startLocationRow = row;
			startLocationCol = col;
		}
	}
	//cout << endl;
}
		map2D[startLocationRow][startLocationCol] = "@";	
///
//Print 2D Array

	for (int r = 0; r < intArray[1]; r++) // ROWS
	{
		for (int c = 0; c < intArray[0]; c++) // COLS
		{
			cout << map2D[r][c];
		}
		cout << endl;
	}

///
	stringstream ss2;
	ss2 << currentLevel + 1;
	string nextLevel = ss2.str();
	
	string playerMovement;
	cin >> playerMovementFull;
	
while(!gameEnd)
{
	clearScreen();

	for (int run = 0; run < playerMovementFull.size(); run++ ){
		playerMovement = playerMovementFull.substr(run,1);

	if(playerMovement == "w" || playerMovement == "W")
	{
		if(startLocationRow - 1 >= 0)
		{
			if(map2D[startLocationRow-1][startLocationCol] != "#")
			{
				if(map2D[startLocationRow-1][startLocationCol] == "$")
				{
					score += 5;
				}
				if(map2D[startLocationRow-1][startLocationCol] == nextLevel || map2D[startLocationRow-1][startLocationCol] == "f")
				{
					clearScreen();
					currentLevel += 1;
					gameEnd = true;
				}
				if(map2D[startLocationRow-1][startLocationCol] == "x")
				{
					health -= 20;
					if(health <= 0)
					{
						clearScreen();
						cout << "You lost on level " << currentLevel << "!" << endl;
						cout << "Your score was " << score << endl;
						exit(1);
					}
				}
				map2D[startLocationRow-1][startLocationCol] = "@";
				map2D[startLocationRow][startLocationCol] = ".";
				startLocationRow -= 1;
			}
		}
	}
	if(playerMovement == "s" || playerMovement == "S")
	{
		if(startLocationRow + 1 <= intArray[1]-1)
		{
			if(map2D[startLocationRow+1][startLocationCol] != "#")
			{
				if(map2D[startLocationRow+1][startLocationCol] == "$")
				{
					score += 5;
				}
				if(map2D[startLocationRow+1][startLocationCol] == nextLevel || map2D[startLocationRow+1][startLocationCol] == "f")
				{
					clearScreen();
					currentLevel += 1;
					gameEnd = true;
				}
				if(map2D[startLocationRow+1][startLocationCol] == "x")
				{
					health -= 20;
					if(health <= 0)
					{
						clearScreen();
						cout << "You lost on level " << currentLevel << "!" << endl;
						cout << "Your score was " << score << endl;
						exit(1);
					}
				}
				map2D[startLocationRow+1][startLocationCol] = "@";
				map2D[startLocationRow][startLocationCol] = ".";
				startLocationRow += 1;
			}
		}
	}
	if(playerMovement == "a" || playerMovement == "A")
	{ 
		if(startLocationCol - 1 >= 0)
		{
			if(map2D[startLocationRow][startLocationCol-1] != "#")
			{
				if(map2D[startLocationRow][startLocationCol-1] == "$")
				{
					score += 5;
				}
				if(map2D[startLocationRow][startLocationCol-1] == nextLevel || map2D[startLocationRow][startLocationCol-1] == "f")
				{
					clearScreen();
					currentLevel += 1;
					gameEnd = true;
				}
				if(map2D[startLocationRow][startLocationCol-1] == "x")
				{
					health -= 20;
					if(health <= 0)
					{
						clearScreen();
						cout << "You lost on level " << currentLevel << "!" << endl;
						cout << "Your score was " << score << endl;
						exit(1);
					}
				}
				map2D[startLocationRow][startLocationCol-1] = "@";
				map2D[startLocationRow][startLocationCol] = ".";
				startLocationCol -= 1;
			}
		}
	}
	if(playerMovement == "d" || playerMovement == "D")
	{
		if(startLocationCol + 1 <= intArray[0]-1)
		{
			if(map2D[startLocationRow][startLocationCol+1] != "#")
			{
				if(map2D[startLocationRow][startLocationCol+1] == "$")
				{
					score += 5;
				}
				if(map2D[startLocationRow][startLocationCol+1] == nextLevel || map2D[startLocationRow][startLocationCol+1] == "f")
				{
					clearScreen();
					currentLevel += 1;
					gameEnd = true;
				}
				if(map2D[startLocationRow][startLocationCol+1] == "x")
				{
					health -= 20;
					if(health <= 0)
					{
						clearScreen();
						cout << "You lost on level " << currentLevel << "!" << endl;
						cout << "Your score was " << score << endl;
						exit(1);
					}
				}
				map2D[startLocationRow][startLocationCol+1] = "@";
				map2D[startLocationRow][startLocationCol] = ".";
				startLocationCol += 1;
			}
		}
	}
}
///
//Print 2D Array

	for (int r = 0; r < intArray[1]; r++) // ROWS
	{
		for (int c = 0; c < intArray[0]; c++) // COLS
		{
			cout << map2D[r][c];
		}
		cout << endl;
	}
	cout << "Score: " << score << endl;
	cout << "Health: " << health << endl;
///
	if(!gameEnd)
	cin >> playerMovementFull;

}
clearScreen();
gameEnd = false;
}
	cout << "You win with a score of: " << score << endl;
	return 0;
}

void parseFile(string name, int intArray[])
	{
		ifstream myFile;
		int count = 0;
		myFile.open(name);

		if(myFile.is_open())
		{
			string line;
			getline(myFile, line);

			stringstream stream(line);
			while (1)
			{
				int n;
				stream >> n;
				if (!stream)
					break;
				intArray[count] = n;
				count++;

			}

			myFile.close();
		}
		else 
		{
			cout << "File could not open!" << endl;
			exit(1);
		}

	}

void mapToArray(string name, string map[])
{
	ifstream myFile;
	myFile.open(name);

	if(myFile.is_open())
	{
		string line;
		int count = 0;

		while(getline(myFile, line))
		{
			map[count] = line;
			count ++;
		}
		myFile.close();
	}

	else 
	{
		cout << "File could not open!" << endl;
		exit(1);
	}
}
void clearScreen()
{
	for(int clear = 0; clear < 10; clear++)
	{
		cout << endl;
	}
}
