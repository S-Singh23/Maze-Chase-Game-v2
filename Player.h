#pragma once
#include <iostream>
#include <cctype> 
#include "PrimMaze.h"
using namespace std;

class Player
{
    int curRow;
    int curCol;
    int curIndex;
    
    int nextRow;
    int nextCol;
    int nextIndex;
    
    char nextMove;

    bool requestMoveFromPlayer(PrimMaze& grid)
    {
        int counter = 0;
        nextMove = '@';
        bool validEntry = false;
        while(!validEntry)
        {
			//Return false if the player has tried to enter a move 3 times and failed.
            if (counter == 3)
            {
                return false; 
            }
			//Tell the player to enter N, S, E, or W to move  
            cout << "Player enter N, S, E, or W to move" << '\n' << "Make 3 invaild moves to quit, however no score will  be counted" << '\n';

			//Set nextMove to the player's response
            cin >> nextMove; 
			//Convert nextMove to lower case
            nextMove = tolower(nextMove); 
            //Check if nextMove is 'n','s','e' or 'w'
            if(nextMove == 'n' ||nextMove == 's' ||nextMove == 'e' ||nextMove == 'w') 
            {
				//call calculateNextRC to update the requested next move
                calculateNextRC();
                //set validEntry based on a call to checkMoveValid()
                if (checkMoveValid(grid))
                {
                    validEntry = true;
                    counter = 0; 
                }
                else
                {
                    validEntry = false; 
                    counter++;   
                }
            }
        }
        return true;
    }
    void calculateNextRC()
    {
		//update nextRow and nextCol based on nextMove
        if (nextMove == 'n')
        {
            nextRow = curRow - 1;
            nextCol = curCol;
        }
        else if (nextMove == 's')
        {
            nextRow = curRow + 1;
            nextCol = curCol;
        }
        else if (nextMove == 'e')
        {
            nextRow = curRow;
            nextCol = curCol + 1; 
        }
        else if (nextMove == 'w')
        {
            nextRow = curRow;
            nextCol = curCol - 1; 
        }
    }

    bool checkMoveValid(PrimMaze& grid)
    {
		//check the grid to make sure the row and col is valid
        if(grid.isValid(nextRow, nextCol))
        {
			//calculate nextIndex only if row and col are valid
            nextIndex = grid.indexFrom2D(nextRow, nextCol); 
            //check if the index is an open space
			if(grid.getMaze().at(nextIndex) == ' ' )
            {
                return true;
            }
        }
        return false;
    }

public:
    Player(int row, int col)
    {
        curRow = row;
        curCol = col;
    }
    Player(int index, PrimMaze& grid)
    {
        curRow = grid.indexTo2DRow(index);
        curCol = grid.indexTo2DCol(index);
        curIndex = index;
    }

    int getIndex() {return curIndex;}

    int playerTakeTurn(PrimMaze& grid)
    {
		//request a move from the player
        bool request; 
        request = requestMoveFromPlayer(grid);
		//If that returns true...
        if(request)
        {
			//update curRow, curCol, and curIndex
            curRow = nextRow;
            curCol = nextCol;
            curIndex = nextIndex;
			//return curIndex
            return curIndex;
        }
		//If the request returned false, return -1
        cout << "Game Over You Quit" << '\n';
        return -1; 
    }
};
