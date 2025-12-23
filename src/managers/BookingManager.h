#ifndef BOOKINGMANAGER_H
#define BOOKINGMANAGER_H

#include <vector>
#include <iostream>
#include <string>
#include "../models/Booking.h"
#include "../models/Flight.h"
#include "../models/Passenger.h"
#include "../ds/Queue.h"
#include "../ds/PriorityQueue.h"

class BookingManager{
    private:
    std::vector<Booking>* bookingsRef;
    std::vector<Flight>* flightsRef;
    std::vector<Passenger>* passengersRef;
    Queue waitlistQueue;
    PriorityQueue boardingQueue;

    std::string generateBookingID(){
        int maxID = 0;
        for(int i = 0; i < bookingsRef->size(); i++){
            std::string id = (*bookingsRef)[i].getBookingID();
            if(id.length() > 1){
                int numID = std::stoi(id.substr(1));
                if(numID > maxID){
                    maxID = numID;
                }
            }
        }
        maxID++;
        return "B" + std::to_string(maxID);
    }

    std::string generateSeatNumber(int seatNum){
        char row = 'A' + (seatNum / 6);
        int col = (seatNum % 6) + 1;
        return std::string(1, row) + std::to_string(col);
    }

    Flight* findFlight(std::string flightID){
        for(int i = 0; i < flightsRef->size(); i++){
            if((*flightsRef)[i].getFlightID() == flightID){
                return &(*flightsRef)[i];
            }
        }
        return nullptr;
    }

    Passenger* findPassenger(std::string passengerID){
        for(int i = 0; i < passengersRef->size(); i++){
            if((*passengersRef)[i].getPassengerID() == passengerID){
                return &(*passengersRef)[i];
            }
        }
        return nullptr;
    }

    public:
    BookingManager(std::vector<Booking>* bookings, std::vector<Flight>* flights, 
                   std::vector<Passenger>* passengers){
        bookingsRef = bookings;
        flightsRef = flights;
        passengersRef = passengers;
    }

    void bookFlight(std::string passengerID){
        std::string flightID;
        std::cin.ignore();
        std::cout << "\nENTER FLIGHT ID TO BOOK: ";
        std::getline(std::cin, flightID);

        Flight* flight = findFlight(flightID);
        if(flight == nullptr){
            std::cout << "FLIGHT NOT FOUND!" << std::endl;
            return;
        }

        // CHECK IF ALREADY BOOKED
        for(int i = 0; i < bookingsRef->size(); i++){
            if((*bookingsRef)[i].getPassengerID() == passengerID && 
               (*bookingsRef)[i].getFlightID() == flightID &&
               (*bookingsRef)[i].getBookingStatus() != "CANCELLED"){
                std::cout << "\nYOU HAVE ALREADY BOOKED THIS FLIGHT!" << std::endl;
                return;
            }
        }

        std::string bookingID = generateBookingID();

        if(flight->isFull()){
            // ADD TO WAITLIST
            waitlistQueue.enqueue(passengerID, flightID);
            Booking newBooking(bookingID, passengerID, flightID, "WAITLIST", "WAITLIST");
            bookingsRef->push_back(newBooking);
            std::cout << "\nFLIGHT IS FULL! ADDED TO WAITLIST." << std::endl;
            std::cout << "BOOKING ID: " << bookingID << std::endl;
        }
        else{
            // CONFIRM BOOKING
            std::string seatNumber = generateSeatNumber(flight->getBookedSeats());
            Booking newBooking(bookingID, passengerID, flightID, seatNumber, "CONFIRMED");
            bookingsRef->push_back(newBooking);

            flight->setBookedSeats(flight->getBookedSeats() + 1);

            // UPDATE FLIGHT IN VECTOR
            for(int i = 0; i < flightsRef->size(); i++){
                if((*flightsRef)[i].getFlightID() == flightID){
                    (*flightsRef)[i].setBookedSeats(flight->getBookedSeats());
                    break;
                }
            }

            // ADD TO BOARDING PRIORITY QUEUE
            Passenger* passenger = findPassenger(passengerID);
            if(passenger != nullptr){
                boardingQueue.insert(*passenger);
            }

            std::cout << "\nBOOKING CONFIRMED!" << std::endl;
            std::cout << "BOOKING ID: " << bookingID << std::endl;
            std::cout << "SEAT NUMBER: " << seatNumber << std::endl;
        }
    }

