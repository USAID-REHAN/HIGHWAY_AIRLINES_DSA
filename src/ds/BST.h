#ifndef BST_H
#define BST_H

#include "../models/Flight.h"
#include <iostream>
#include <string>

using namespace std;

struct BSTNode {
  Flight flight;
  BSTNode *left;
  BSTNode *right;

  // constructor for bst node
  BSTNode(Flight f) {
    flight = f;
    left = nullptr;
    right = nullptr;
  }
};

class BST {
private:
  BSTNode *root;

  // recursive helper to insert a flight into the tree
  BSTNode *insert(BSTNode *node, Flight flight) {
    if (node == nullptr) {
      return new BSTNode(flight);
    }

    if (flight.getFlightID() < node->flight.getFlightID()) {
      node->left = insert(node->left, flight);
    } else if (flight.getFlightID() > node->flight.getFlightID()) {
      node->right = insert(node->right, flight);
    }

    return node;
  }

  // recursive helper to search for a flight by id
  BSTNode *search(BSTNode *node, string flightID) {
    if (node == nullptr) {
      return nullptr;
    }

    if (flightID == node->flight.getFlightID()) {
      return node;
    }

    if (flightID < node->flight.getFlightID()) {
      return search(node->left, flightID);
    } else {
      return search(node->right, flightID);
    }
  }

  // recursive helper to display flights in sorted order
  void inorder(BSTNode *node) {
    if (node != nullptr) {
      inorder(node->left);

      cout << "\nFLIGHT ID: " << node->flight.getFlightID() << " | "
           << node->flight.getOrigin() << " -> "
           << node->flight.getDestination()
           << " | TIME: " << node->flight.getDepartureTime()
           << " | DATE: " << node->flight.getDate()
           << " | STATUS: " << node->flight.getStatus() << endl;

      inorder(node->right);
    }
  }

  // recursive helper to find the minimum node in a subtree
  BSTNode *minValueNode(BSTNode *node) {
    BSTNode *current = node;
    while (current && current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  // recursive helper to delete a flight from the tree
  BSTNode *remove(BSTNode *root, string flightID) {
    if (root == nullptr) {
      return root;
    }

    if (flightID < root->flight.getFlightID()) {
      root->left = remove(root->left, flightID);
    } else if (flightID > root->flight.getFlightID()) {
      root->right = remove(root->right, flightID);
    } else {
      // node with only one child or no child
      if (root->left == nullptr) {
        BSTNode *temp = root->right;
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        BSTNode *temp = root->left;
        delete root;
        return temp;
      }

      // node with two children: get inorder successor
      BSTNode *temp = minValueNode(root->right);
      root->flight = temp->flight;
      root->right = remove(root->right, temp->flight.getFlightID());
    }
    return root;
  }

  // recursive helper to delete all nodes and free memory
  void destroyTree(BSTNode *node) {
    if (node != nullptr) {
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
    }
  }

public:
  // constructor for bst
  BST() { root = nullptr; }

  // public interface to insert a flight
  void insert(Flight flight) { root = insert(root, flight); }

  // public interface to delete a flight
  void remove(string flightID) { root = remove(root, flightID); }

  // public interface to search for a flight
  Flight *search(string flightID) {
    BSTNode *node = search(root, flightID);
    if (node == nullptr) {
      return nullptr;
    }
    return &(node->flight);
  }

  // displays all flights sorted by id
  void displayInorder() {
    if (root == nullptr) {
      cout << "NO FLIGHTS IN SYSTEM!" << endl;
      return;
    }
    cout << "\n========== ALL FLIGHTS (SORTED BY ID) ==========";
    inorder(root);
    cout << "===============================================\n";
  }

  // destructor to clear the tree
  ~BST() { destroyTree(root); }
};

#endif