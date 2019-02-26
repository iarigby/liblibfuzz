#include <iostream>
#include <cstdlib>
#include "stack-nontemplate.h"
// from https://www.techiedelight.com/stack-implementation-in-cpp/

// define default capacity of the stack

// Constructor to initialize stack

stack::stack(int size)
{
    arr = new int[size];
    capacity = size;
    top = -1;
}

stack::~stack() {
    delete[] arr;
}

// helper function to communicate results since 
// can't get return types :D
void stack::toggleOutput(bool outPutMessages) {
    this->outPutMessages = outPutMessages;
}

// Utility function to add an element x in the stack
void stack::push(int x)
{
    if (isFull())
    {
        if (this->outPutMessages) {
            std::cout << "OverFlow\nProgram Terminated\n";
        }
        exit(EXIT_FAILURE);
    }

    if (this->outPutMessages) {
        std::cout << "Inserting " << x << std::endl;
    }
    arr[++top] = x;
}

// Utility function to pop top element from the stack
int stack::pop()
{
    // check for stack underflow
    if (isEmpty())
    {
        if (this->outPutMessages) {
            std::cout << "UnderFlow\nProgram Terminated\n";
        }
        exit(EXIT_FAILURE);
    }

    if (this->outPutMessages) {
        std::cout << "pop: Removing " << peek() << std::endl;
}

    // decrease stack size by 1 and (optionally) return the popped element
    return arr[top--];
}

// Utility function to return top element in a stack
int stack::peek()
{
    if (!isEmpty()) {
        if (this->outPutMessages) {
            std::cout << "peek: returning " << arr[top] << std::endl; 
        }
        return arr[top];
    }
    else
        exit(EXIT_FAILURE);
}

// Utility function to return the size of the stack
int stack::size()
{
    return top + 1;
}

// Utility function to check if the stack is empty or not
bool stack::isEmpty()
{
    return top == -1;	// or return size() == 0;
}

// Utility function to check if the stack is full or not
bool stack::isFull()
{
    return top == capacity - 1;	// or return size() == capacity;
}