    void cancelBooking(std::string passengerID){
        std::string bookingID;
        std::cin.ignore();
        std::cout << "\nENTER BOOKING ID TO CANCEL: ";
        std::getline(std::cin, bookingID);

        Booking* booking = nullptr;
        int bookingIndex = -1;

        for(int i = 0; i < bookingsRef->size(); i++){
            if((*bookingsRef)[i].getBookingID() == bookingID && 
               (*bookingsRef)[i].getPassengerID() == passengerID){
                booking = &(*bookingsRef)[i];
                bookingIndex = i;
                break;
            }
        }

        if(booking == nullptr){
            std::cout << "BOOKING NOT FOUND!" << std::endl;
            return;
        }

        if(booking->getBookingStatus() == "CANCELLED"){
            std::cout << "BOOKING ALREADY CANCELLED!" << std::endl;
            return;
        }

        std::string flightID = booking->getFlightID();
        booking->setBookingStatus("CANCELLED");

        Flight* flight = findFlight(flightID);
        if(flight != nullptr && booking->getBookingStatus() != "WAITLIST"){
            flight->setBookedSeats(flight->getBookedSeats() - 1);

            // UPDATE FLIGHT IN VECTOR
            for(int i = 0; i < flightsRef->size(); i++){
                if((*flightsRef)[i].getFlightID() == flightID){
                    (*flightsRef)[i].setBookedSeats(flight->getBookedSeats());
                    break;
                }
            }

            // CHECK WAITLIST AND PROMOTE
            QueueNode* waitlistPassenger = waitlistQueue.peek();
            if(waitlistPassenger != nullptr && waitlistPassenger->flightID == flightID){
                waitlistQueue.dequeue();

                // FIND WAITLIST BOOKING AND CONFIRM IT
                for(int i = 0; i < bookingsRef->size(); i++){
                    if((*bookingsRef)[i].getPassengerID() == waitlistPassenger->passengerID && 
                       (*bookingsRef)[i].getFlightID() == flightID &&
                       (*bookingsRef)[i].getBookingStatus() == "WAITLIST"){
                        
                        std::string seatNumber = generateSeatNumber(flight->getBookedSeats());
                        (*bookingsRef)[i].setSeatNumber(seatNumber);
                        (*bookingsRef)[i].setBookingStatus("CONFIRMED");

                        flight->setBookedSeats(flight->getBookedSeats() + 1);

                        // UPDATE FLIGHT IN VECTOR
                        for(int j = 0; j < flightsRef->size(); j++){
                            if((*flightsRef)[j].getFlightID() == flightID){
                                (*flightsRef)[j].setBookedSeats(flight->getBookedSeats());
                                break;
                            }
                        }

                        std::cout << "\nWAITLIST PASSENGER " << waitlistPassenger->passengerID 
                                  << " PROMOTED TO CONFIRMED!" << std::endl;
                        break;
                    }
                }
                delete waitlistPassenger;
            }
        }

        std::cout << "\nBOOKING CANCELLED SUCCESSFULLY!" << std::endl;
    }

    void viewPassengerBookings(std::string passengerID){
        bool found = false;

        std::cout << "\n===== YOUR BOOKINGS =====\n";
        for(int i = 0; i < bookingsRef->size(); i++){
            if((*bookingsRef)[i].getPassengerID() == passengerID){
                Booking& b = (*bookingsRef)[i];
                std::cout << "\nBOOKING ID: " << b.getBookingID()
                          << "\nFLIGHT ID: " << b.getFlightID()
                          << "\nSEAT: " << b.getSeatNumber()
                          << "\nSTATUS: " << b.getBookingStatus() << std::endl;
                std::cout << "-------------------------" << std::endl;
                found = true;
            }
        }

        if(!found){
            std::cout << "NO BOOKINGS FOUND!" << std::endl;
        }
        std::cout << "=========================\n";
    }

    void viewWaitlist(){
        std::string flightID;
        std::cin.ignore();
        std::cout << "\nENTER FLIGHT ID: ";
        std::getline(std::cin, flightID);

        waitlistQueue.display(flightID);
    }

    void viewBoardingPriority(){
        boardingQueue.displayBoardingOrder();
    }
};

#endif