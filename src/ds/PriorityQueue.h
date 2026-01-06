#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "../models/Passenger.h"
#include <iostream>
#include <string>

using namespace std;

struct PriorityNode {
  Passenger passenger;
  int priority; // LOWER NUMBER = HIGHER PRIORITY (1=PREMIUM, 4=ECONOMY)

  // default constructor
  PriorityNode() { priority = 4; }

  // parameterized constructor
  PriorityNode(Passenger p, int pr) {
    passenger = p;
    priority = pr;
  }
};

class PriorityQueue {
private:
  PriorityNode *heap;
  int capacity;
  int size;

  // restores heap property from bottom up
  void heapifyUp(int index) {
    if (index == 0) {
      return;
    }

    int parent = (index - 1) / 2;

    // MIN-HEAP: LOWER PRIORITY NUMBER = HIGHER PRIORITY
    if (heap[index].priority < heap[parent].priority) {
      PriorityNode temp = heap[index];
      heap[index] = heap[parent];
      heap[parent] = temp;
      heapifyUp(parent);
    }
  }

  // restores heap property from top down
  void heapifyDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < size && heap[left].priority < heap[smallest].priority) {
      smallest = left;
    }

    if (right < size && heap[right].priority < heap[smallest].priority) {
      smallest = right;
    }

    if (smallest != index) {
      PriorityNode temp = heap[index];
      heap[index] = heap[smallest];
      heap[smallest] = temp;
      heapifyDown(smallest);
    }
  }

public:
  // constructor for priority queue
  PriorityQueue() {
    capacity = 100;
    heap = new PriorityNode[capacity];
    size = 0;
  }

  // inserts a passenger into the queue
  void insert(Passenger passenger) {
    if (size == capacity) {
      cout << "PRIORITY QUEUE IS FULL!" << endl;
      return;
    }

    int priority = passenger.getPriority();
    heap[size] = PriorityNode(passenger, priority);
    heapifyUp(size);
    size++;
  }

  // removes and returns the highest priority passenger
  Passenger removeMax() {
    if (size == 0) {
      cout << "PRIORITY QUEUE IS EMPTY!" << endl;
      return Passenger();
    }

    Passenger highestPriority = heap[0].passenger;
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);

    return highestPriority;
  }

  // displays all passengers in boarding order
  void displayBoardingOrder() {
    if (size == 0) {
      cout << "   [-] NO PASSENGERS IN BOARDING QUEUE!" << endl;
      return;
    }

    cout << "\n========== BOARDING ORDER (BY PRIORITY) ==========\n";

    // CREATE TEMPORARY COPY TO DISPLAY
    PriorityNode *tempHeap = new PriorityNode[size];
    int tempSize = size;

    for (int i = 0; i < tempSize; i++) {
      tempHeap[i] = heap[i];
    }

    int position = 1;
    while (tempSize > 0) {
      // FIND MIN (HIGHEST PRIORITY)
      int minIndex = 0;
      for (int i = 1; i < tempSize; i++) {
        if (tempHeap[i].priority < tempHeap[minIndex].priority) {
          minIndex = i;
        }
      }

      Passenger p = tempHeap[minIndex].passenger;
      cout << "   [" << position << "] " << p.getName()
           << " (ID: " << p.getPassengerID()
           << " | Type: " << p.getPassengerType() << ")" << endl;

      // REMOVE FROM TEMP ARRAY
      tempHeap[minIndex] = tempHeap[tempSize - 1];
      tempSize--;
      position++;
    }

    delete[] tempHeap;
    cout << "=================================================\n";
  }

  // returns current size of the queue
  int getSize() { return size; }

  // destructor to free memory
  ~PriorityQueue() { delete[] heap; }
};

#endif