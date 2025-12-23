#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <sstream>
#include <vector>
#include "../models/Passenger.h"
#include "../models/Flight.h"
#include "../models/Airport.h"
#include "../models/Aircraft.h"
#include "../models/Booking.h"

class FileManager{
    public:
    // LOAD PASSENGERS FROM FILE
    static std::vector<Passenger> loadPassengers(std::string filename){
        std::vector<Passenger> passengers;
        std::ifstream inFile(filename);
        
        if(!inFile.is_open()){
            std::cout << "ERROR: COULD NOT OPEN " << filename << std::endl;
            return passengers;
        }

        std::string line;
        while(std::getline(inFile, line)){
            std::stringstream ss(line);
            std::string id, name, email, password, phone, type;

            std::getline(ss, id, '|');
            std::getline(ss, name, '|');
            std::getline(ss, email, '|');
            std::getline(ss, password, '|');
            std::getline(ss, phone, '|');
            std::getline(ss, type, '|');

            passengers.push_back(Passenger(id, name, email, password, phone, type));
        }

        inFile.close();
        return passengers;
    }

    // SAVE PASSENGERS TO FILE
    static void savePassengers(std::string filename, std::vector<Passenger>& passengers){
        std::ofstream outFile(filename);

        if(!outFile.is_open()){
            std::cout << "ERROR: COULD NOT OPEN " << filename << std::endl;
            return;
        }

        for(int i = 0; i < passengers.size(); i++){
            outFile << passengers[i].getPassengerID() << "|"
                    << passengers[i].getName() << "|"
                    << passengers[i].getEmail() << "|"
                    << passengers[i].getPassword() << "|"
                    << passengers[i].getPhone() << "|"
                    << passengers[i].getPassengerType();
            
            if(i < passengers.size() - 1){
                outFile << std::endl;
            }
        }

        outFile.close();
    }

    // LOAD FLIGHTS FROM FILE
    static std::vector<Flight> loadFlights(std::string filename){
        std::vector<Flight> flights;
        std::ifstream inFile(filename);

        if(!inFile.is_open()){
            std::cout << "ERROR: COULD NOT OPEN " << filename << std::endl;
            return flights;
        }

        std::string line;
        while(std::getline(inFile, line)){
            std::stringstream ss(line);
            std::string id, aircraft, origin, dest, depTime, arrTime, date, cap, booked, status;

            std::getline(ss, id, '|');
            std::getline(ss, aircraft, '|');
            std::getline(ss, origin, '|');
            std::getline(ss, dest, '|');
            std::getline(ss, depTime, '|');
            std::getline(ss, arrTime, '|');
            std::getline(ss, date, '|');
            std::getline(ss, cap, '|');
            std::getline(ss, booked, '|');
            std::getline(ss, status, '|');

            flights.push_back(Flight(id, aircraft, origin, dest, depTime, arrTime, 
                                   date, std::stoi(cap), std::stoi(booked), status));
        }

        inFile.close();
        return flights;
    }

    // SAVE FLIGHTS TO FILE
    static void saveFlights(std::string filename, std::vector<Flight>& flights){
        std::ofstream outFile(filename);

        if(!outFile.is_open()){
            std::cout << "ERROR: COULD NOT OPEN " << filename << std::endl;
            return;
        }

        for(int i = 0; i < flights.size(); i++){
            outFile << flights[i].getFlightID() << "|"
                    << flights[i].getAircraftID() << "|"
                    << flights[i].getOrigin() << "|"
                    << flights[i].getDestination() << "|"
                    << flights[i].getDepartureTime() << "|"
                    << flights[i].getArrivalTime() << "|"
                    << flights[i].getDate() << "|"
                    << flights[i].getCapacity() << "|"
                    << flights[i].getBookedSeats() << "|"
                    << flights[i].getStatus();

            if(i < flights.size() - 1){
                outFile << std::endl;
            }
        }

        outFile.close();
    }

    // LOAD BOOKINGS FROM FILE
    static std::vector<Booking> loadBookings(std::string filename){
        std::vector<Booking> bookings;
        std::ifstream inFile(filename);

        if(!inFile.is_open()){
            std::cout << "ERROR: COULD NOT OPEN " << filename << std::endl;
            return bookings;
        }

        std::string line;
        while(std::getline(inFile, line)){
            std::stringstream ss(line);
            std::string bookingID, passengerID, flightID, seat, status;

            std::getline(ss, bookingID, '|');
            std::getline(ss, passengerID, '|');
            std::getline(ss, flightID, '|');
            std::getline(ss, seat, '|');
            std::getline(ss, status, '|');

            bookings.push_back(Booking(bookingID, passengerID, flightID, seat, status));
        }

        inFile.close();
        return bookings;
    }

    // SAVE BOOKINGS TO FILE
    static void saveBookings(std::string filename, std::vector<Booking>& bookings){
        std::ofstream outFile(filename);

        if(!outFile.is_open()){
            std::cout << "ERROR: COULD NOT OPEN " << filename << std::endl;
            return;
        }

        for(int i = 0; i < bookings.size(); i++){
            outFile << bookings[i].getBookingID() << "|"
                    << bookings[i].getPassengerID() << "|"
                    << bookings[i].getFlightID() << "|"
                    << bookings[i].getSeatNumber() << "|"
                    << bookings[i].getBookingStatus();

            if(i < bookings.size() - 1){
                outFile << std::endl;
            }
        }

        outFile.close();
    }

    // LOAD AIRPORTS FROM FILE
    static std::vector<Airport> loadAirports(std::string filename){
        std::vector<Airport> airports;
        std::ifstream inFile(filename);

        if(!inFile.is_open()){
            std::cout << "ERROR: COULD NOT OPEN " << filename << std::endl;
            return airports;
        }

        std::string line;
        while(std::getline(inFile, line)){
            std::stringstream ss(line);
            std::string code, name, city;

            std::getline(ss, code, '|');
            std::getline(ss, name, '|');
            std::getline(ss, city, '|');

            airports.push_back(Airport(code, name, city));
        }

        inFile.close();
        return airports;
    }

    // LOAD AIRCRAFTS FROM FILE
    static std::vector<Aircraft> loadAircrafts(std::string filename){
        std::vector<Aircraft> aircrafts;
        std::ifstream inFile(filename);

        if(!inFile.is_open()){
            std::cout << "ERROR: COULD NOT OPEN " << filename << std::endl;
            return aircrafts;
        }

        std::string line;
        while(std::getline(inFile, line)){
            std::stringstream ss(line);
            std::string id, model, cap;

            std::getline(ss, id, '|');
            std::getline(ss, model, '|');
            std::getline(ss, cap, '|');

            aircrafts.push_back(Aircraft(id, model, std::stoi(cap)));
        }

        inFile.close();
        return aircrafts;
    }

    // LOAD ADMIN CREDENTIALS
    static bool verifyAdmin(std::string filename, std::string username, std::string password){
        std::ifstream inFile(filename);

        if(!inFile.is_open()){
            std::cout << "ERROR: COULD NOT OPEN " << filename << std::endl;
            return false;
        }

        std::string line;
        while(std::getline(inFile, line)){
            std::stringstream ss(line);
            std::string user, pass;

            std::getline(ss, user, '|');
            std::getline(ss, pass, '|');

            if(user == username && pass == password){
                inFile.close();
                return true;
            }
        }

        inFile.close();
        return false;
    }
};

#endif