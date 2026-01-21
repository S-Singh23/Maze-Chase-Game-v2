#include <vector>       // For std::vector
#include <climits>      // For INT_MAX
#include <stdexcept>    // For exception handling (optional, depends on SLLPriorityQueue)
#include <iostream>     // For debugging/printing (optional)
#include "SLLPriorityQueue.h"  // Include your priority queue header
#include "PrimMaze.h"      // Include your PrimMaze header

using namespace std;

class Enemy {
public:
    int currentLocation;    // The enemy's current position in the maze (1D index)
    int target;             // The location where the enemy wishes to go (1D index)
    int distanceToTarget;   // The shortest number of steps to the target
    int nextLocation;       // The next cell the enemy should move to (1D index)
    int enemyStartIndex; 

    // Constructor to initialize the enemy's starting position
    Enemy(int start) {
        currentLocation = start;
        distanceToTarget = INT_MAX;
        nextLocation = -1;
    }

    void updateTarget(int location) {
        target = location;
    }

    void updatePathing(const vector<char>& grid, PrimMaze maze) {
        calculateShortestPath(grid, maze);
    }

    void takeStep() {
        if (nextLocation >= 0)
            currentLocation = nextLocation;
    }

    void startIndex(PrimMaze& maze)
    {
        enemyStartIndex = maze.startingPositions(); 
    }

    int getIndex()
    {
        return currentLocation; 
    }

private:
    // Dijkstra's algorithm to calculate the shortest path to the player
    void calculateShortestPath(const vector<char>& grid, PrimMaze maze) {
        // Create a maze object for utility functions (if needed)

        // Initialize distance vector to store the shortest distance to each cell (set to infinity initially)
        vector<int> dist(maze.getMazeWidth() * maze.getMazeHeight(), INT_MAX);

        // Initialize a vector to store the previous cell that led to each current cell
        vector<int> path(maze.getMazeWidth() * maze.getMazeHeight(), -1); // -1 means no previous cell

        // Create the singly linked list priority queue
        SLLPriorityQueue pq;

        int size = dist.size();
        int size2 = target; 

        // Set the distance to the target index as 0
        dist.at(currentLocation) = 0;

        // Enqueue a node with 0 distance and currentLocation index into the priority queue
        pq.enqueue(0, currentLocation);

        int count = 0;
        // While the priority queue is not empty, process the next node
        while (!pq.isEmpty()) {
            // Dequeue the cell with the smallest distance (highest priority)
            Node currentNode = pq.peek();
            int current = currentNode.cellIndex;
            pq.dequeue();
            count++; 

            // If we've reached the goal, stop processing
            if (current == target) {
                break;
            }

            // Convert the current 1D index to 2D coordinates
            int currentRow = maze.indexTo2DRow(current);
            int currentCol = maze.indexTo2DCol(current);

            // Define the four possible directions (N, S, E, W) as 2D row/col changes
            int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

            // Check each neighboring cell
            for (int i = 0; i < 4; i++) {
                int neighborRow = currentRow + directions[i][0];
                int neighborCol = currentCol + directions[i][1];

                // Check if the neighboring cell is within bounds
                if (maze.isValid(neighborRow, neighborCol)) {
                    int neighborIndex = maze.indexFrom2D(neighborRow, neighborCol);

                    // Check if the neighboring cell is not a wall
                    if (grid[neighborIndex] != '#') {
                        // Calculate the new distance to the neighbor
                        int newDist = dist[current] + 1; // this is messing up the code    

                        // If the new distance is shorter than the current known distance to the neighbor
                        if (newDist < dist[neighborIndex]) {
                            // Update the distance in the neighbor's index of the distance vector
                            dist[neighborIndex] = newDist;

                            // Update the location that led to the neighbor in the neighbor's index of the path vector
                            path[neighborIndex] = current;

                            // Add the neighbor to the queue with the updated distance
                            pq.enqueue(newDist, neighborIndex);
                        }
                    }
                }
            }
        }

        // If the target is unreachable
        if (dist[target] == INT_MAX) {
            distanceToTarget = INT_MAX;
            nextLocation = -1;
        } else {
            // Set the shortest distance to the target
            distanceToTarget = dist[target];

            // Backtrack from the target's location to find the next step
            int currentStep = target;
            while (path[currentStep] != currentLocation && path[currentStep] != -1) {
                currentStep = path[currentStep];
            }

            // Set the next location for the enemy to move toward
            nextLocation = currentStep;
        }
    }
};
