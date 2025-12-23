#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H

#include <vector>
#include <iostream>
#include <string>
#include "../models/Flight.h"
#include "../models/Aircraft.h"
#include "../ds/BST.h"
#include "../ds/Stack.h"
#include "../ds/LinkedList.h"

class FlightManager{
    private:
    std::vector<Flight>* flightsRef;
    std::vector<Aircraft>* aircraftsRef;
    BST flightBST;
    Stack undoStack;
    LinkedList activityLog;

    std::string generateFlightID(){
        int maxID = 0;
        for(int i = 0; i < flightsRef->size(); i++){
            std::string id = (*flightsRef)[i].getFlightID();
            if(id.length() > 2){
                int numID = std::stoi(id.substr(2));
                if(numID > maxID){
                    maxID = numID;
                }
            }
        }
        maxID++;
        return "HW" + std::to_string(maxID);
    }

    bool checkConflict(std::string aircraftID, std::string date, std::string depTime){
        // SIMPLE CONFLICT CHECK: SAME AIRCRAFT, SAME DATE, OVERLAPPING TIME
        for(int i = 0; i < flightsRef->size(); i++){
            Flight& f = (*flightsRef)[i];
            if(f.getAircraftID() == aircraftID && 
               f.getDate() == date && 
               f.getDepartureTime() == depTime){
                return true; // CONFLICT FOUND
            }
        }
        return false;
    }

    std::string getCurrentTimestamp(){
        return "[TIME]"; // SIMPLIFIED - IN REAL APP, USE <ctime>
    }

    public:
    FlightManager(std::vector<Flight>* flights, std::vector<Aircraft>* aircrafts){
        flightsRef = flights;
        aircraftsRef = aircrafts;

        // BUILD BST FROM EXISTING FLIGHTS
        for(int i = 0; i < flightsRef->size(); i++){
            flightBST.insert((*flightsRef)[i]);
        }
    }

    void addFlight(){
        std::string aircraftID, origin, dest, depTime, arrTime, date, status;
        int capacity;

        std::cout << "\n===== ADD NEW FLIGHT =====\n";
        
        // SHOW AVAILABLE AIRCRAFT
        std::cout << "AVAILABLE AIRCRAFT:\n";
        for(int i = 0; i < aircraftsRef->size(); i++){
            std::cout << (*aircraftsRef)[i].getAircraftID() << " - " 
                      << (*aircraftsRef)[i].getModel() << " (Capacity: " 
                      << (*aircraftsRef)[i].getCapacity() << ")" << std::endl;
        }

        std::cin.ignore();
        std::cout << "ENTER AIRCRAFT ID: ";
        std::getline(std::cin, aircraftID);

        // FIND AIRCRAFT CAPACITY
        capacity = 0;
        for(int i = 0; i < aircraftsRef->size(); i++){
            if((*aircraftsRef)[i].getAircraftID() == aircraftID){
                capacity = (*aircraftsRef)[i].getCapacity();
                break;
            }
        }

        if(capacity == 0){
            std::cout << "INVALID AIRCRAFT ID!" << std::endl;
            return;
        }

        std::cout << "ENTER ORIGIN (AIRPORT CODE): ";
        std::getline(std::cin, origin);
        std::cout << "ENTER DESTINATION (AIRPORT CODE): ";
        std::getline(std::cin, dest);
        std::cout << "ENTER DEPARTURE TIME (HH:MM): ";
        std::getline(std::cin, depTime);
        std::cout << "ENTER ARRIVAL TIME (HH:MM): ";
        std::getline(std::cin, arrTime);
        std::cout << "ENTER DATE (DD-MM-YYYY): ";
        std::getline(std::cin, date);

        // CHECK CONFLICT
        if(checkConflict(aircraftID, date, depTime)){
            std::cout << "\nCONFLICT DETECTED! AIRCRAFT ALREADY SCHEDULED AT THIS TIME!" << std::endl;
            return;
        }

        std::string newID = generateFlightID();
        Flight newFlight(newID, aircraftID, origin, dest, depTime, arrTime, 
                        date, capacity, 0, "SCHEDULED");

        // PUSH TO UNDO STACK (SAVE CURRENT STATE)
        undoStack.push(newFlight);

        flightsRef->push_back(newFlight);
        flightBST.insert(newFlight);

        activityLog.insertEnd("Added Flight: " + newID, getCurrentTimestamp());

        std::cout << "\nFLIGHT ADDED SUCCESSFULLY! FLIGHT ID: " << newID << std::endl;
    }

