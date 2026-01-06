#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include "../CLI/Colors.h"
#include "../models/Passenger.h"
#include "FileManager.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class AuthManager {
private:
  vector<Passenger> *passengersRef;

  // generates a unique passenger id
  string generatePassengerID() {
    int maxID = 0;
    for (int i = 0; i < passengersRef->size(); i++) {
      string id = (*passengersRef)[i].getPassengerID();
      if (id.length() > 1) {
        int numID = stoi(id.substr(1));
        if (numID > maxID) {
          maxID = numID;
        }
      }
    }
    maxID++;
    return "P" + to_string(maxID);
  }

public:
  // constructor for auth manager
  AuthManager(vector<Passenger> *passengers) { passengersRef = passengers; }

  // handles passenger login
  Passenger *loginPassenger(string email, string password) {
    for (int i = 0; i < passengersRef->size(); i++) {
      if ((*passengersRef)[i].getEmail() == email &&
          (*passengersRef)[i].getPassword() == password) {
        return &(*passengersRef)[i];
      }
    }
    return nullptr;
  }

  // handles passenger signup
  bool signupPassenger(string name, string email, string password, string phone,
                       string type) {

    // CHECK IF EMAIL ALREADY EXISTS
    for (int i = 0; i < passengersRef->size(); i++) {
      if ((*passengersRef)[i].getEmail() == email) {
        return false;
      }
    }

    string newID = generatePassengerID();
    Passenger newPassenger(newID, name, email, password, phone, type);
    passengersRef->push_back(newPassenger);
    return true;
  }

  // handles admin login
  bool loginAdmin(string filename, string username, string password) {
    return FileManager::verifyAdmin(filename, username, password);
  }
};

#endif