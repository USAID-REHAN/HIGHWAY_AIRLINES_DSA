#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../CLI/Colors.h"
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
      cout << Colors::BOLD << Colors::BRIGHT_RED
           << "   [-] NO ACTIVITY LOGS AVAILABLE!" << Colors::RESET << endl;
      return;
    }

    cout << Colors::BOLD << Colors::BRIGHT_CYAN
         << "\n========== ACTIVITY LOG ==========\n"
         << Colors::RESET;
    LogNode *temp = head;
    int count = 1;
    while (temp != nullptr) {
      cout << Colors::BRIGHT_GREEN << "   [" << count << "] " << Colors::RESET
           << "[" << temp->timestamp << "] " << temp->action << endl;
      temp = temp->next;
      count++;
    }
    cout << Colors::BOLD << Colors::BRIGHT_CYAN
         << "==================================\n"
         << Colors::RESET;
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