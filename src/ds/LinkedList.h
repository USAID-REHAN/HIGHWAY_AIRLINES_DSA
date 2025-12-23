#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <iostream>

struct LogNode{
    std::string action;
    std::string timestamp;
    LogNode* next;

    LogNode(std::string act, std::string time){
        action = act;
        timestamp = time;
        next = nullptr;
    }
};

class LinkedList{
    private:
    LogNode* head;

    public:
    LinkedList(){
        head = nullptr;
    }

    void insertEnd(std::string action, std::string timestamp){
        LogNode* newNode = new LogNode(action, timestamp);

        if(head == nullptr){
            head = newNode;
            return;
        }

        LogNode* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void displayAll(){
        if(head == nullptr){
            std::cout << "NO ACTIVITY LOGS AVAILABLE!" << std::endl;
            return;
        }

        std::cout << "\n========== ACTIVITY LOG ==========\n";
        LogNode* temp = head;
        int count = 1;
        while(temp != nullptr){
            std::cout << count << ". [" << temp->timestamp << "] " << temp->action << std::endl;
            temp = temp->next;
            count++;
        }
        std::cout << "==================================\n";
    }

    ~LinkedList(){
        LogNode* temp = head;
        while(temp != nullptr){
            LogNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

#endif