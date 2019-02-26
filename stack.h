#ifndef STACK_H
#define STACK_H

#define SIZE 10

template <typename T>
class stack
    {
        T *arr;
        int top;
        int capacity;
        bool outPutMessages = false;
    public:
        stack(int size = SIZE);		// constructor
        void toggleOutput(bool newValue);
        void push(T);
        T pop();
        T peek();

        int size();
        bool isEmpty();
        bool isFull();
    };

#endif // STACK_H