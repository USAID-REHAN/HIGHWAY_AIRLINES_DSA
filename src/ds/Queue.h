#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <iostream>

struct QueueNode{
    std::string passengerID;
    std::string flightID;
    QueueNode* next;

    QueueNode(std::string pID, std::string fID){
        passengerID = pID;
        flightID = fID;
        next = nullptr;
    }
};

class Queue{
    private:
    QueueNode* front;
    QueueNode* rear;

    public:
    Queue(){
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(std::string passengerID, std::string flightID){
        QueueNode* newNode = new QueueNode(passengerID, flightID);

        if(rear == nullptr){
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    QueueNode* dequeue(){
        if(isEmpty()){
            return nullptr;
        }

        QueueNode* temp = front;
        front = front->next;

        if(front == nullptr){
            rear = nullptr;
        }

        return temp;
    }

    QueueNode* peek(){
        return front;
    }

    bool isEmpty(){
        return front == nullptr;
    }

    void display(std::string flightID){
        if(isEmpty()){
            std::cout << "NO PASSENGERS IN WAITLIST!" << std::endl;
            return;
        }

        std::cout << "\n===== WAITLIST FOR FLIGHT " << flightID << " =====\n";
        QueueNode* temp = front;
        int position = 1;
        while(temp != nullptr){
            if(temp->flightID == flightID){
                std::cout << position << ". PASSENGER ID: " << temp->passengerID << std::endl;
                position++;
            }
            temp = temp->next;
        }
        std::cout << "==========================================\n";
    }

    ~Queue(){
        while(!isEmpty()){
            QueueNode* temp = dequeue();
            delete temp;
        }
    }
};

#endif