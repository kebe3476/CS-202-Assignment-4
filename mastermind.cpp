/*
CS 202 Assignment 4

Name: Keith Beauvais, 5005338658, CS 202 Assignment 4
*/
#include "mastermind.h"
#include <vector>
#include <string>
using namespace std;

mastermind::mastermind(int size){
  maxMoves = 5;
  moves = 0;
  for(int i = 0; i < size; i++){
    solution.push_back("Red");
  }
}

mastermind::mastermind(vector<string> initial){
  maxMoves = 5;
  moves = 0;
  solution = initial;
}
/* move - this function simulates one move/round of the mastermind game. The
  playerMove vector consists of the user’s guess which is a set of pegs with their
  colors, and the function needs to determine how many pegs’s colors are in the same
  respective column as the solution vector (update gold each time), and the colors
  from playerMove that matches with solution but not in the same respective position
  (update silver each time), then update the moves counter.

	vector<string> playerMove - this is the users guess vector that is compared to
  the solution vector.

  int& gold - reference integer that updates the gold counter

  int& silver - reference integer that updates the silver counter

	return value - If it returns 0, the game is not over
  – If it returns 1, the user won (i.e. the amount of gold matches the width of the board)
  – If it returns -1, the user lost (ran out of attempts)

*/
int mastermind::move(vector<string> playerMove, int& gold, int& silver){

  int found = 0; // used a bool flag
  gold = 0;
  silver = 0;

  for(int i = 0; i < getNumberOfColumns(); i++){
    if(playerMove[i] == solution[i]){
      gold++;
      found = 1; // if it goes through gold the bool flag will be changed to 1 not allowing
                //it to go through silver.
    }
    else{
      found = 0; // resets the bool flag
      for(int j = 0; j < getNumberOfColumns(); j++){
        if(playerMove[j] == solution[i] && i != j){
          if((found != 1)){
            silver++;
            found = 0; //resets bool flag
          }
          else{
            break;
          }
        }
      }
    }
  }

  moves++;

  if(gold == playerMove.size()){
    return 1;
  }
  if(moves == maxMoves){
    return -1;
  }
  else{
    return 0;
  }
}

/* getMoveIndex()- getter used to get the moves from the class mastermind

	return value - returns the moves amount,
*/

int mastermind::getMoveIndex() const{
  return moves;
}

/* getNumberOfColumns()- getter used to get the solution size from the class mastermind

	return value - returns the width of the current game.
*/

int mastermind::getNumberOfColumns() const{
  return solution.size();
}
