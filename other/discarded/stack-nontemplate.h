#ifndef STACK_H
#define STACK_H

#define SIZE 10

class stack
    {
        int *arr;
        int top;
        int capacity;
        bool outPutMessages = false;
    public:
        stack(int size = SIZE);		// constructor
        ~stack();
        void toggleOutput(bool newValue);
        void push(int);
        int pop();
        int peek();

        int size();
        bool isEmpty();
        bool isFull();
    };

#endif // STACK_H