/*
CS 202 Assignment 4

Name: Keith Beauvais, 5005338658, CS 202 Assignment 4
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include "mastermind.h"
using namespace std;

void setupGame(mastermind*&, mastermind*&);
void loadGame(mastermind*&, mastermind*&);
void saveGame(mastermind*&, mastermind*&);
bool yesOrNo(string);
void playGame(mastermind*&, mastermind*&);
string formatString(string);

int main()
{
	mastermind * currentGame;
	mastermind * savedGame;
	char choice;
	bool done = false;

	currentGame = savedGame = NULL;

	while (!done)
	{
		cout << endl;

		cout << "Do wish to (P)lay a new game, (C)ontinue current game"
		 	 << ", (L)oad saved game, or (Q)uit)? ";

		cin >> choice;

		switch (tolower(choice))
		{
			case 'p':
				setupGame(currentGame, savedGame);
				playGame(currentGame, savedGame);
				break;

			case 'l':
				loadGame(currentGame, savedGame);
				playGame(currentGame, savedGame);
				break;

			case 'c':
				playGame(currentGame, savedGame);
				break;

			case 'q':
				done = true;
				break;

			default:
				cout << "Nope. 0/10. Do not approve of this input" << endl;
				break;
		}

	}

	//deallocate the objects if any are still left after
	//user decides to quit
	if (currentGame != NULL)
		delete currentGame;

	if (savedGame != NULL)
		delete savedGame;

	cout << endl;
	cout << "Ok well, I hope this was enjoyable" << endl;

	return 0;
}
/* setupGame - this function creates a new game by performing the following tasks:
	- Prompt the user for peg colors terminated with ”0”.
	- If no currentGame in progress, it will allocate a new game to currentGame pointer
		by passing the vector playerInput to the constructor.
	- If there is a current game in progress, ask the user if they wish to save the
		game, if they wish to save the game call the saveGame function if the saveGame
		function did not actually save the game then exit the setup function, otherwise it
		will allocate a new game to currentGame pointer by passing the vector playerInput
		to the constructor.
	- If there is a current game in progress, and the user does not want to save the
		game, deallocate the currentGame and go to allocate a new game to currentGame pointer
		by passing the vector playerInput to the constructor.


		mastermind*& currentGame - currentGame is a reference pointer

		mastermind*& savedGame - savedGame is a reference pointer

		return value - Void function does not return a value.
*/
void setupGame(mastermind*& currentGame, mastermind*& savedGame){
	string line, yOrN, lowerInput;
	int index = 0;
	vector<string> playerInput;

	cout << "Enter the peg color followed by 0" << endl;
	cin >> line;
	cout<<endl;

	while(line == "0"){
		cout << "Sorry! You need at least 1 peg to play the game" <<endl;
		cin >> line;
	}

	lowerInput = formatString(line);
	playerInput.push_back(lowerInput);

	while(line != "0"){
		cin >> line;
		lowerInput = formatString(line);
		playerInput.push_back(lowerInput);
	}


	if(currentGame == NULL){
		currentGame = new mastermind(playerInput);
		return;
	}

	if (currentGame != NULL){
		cout << "You already have a game in progress" << endl;
		cout <<"Do you wish to save the game? " << endl;
		if(yesOrNo("(Y/N)") == true){
			cout << "Saving current game...."<<endl;
			saveGame(currentGame,savedGame);
			if(currentGame == NULL){
				currentGame = new mastermind(playerInput);
			}
		}
		else{
			delete currentGame;
			currentGame = NULL;
			currentGame = new mastermind(playerInput);
		}
	}
}
/* saveGame - this function creates a new game by performing the following tasks:
	- If there is no saved game, set saveGame to currentGame and assign currentGame
		to NULL and exit function
	- If there is a saved game, ask the user if they still want to save over the savedGame,
		if they want to save over, deallocate savedGame and set it to currentGame, then
		set currentGame to NULL
	- If the user does not want to save the game then do nothing and exit from the function

		mastermind*& currentGame - currentGame is a reference pointer

		mastermind*& savedGame - savedGame is a reference pointer

		return value - Void function does not return a value.

*/
void saveGame(mastermind*& currentGame, mastermind*& savedGame){

	string yOrN;

	if(savedGame == NULL){
		savedGame = currentGame;
		currentGame = NULL;
		return;
	}
	if(savedGame != NULL){
		cout << "There is a saved game"<<endl;
		cout << "This action will destroy/overwrite previously saved game. Is this ok? " << endl;
		if(yesOrNo("(Y/N)") == true){
			delete savedGame;
			savedGame = currentGame;
			currentGame = NULL;
		}
		else{
			return;
		}
	}
	savedGame = currentGame;
	currentGame = NULL;
}
/* loadGame - this function creates a new game by performing the following tasks:
	- If there is no saved game, exit out of the function
	- If there is a current game, ask the user if they wish to destroy this game,
		if they do, destroy the game and go to set current game with the game in saved
		game and set saved game to NULL
	- If they do not wish to destroy the current game, then exit the function
	- Set current game with the game in saved game and set saved game to NULL

		mastermind*& currentGame - currentGame is a reference pointer

		mastermind*& savedGame - savedGame is a reference pointer

		return value - Void function does not return a value.

*/
void loadGame(mastermind*& currentGame, mastermind*& savedGame){

	string yOrN;
	if(savedGame == NULL){
		cout << "There is no game to load. Unable to complete the task."<<endl;
		cout<<endl;
		return;
	}
	if(currentGame!= NULL){
		cout<< "Do you wish to destroy this game?" << endl;
		if(yesOrNo("(Y/N)") == true){
			delete currentGame;
			currentGame = savedGame;
			savedGame = NULL;
		}
		else{
			return;
		}
	}
	else{
		currentGame = savedGame;
		savedGame = NULL;
	}
}

