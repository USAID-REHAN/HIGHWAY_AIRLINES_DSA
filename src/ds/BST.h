#ifndef BST_H
#define BST_H

#include "../models/Flight.h"
#include <iostream>

struct BSTNode{
    Flight flight;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Flight f){
        flight = f;
        left = nullptr;
        right = nullptr;
    }
};

class BST{
    private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, Flight flight){
        if(node == nullptr){
            return new BSTNode(flight);
        }

        if(flight.getFlightID() < node->flight.getFlightID()){
            node->left = insert(node->left, flight);
        }
        else if(flight.getFlightID() > node->flight.getFlightID()){
            node->right = insert(node->right, flight);
        }

        return node;
    }

    BSTNode* search(BSTNode* node, std::string flightID){
        if(node == nullptr){
            return nullptr;
        }

        if(flightID == node->flight.getFlightID()){
            return node;
        }

        if(flightID < node->flight.getFlightID()){
            return search(node->left, flightID);
        }
        else{
            return search(node->right, flightID);
        }
    }

    void inorder(BSTNode* node){
        if(node != nullptr){
            inorder(node->left);
            
            std::cout << "\nFLIGHT ID: " << node->flight.getFlightID()
                      << " | " << node->flight.getOrigin() 
                      << " -> " << node->flight.getDestination()
                      << " | TIME: " << node->flight.getDepartureTime()
                      << " | DATE: " << node->flight.getDate()
                      << " | STATUS: " << node->flight.getStatus() << std::endl;
            
            inorder(node->right);
        }
    }

    void destroyTree(BSTNode* node){
        if(node != nullptr){
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    public:
    BST(){
        root = nullptr;
    }

    void insert(Flight flight){
        root = insert(root, flight);
    }

    Flight* search(std::string flightID){
        BSTNode* node = search(root, flightID);
        if(node == nullptr){
            return nullptr;
        }
        return &(node->flight);
    }

    void displayInorder(){
        if(root == nullptr){
            std::cout << "NO FLIGHTS IN SYSTEM!" << std::endl;
            return;
        }
        std::cout << "\n========== ALL FLIGHTS (SORTED BY ID) ==========";
        inorder(root);
        std::cout << "===============================================\n";
    }

    ~BST(){
        destroyTree(root);
    }
};

#endif