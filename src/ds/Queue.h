#ifndef QUEUE_H
#define QUEUE_H

#include "../CLI/Colors.h"
#include <iostream>
#include <string>

using namespace std;

struct QueueNode {
  string passengerID;
  string flightID;
  QueueNode *next;

  // constructor for queue node
  QueueNode(string pID, string fID) {
    passengerID = pID;
    flightID = fID;
    next = nullptr;
  }
};

class Queue {
private:
  QueueNode *front;
  QueueNode *rear;

public:
  // constructor for queue
  Queue() {
    front = nullptr;
    rear = nullptr;
  }

  // adds an element to the back of the queue
  void enqueue(string passengerID, string flightID) {
    QueueNode *newNode = new QueueNode(passengerID, flightID);

    if (rear == nullptr) {
      front = rear = newNode;
      return;
    }

    rear->next = newNode;
    rear = newNode;
  }

  // removes and returns the front element
  QueueNode *dequeue() {
    if (isEmpty()) {
      return nullptr;
    }

    QueueNode *temp = front;
    front = front->next;

    if (front == nullptr) {
      rear = nullptr;
    }

    return temp;
  }

  // removes and returns the first passenger waiting for a specific flight
  QueueNode *dequeueForFlight(string fID) {
    if (isEmpty())
      return nullptr;

    QueueNode *current = front;
    QueueNode *prev = nullptr;

    while (current != nullptr) {
      if (current->flightID == fID) {
        if (prev == nullptr) {
          front = current->next;
          if (front == nullptr) {
            rear = nullptr;
          }
        } else {
          prev->next = current->next;
          if (current == rear) {
            rear = prev;
          }
        }
        current->next = nullptr;
        return current;
      }
      prev = current;
      current = current->next;
    }
    return nullptr;
  }

  // returns the front element without removing it
  QueueNode *peek() { return front; }

  // checks if the queue is empty
  bool isEmpty() { return front == nullptr; }

  // displays passengers in the waitlist for a flight
  void display(string flightID) {
    if (isEmpty()) {
      cout << Colors::BOLD << Colors::BRIGHT_RED
           << "   [-] NO PASSENGERS IN WAITLIST!" << Colors::RESET << endl;
      return;
    }

    cout << Colors::BOLD << Colors::BRIGHT_CYAN
         << "\n========== WAITLIST FOR FLIGHT " << flightID << " ==========\n"
         << Colors::RESET;
    QueueNode *temp = front;
    int position = 1;
    while (temp != nullptr) {
      if (temp->flightID == flightID) {
        cout << Colors::BRIGHT_GREEN << "   [" << position << "] "
             << Colors::RESET << "Passenger: " << temp->passengerID << endl;
        position++;
      }
      temp = temp->next;
    }
    cout << Colors::BOLD << Colors::BRIGHT_CYAN
         << "=============================================\n"
         << Colors::RESET;
  }

  // destructor to free memory
  ~Queue() {
    while (!isEmpty()) {
      QueueNode *temp = dequeue();
      delete temp;
    }
  }
};

#endif