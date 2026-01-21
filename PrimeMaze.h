
#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>   // For rand()
#include <ctime>     // For time()

using namespace std;

class PrimMaze
{
private:
    vector<char> maze;
    int width;
    int height;
    int mazeWidth;
    int mazeHeight;

    void setMaze()
    {
        srand(time(NULL));  // Seed for random number generator
        mazeWidth = width * 2 + 1;// = set the actual width of the maze;
        mazeHeight = height * 2 + 1 ;// = set the actual height of the maze;
        //resize the maze vector and fill it with '#' 
        maze.resize(mazeWidth*mazeHeight);
        
        for (int i = 0; i < maze.size(); i++)
        {
            maze.at(i) = '#'; 
        }
    }

    void primMaze() 
    {
		 vector<int> frontier; 

    srand(time(0)); 

    int startRow = rand() % height * 2 + 1;
    int startCol = rand() % width * 2 + 1;

    maze[indexFrom2D(startRow, startCol)] = ' ';  

   
    if (isValid(startRow - 2, startCol)) {
        frontier.push_back(indexFrom2D(startRow - 2, startCol));
    }


    if (isValid(startRow + 2, startCol)) {
        frontier.push_back(indexFrom2D(startRow + 2, startCol));
    }


    if (isValid(startRow, startCol - 2)) {
        frontier.push_back(indexFrom2D(startRow, startCol - 2));
    }


    if (isValid(startRow, startCol + 2)) {
        frontier.push_back(indexFrom2D(startRow, startCol + 2));
    }



    // Prim's algorithm loop
    // Begin a while loop that will end when the frontier is empty
    while (!frontier.empty()) 
    {
        int randIndex = rand() % frontier.size() ; 
        int frontierCell = frontier[randIndex]; 
        frontier.erase(frontier.begin() + randIndex);  

        int frontierRow = indexTo2DRow(frontierCell); 
        int frontierCol = indexTo2DCol(frontierCell); 

        vector<int> mazeNeighbors;
        
    if (isValid(frontierRow - 2, frontierCol) && maze[indexFrom2D(frontierRow - 2, frontierCol)] == ' ') 
    {
        mazeNeighbors.push_back(indexFrom2D(frontierRow - 2, frontierCol));
    }


    if (isValid(frontierRow + 2, frontierCol) && maze[indexFrom2D(frontierRow + 2, frontierCol)] == ' ') 
    {
        mazeNeighbors.push_back(indexFrom2D(frontierRow + 2, frontierCol));
    }


    if (isValid(frontierRow, frontierCol - 2) && maze[indexFrom2D(frontierRow, frontierCol - 2)] == ' ') 
    {
        mazeNeighbors.push_back(indexFrom2D(frontierRow, frontierCol - 2));
    }


    if (isValid(frontierRow, frontierCol + 2) && maze[indexFrom2D(frontierRow, frontierCol + 2)] == ' ') 
    {
        mazeNeighbors.push_back(indexFrom2D(frontierRow, frontierCol + 2));
    }



        
        // If there are valid neighbors in the maze, carve a path between the frontier and ONE of its neighbors
        if (!mazeNeighbors.empty()) 
        {
            int neighbor = mazeNeighbors[rand() % mazeNeighbors.size()];  // Random neighbor
            int neighborRow = indexTo2DRow(neighbor); // = Convert neighbor (1D index) to 2D row
            int neighborCol = indexTo2DCol(neighbor); // = Convert neighbor (1D index) to 2D col

            int foundRow = (frontierRow + neighborRow) / 2;
            int foundCol =  (frontierCol + neighborCol) / 2;

            int foundIndex = indexFrom2D(foundRow, foundCol);

            maze.at(frontierCell) = ' '; 
            maze.at(foundIndex) = ' ';

            if (isValid(frontierRow - 2, frontierCol) && maze.at(indexFrom2D(frontierRow - 2, frontierCol)) == '#' ) 
            {
                frontier.push_back(indexFrom2D(frontierRow - 2, frontierCol));
            }


            if (isValid(frontierRow + 2, frontierCol) && maze.at(indexFrom2D(frontierRow + 2, frontierCol)) == '#')
            {
                frontier.push_back(indexFrom2D(frontierRow + 2, frontierCol));
            }


            if (isValid(frontierRow, frontierCol - 2) && maze.at(indexFrom2D(frontierRow, frontierCol - 2)) == '#') {
                frontier.push_back(indexFrom2D(frontierRow, frontierCol - 2));
            }


            if (isValid(frontierRow, frontierCol + 2) && maze.at(indexFrom2D(frontierRow, frontierCol + 2)) == '#') 
            {
                frontier.push_back(indexFrom2D(frontierRow, frontierCol + 2));
            }
        }
    }
    }

public:
	PrimMaze()
    {
        width = 20;
        height = 10;
        setMaze(); 
        primMaze(); 
    }
	