    void updateFlight(){
        std::string flightID;
        std::cin.ignore();
        std::cout << "\nENTER FLIGHT ID TO UPDATE: ";
        std::getline(std::cin, flightID);

        Flight* flight = flightBST.search(flightID);
        if(flight == nullptr){
            std::cout << "FLIGHT NOT FOUND!" << std::endl;
            return;
        }

        // SAVE TO UNDO STACK
        undoStack.push(*flight);

        std::cout << "\n===== UPDATE FLIGHT " << flightID << " =====\n";
        std::cout << "1. UPDATE DEPARTURE TIME\n";
        std::cout << "2. UPDATE ARRIVAL TIME\n";
        std::cout << "3. UPDATE DATE\n";
        std::cout << "4. UPDATE STATUS\n";
        std::cout << "ENTER CHOICE: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        std::string newValue;
        switch(choice){
            case 1:
                std::cout << "ENTER NEW DEPARTURE TIME (HH:MM): ";
                std::getline(std::cin, newValue);
                flight->setDepartureTime(newValue);
                break;
            case 2:
                std::cout << "ENTER NEW ARRIVAL TIME (HH:MM): ";
                std::getline(std::cin, newValue);
                flight->setArrivalTime(newValue);
                break;
            case 3:
                std::cout << "ENTER NEW DATE (DD-MM-YYYY): ";
                std::getline(std::cin, newValue);
                flight->setDate(newValue);
                break;
            case 4:
                std::cout << "ENTER NEW STATUS (SCHEDULED/DELAYED/CANCELLED/COMPLETED): ";
                std::getline(std::cin, newValue);
                flight->setStatus(newValue);
                break;
            default:
                std::cout << "INVALID CHOICE!" << std::endl;
                return;
        }

        // UPDATE IN VECTOR
        for(int i = 0; i < flightsRef->size(); i++){
            if((*flightsRef)[i].getFlightID() == flightID){
                (*flightsRef)[i] = *flight;
                break;
            }
        }

        activityLog.insertEnd("Updated Flight: " + flightID, getCurrentTimestamp());
        std::cout << "\nFLIGHT UPDATED SUCCESSFULLY!" << std::endl;
    }

    void deleteFlight(){
        std::string flightID;
        std::cin.ignore();
        std::cout << "\nENTER FLIGHT ID TO DELETE: ";
        std::getline(std::cin, flightID);

        Flight* flight = flightBST.search(flightID);
        if(flight == nullptr){
            std::cout << "FLIGHT NOT FOUND!" << std::endl;
            return;
        }

        // SAVE TO UNDO STACK
        undoStack.push(*flight);

        // DELETE FROM VECTOR
        for(int i = 0; i < flightsRef->size(); i++){
            if((*flightsRef)[i].getFlightID() == flightID){
                flightsRef->erase(flightsRef->begin() + i);
                break;
            }
        }

        activityLog.insertEnd("Deleted Flight: " + flightID, getCurrentTimestamp());
        std::cout << "\nFLIGHT DELETED SUCCESSFULLY!" << std::endl;
    }

