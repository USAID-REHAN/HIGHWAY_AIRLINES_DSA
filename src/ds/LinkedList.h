#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;

struct LogNode {
  string action;
  string timestamp;
  LogNode *next;

  // constructor for log node
  LogNode(string act, string time) {
    action = act;
    timestamp = time;
    next = nullptr;
  }
};

class LinkedList {
private:
  LogNode *head;

public:
  // constructor for linked list
  LinkedList() { head = nullptr; }

  // inserts a new log entry at the end of the list
  void insertEnd(string action, string timestamp) {
    LogNode *newNode = new LogNode(action, timestamp);

    if (head == nullptr) {
      head = newNode;
      return;
    }

    LogNode *temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = newNode;
  }

  // displays all logs in the list
  void displayAll() {
    if (head == nullptr) {
      cout << "   [-] NO ACTIVITY LOGS AVAILABLE!" << endl;
      return;
    }

    cout << "\n========== ACTIVITY LOG ==========\n";
    LogNode *temp = head;
    int count = 1;
    while (temp != nullptr) {
      cout << "   [" << count << "] [" << temp->timestamp << "] "
           << temp->action << endl;
      temp = temp->next;
      count++;
    }
    cout << "==================================\n";
  }

  // destructor to free memory
  ~LinkedList() {
    LogNode *temp = head;
    while (temp != nullptr) {
      LogNode *nextNode = temp->next;
      delete temp;
      temp = nextNode;
    }
  }
};

#endif