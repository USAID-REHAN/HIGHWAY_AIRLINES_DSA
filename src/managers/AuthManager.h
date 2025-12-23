#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <vector>
#include <iostream>
#include "../models/Passenger.h"
#include "FileManager.h"

class AuthManager{
    private:
    std::vector<Passenger>* passengersRef;

    std::string generatePassengerID(){
        int maxID = 0;
        for(int i = 0; i < passengersRef->size(); i++){
            std::string id = (*passengersRef)[i].getPassengerID();
            if(id.length() > 1){
                int numID = std::stoi(id.substr(1));
                if(numID > maxID){
                    maxID = numID;
                }
            }
        }
        maxID++;
        return "P" + std::to_string(maxID);
    }

    public:
    AuthManager(std::vector<Passenger>* passengers){
        passengersRef = passengers;
    }

    Passenger* loginPassenger(std::string email, std::string password){
        for(int i = 0; i < passengersRef->size(); i++){
            if((*passengersRef)[i].getEmail() == email && 
               (*passengersRef)[i].getPassword() == password){
                std::cout << "\nLOGIN SUCCESSFUL! WELCOME " 
                          << (*passengersRef)[i].getName() << "!" << std::endl;
                return &(*passengersRef)[i];
            }
        }
        std::cout << "\nINVALID EMAIL OR PASSWORD!" << std::endl;
        return nullptr;
    }

    bool signupPassenger(std::string name, std::string email, std::string password, 
                        std::string phone, std::string type){
        
        // CHECK IF EMAIL ALREADY EXISTS
        for(int i = 0; i < passengersRef->size(); i++){
            if((*passengersRef)[i].getEmail() == email){
                std::cout << "\nEMAIL ALREADY REGISTERED!" << std::endl;
                return false;
            }
        }

        std::string newID = generatePassengerID();
        Passenger newPassenger(newID, name, email, password, phone, type);
        passengersRef->push_back(newPassenger);

        std::cout << "\nSIGNUP SUCCESSFUL! YOUR PASSENGER ID IS: " << newID << std::endl;
        return true;
    }

    bool loginAdmin(std::string filename, std::string username, std::string password){
        if(FileManager::verifyAdmin(filename, username, password)){
            std::cout << "\nADMIN LOGIN SUCCESSFUL!" << std::endl;
            return true;
        }
        std::cout << "\nINVALID ADMIN CREDENTIALS!" << std::endl;
        return false;
    }
};

#endif