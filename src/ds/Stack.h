#ifndef STACK_H
#define STACK_H

#include "../models/Flight.h"
#include <iostream>
#include <string>

using namespace std;

struct StackNode {
  Flight data;
  StackNode *next;

  // constructor for stack node
  StackNode(Flight f) {
    data = f;
    next = nullptr;
  }
};

class Stack {
private:
  StackNode *top;

public:
  // constructor for stack
  Stack() { top = nullptr; }

  // pushes a flight onto the stack
  void push(Flight flight) {
    StackNode *newNode = new StackNode(flight);
    newNode->next = top;
    top = newNode;
  }

  // pops and returns the top flight
  Flight pop() {
    if (isEmpty()) {
      cout << "STACK IS EMPTY!" << endl;
      return Flight();
    }

    StackNode *temp = top;
    Flight flight = temp->data;
    top = top->next;
    delete temp;
    return flight;
  }

  // returns the top flight without removing it
  Flight peek() {
    if (isEmpty()) {
      cout << "STACK IS EMPTY!" << endl;
      return Flight();
    }
    return top->data;
  }

  // checks if the stack is empty
  bool isEmpty() { return top == nullptr; }

  // destructor to free memory
  ~Stack() {
    while (!isEmpty()) {
      pop();
    }
  }
};

#endif