bool yesOrNo(string msg){
	char choice;

	cout << endl;

	do{
		cout << msg;
		cin >> choice;
		choice = tolower(choice);
	}
	while (choice != 'y' && choice != 'n');

	return choice == 'y';
}
/* playGame - this function creates a new game by performing the following tasks:
	- If there is no current game, exit out of the function
	- Output the turn number and output the amount of peg colors the user must enter
	- If they enter ”P” or ”p” ask the user if they wish to save their progress, if
		they do then call save game and exit the function, if they do not wish to save
		the game then just exit the function without modifying currentGame or savedGame
	- If they entered their set of colors for the pegs, call currentGame’s move function
	- Output the silver and gold pegs
	- If the game is over (win/lose) output the appropriate function, the destroy the
		currentGame, set the pointer to NULL as well and escape the game.


		mastermind*& currentGame - currentGame is a reference pointer

		mastermind*& savedGame - savedGame is a reference pointer

		return value - Void function does not return a value.

*/
void playGame(mastermind*& currentGame, mastermind*& savedGame){
	int gold=0, silver=0, var;
	string userInput, yOrN, lowerInput;
	vector<string> guess;


	if(currentGame == NULL){
		cout << "No current game found" << endl;
		return;
	}
	do{
		cout << "Turn "<< currentGame->getMoveIndex()+1;
		cout <<": Enter "<< currentGame->getNumberOfColumns()-1 <<" colors or (P)ause"<< endl;
		cout <<endl;
		cin >> userInput;

		if(userInput == "p"||userInput == "P"){
			cout<< "Ok, we all need a break sometimes"<<endl;
			cout<< "Do you wish to to save progress?" << endl;
			if(yesOrNo("(Y/N)")== true){
				cout<<"Saving Game..."<<endl;
				saveGame(currentGame,savedGame);
				return;
			}
			else{
				cout<<"Ok thats fine, you can always resume"<<endl;
				return;
			}
		}
		lowerInput = formatString(userInput);//sets userInput to lowercase
		guess.push_back(lowerInput);//pushes back lowercase in vector

		for(int i = 0; i < currentGame->getNumberOfColumns()-2; i++){
			cin >> userInput;
			lowerInput = formatString(userInput);//sets userInput to lowercase
			guess.push_back(lowerInput);//pushes back lowercase in vector
		}
			var = currentGame->move( guess , gold, silver);//calls on move function and sets it to var
			guess.clear();
			cout<< "Gold Pegs: " << gold << endl;
			cout<< "Silver Pegs: " << silver << endl;
			cout<<endl;

			if(var == 1){
				cout << "You Won!, Destroying Game" << endl;
				delete currentGame;
				currentGame = NULL;
				guess.clear();
				return;
			}
			if(var == -1){
				cout << "You Lost!, Destroying Game" << endl;
				delete currentGame;
				currentGame = NULL;
				guess.clear();
				return;
			}

		guess.clear();
	}
	while(var == 0);
}
/* formatString - takes in any string and makes it lower case.

		string s - string to be converted to lowercase to make the functions case insensitive.

		return value - returns a string of all lowercase.

*/
string formatString(string s){
	for(int i =0; i < s.length(); i++){
    s[i]=tolower(s[i]);
  }
  return s;
}