	//Overload Constructor (custom width and height)
    PrimMaze(int w, int h)
    {
        width = w;
        height = h;
        setMaze(); 
        primMaze(); 
    }
	
	//Overload constructor (custom maze for testing)
	//After calling setMaze(), make maze = layout
    PrimMaze(int w, int h, const vector <char>& layout)
    {
        //width = w;
       // height = h;
        mazeWidth = w * 2 + 1;// = set the actual width of the maze;
        mazeHeight = h * 2 + 1 ;// = set the actual height of the maze;
       
        for (int i = 0; i < layout.size(); i++)
        {
            maze.push_back(layout.at(i));  
        }
        
    }

	//Public function to create a maze.
    void generateMaze()
    {
        primMaze(); 
    }

    int indexTo2DRow(int index) 
    {
        int temp = index / getMazeWidth();
        return temp; 

    }

    int indexTo2DCol(int index) 
    {
        int temp = index % getMazeWidth(); 
        return temp;
    }

    int indexFrom2D(int row, int col) 
    {
        int temp; 

        temp = (row * getMazeWidth()) + col; 

        return temp;
    }

    bool isValid(int row, int col) 
    {
        if ((row < getMazeHeight() && row >= 0) && (col < getMazeWidth() && col >= 0))
        {
            return true; 
        }
        else 
        {
            return false; 
        }
    }

	//Create getters for mazeHeight and mazeWidth
    int getMazeHeight()
    {
        return mazeHeight;
    }

    int getMazeWidth()
    {
        return mazeWidth;
    } 
    
	//Create a getter that returns a reference to maze
    vector<char>& getMaze ()
    {
        return maze; 
    }
	//Function to find valid starting
    //locations for player and enemy

    int startingPositions()
    {
        while (true) 
        {
            int startRow = rand() % height * 2 + 1;
            int startCol = rand() % width * 2 + 1;

            int startIndex = indexFrom2D(startRow, startCol);

            if (isValid(startRow, startCol) && maze.at(startIndex) == ' ')
            {
                return startIndex;
            }
        }
        
    }

	void PElocation()
    {
       int playerIndex = startingPositions();
       int enemyIndex = startingPositions();
    }


    int getEmptyCell()
    {
        while(true)
        {
            int row = rand() % mazeHeight;
            int col = rand() % mazeWidth;
            int index = indexFrom2D(row,col);
            if(maze.at(index) == ' ') return index; 
        }
    }

    void drawMaze(int p, int e) 
    {
        int index; 

         for (int i = 0; i < getMazeHeight(); ++i) 
        {
            for (int j = 0; j < getMazeWidth(); ++j) 
            {
                index = indexFrom2D(i,j);
                if (index == p && index == e)
                {
                    cout << 'X'; 
                }
                else if (index == p)
                {
                    cout << 'P'; 
                }
                else if (index == e)
                {
                    cout << 'E';
                }
                else
                {
                    cout << maze[indexFrom2D(i, j)];
                }
            }
            cout << endl;
        }
    }
};  
