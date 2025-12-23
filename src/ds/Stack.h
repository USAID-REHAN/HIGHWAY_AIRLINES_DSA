#ifndef STACK_H
#define STACK_H

#include "../models/Flight.h"
#include <iostream>

struct StackNode{
    Flight data;
    StackNode* next;

    StackNode(Flight f){
        data = f;
        next = nullptr;
    }
};

class Stack{
    private:
    StackNode* top;

    public:
    Stack(){
        top = nullptr;
    }

    void push(Flight flight){
        StackNode* newNode = new StackNode(flight);
        newNode->next = top;
        top = newNode;
    }

    Flight pop(){
        if(isEmpty()){
            std::cout << "STACK IS EMPTY!" << std::endl;
            return Flight();
        }

        StackNode* temp = top;
        Flight flight = temp->data;
        top = top->next;
        delete temp;
        return flight;
    }

    Flight peek(){
        if(isEmpty()){
            std::cout << "STACK IS EMPTY!" << std::endl;
            return Flight();
        }
        return top->data;
    }

    bool isEmpty(){
        return top == nullptr;
    }

    ~Stack(){
        while(!isEmpty()){
            pop();
        }
    }
};

#endif