    void displayAllFlights(){
        if(flightsRef->empty()){
            std::cout << "\nNO FLIGHTS IN SYSTEM!" << std::endl;
            return;
        }

        std::cout << "\n========== ALL FLIGHTS ==========\n";
        for(int i = 0; i < flightsRef->size(); i++){
            Flight& f = (*flightsRef)[i];
            std::cout << "\nFLIGHT ID: " << f.getFlightID()
                      << "\nAIRCRAFT: " << f.getAircraftID()
                      << "\nROUTE: " << f.getOrigin() << " -> " << f.getDestination()
                      << "\nDEPARTURE: " << f.getDepartureTime() << " | ARRIVAL: " << f.getArrivalTime()
                      << "\nDATE: " << f.getDate()
                      << "\nSEATS: " << f.getBookedSeats() << "/" << f.getCapacity()
                      << "\nSTATUS: " << f.getStatus() << std::endl;
            std::cout << "--------------------------------" << std::endl;
        }
        std::cout << "=================================\n";
    }

    void searchFlightByID(){
        std::string flightID;
        std::cin.ignore();
        std::cout << "\nENTER FLIGHT ID: ";
        std::getline(std::cin, flightID);

        Flight* flight = flightBST.search(flightID);
        if(flight == nullptr){
            std::cout << "FLIGHT NOT FOUND!" << std::endl;
            return;
        }

        std::cout << "\n===== FLIGHT DETAILS =====\n";
        std::cout << "FLIGHT ID: " << flight->getFlightID()
                  << "\nAIRCRAFT: " << flight->getAircraftID()
                  << "\nROUTE: " << flight->getOrigin() << " -> " << flight->getDestination()
                  << "\nDEPARTURE: " << flight->getDepartureTime() 
                  << " | ARRIVAL: " << flight->getArrivalTime()
                  << "\nDATE: " << flight->getDate()
                  << "\nSEATS: " << flight->getBookedSeats() << "/" << flight->getCapacity()
                  << "\nSTATUS: " << flight->getStatus() << std::endl;
        std::cout << "==========================\n";
    }

    void changeFlightStatus(){
        std::string flightID, newStatus;
        std::cin.ignore();
        std::cout << "\nENTER FLIGHT ID: ";
        std::getline(std::cin, flightID);

        Flight* flight = flightBST.search(flightID);
        if(flight == nullptr){
            std::cout << "FLIGHT NOT FOUND!" << std::endl;
            return;
        }

        std::cout << "CURRENT STATUS: " << flight->getStatus() << std::endl;
        std::cout << "ENTER NEW STATUS (SCHEDULED/DELAYED/CANCELLED/COMPLETED): ";
        std::getline(std::cin, newStatus);

        flight->setStatus(newStatus);

        // UPDATE IN VECTOR
        for(int i = 0; i < flightsRef->size(); i++){
            if((*flightsRef)[i].getFlightID() == flightID){
                (*flightsRef)[i].setStatus(newStatus);
                break;
            }
        }

        activityLog.insertEnd("Changed Status of Flight " + flightID + " to " + newStatus, 
                            getCurrentTimestamp());
        std::cout << "\nSTATUS UPDATED SUCCESSFULLY!" << std::endl;
    }

    void undoLastAction(){
        if(undoStack.isEmpty()){
            std::cout << "\nNO ACTIONS TO UNDO!" << std::endl;
            return;
        }

        Flight lastFlight = undoStack.pop();
        std::cout << "\nUNDO: RESTORING FLIGHT " << lastFlight.getFlightID() << std::endl;

        // RESTORE FLIGHT
        bool found = false;
        for(int i = 0; i < flightsRef->size(); i++){
            if((*flightsRef)[i].getFlightID() == lastFlight.getFlightID()){
                (*flightsRef)[i] = lastFlight;
                found = true;
                break;
            }
        }

        if(!found){
            flightsRef->push_back(lastFlight);
        }

        activityLog.insertEnd("Undo Action", getCurrentTimestamp());
        std::cout << "UNDO SUCCESSFUL!" << std::endl;
    }

    void viewActivityLog(){
        activityLog.displayAll();
    }
};

#endif