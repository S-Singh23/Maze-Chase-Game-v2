#include <iostream>
#include <vector>
#include <cassert>
#include "Player.h"
#include "Enemy.h"
#include "PrimMaze.h"

using namespace std;

// Test function to verify enemy movement in the maze
void testPlayerAndEnemyMovement() {
    int score = 0; //keeps track of the amount of move made and addone to the score for each move
    PrimMaze maze; 
    Enemy enemy(maze.startingPositions()); 
    Player player(maze.startingPositions(), maze);
    maze.drawMaze(player.getIndex(),enemy.getIndex());
    while (true) {
    if(player.playerTakeTurn(maze) >= 0)
    {
        enemy.updateTarget(player.getIndex());
    }
    else
    {
        return;
    }
    enemy.updatePathing(maze.getMaze(), maze);
    enemy.takeStep();
    maze.drawMaze(player.getIndex(),enemy.getIndex());
    score++; 
    if (enemy.getIndex() == player.getIndex())
    {
        cout << "Game Over You Died" << '\n' << "Your score " << score << '\n';
        break;
    }
    }
    
}

int main() 
{
    testPlayerAndEnemyMovement();
    return 0;
}
