#include <stdexcept>
#include <iostream>


struct Node 
{
    int distance;  // The priority (distance in this case)
    int cellIndex; // Value to be stored (cell index in this case)
    Node* next;    // Pointer to the next node

    // Constructor for a new node
    Node(int dist, int index) 
	{
		distance = dist; 
		cellIndex = index; 
		next = nullptr;
	}
};

class SLLPriorityQueue 
{
private:
    Node* head;  // Pointer to the first node

public:
    // Constructor to initialize an empty priority queue
    SLLPriorityQueue() 
    {
        head = nullptr;    
    }

    // Destructor to clean up memory
    ~SLLPriorityQueue() 
    {
        while (head != nullptr) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert a new node with the given distance and cellIndex
    void enqueue(int distance, int cellIndex) 
    {
        Node* newNode = new Node(distance, cellIndex);

        // If the list is empty or the new node has a higher priority (smaller distance)
        if (head == nullptr || newNode->distance < head->distance) 
        {
            newNode->next = head; 
            head = newNode;
        }
        else 
        {
            Node* current = head;
            // Traverse the list to find the location where the next node's distance
            // is greater than to the given distance or their is no next object
            while (current->next != nullptr && current->distance <= newNode->distance) 
            {
                current = current->next;
            }

            newNode->next = current->next; 
            current->next = newNode; 
        } 
    }

    // Dequeue (remove and return) the node with the highest priority (smallest distance)
    Node dequeue() 
    {
        if (head == nullptr) 
        {
            throw std::runtime_error("Priority queue is empty!");
        }

        // Remove the head node (smallest distance)
        Node* temp = head;
        Node dequeuedNode = *head;  // Copy the node's data
        head = head->next;
        delete temp;  // Delete the old head
        return dequeuedNode;  // Return the data of the dequeued node
    }

    // Peek at the node with the highest priority without removing it
    Node peek() const 
    {
        if (head == nullptr) 
        {
            throw std::runtime_error("Priority queue is empty!");
        }

        // The head contains the smallest distance
        return *head;
    }

    // Check if the queue is empty
    bool isEmpty() const
    {
        return head == nullptr;
    }
};
