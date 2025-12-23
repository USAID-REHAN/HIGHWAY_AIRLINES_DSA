#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

class Flight{
    private:
    std::string flightID;
    std::string aircraftID;
    std::string origin;
    std::string destination;
    std::string departureTime; // FORMAT: HH:MM
    std::string arrivalTime;   // FORMAT: HH:MM
    std::string date;          // FORMAT: DD-MM-YYYY
    int capacity;
    int bookedSeats;
    std::string status; // SCHEDULED, DELAYED, CANCELLED, COMPLETED

    public:
    Flight(){
        flightID = "";
        aircraftID = "";
        origin = "";
        destination = "";
        departureTime = "";
        arrivalTime = "";
        date = "";
        capacity = 0;
        bookedSeats = 0;
        status = "SCHEDULED";
    }

    Flight(std::string id, std::string aircraft, std::string orig, std::string dest,
           std::string depTime, std::string arrTime, std::string d, int cap, int booked, std::string stat){
        flightID = id;
        aircraftID = aircraft;
        origin = orig;
        destination = dest;
        departureTime = depTime;
        arrivalTime = arrTime;
        date = d;
        capacity = cap;
        bookedSeats = booked;
        status = stat;
    }

    // SETTERS
    void setFlightID(std::string id){ flightID = id; }
    void setAircraftID(std::string aircraft){ aircraftID = aircraft; }
    void setOrigin(std::string orig){ origin = orig; }
    void setDestination(std::string dest){ destination = dest; }
    void setDepartureTime(std::string depTime){ departureTime = depTime; }
    void setArrivalTime(std::string arrTime){ arrivalTime = arrTime; }
    void setDate(std::string d){ date = d; }
    void setCapacity(int cap){ capacity = cap; }
    void setBookedSeats(int booked){ bookedSeats = booked; }
    void setStatus(std::string stat){ status = stat; }

    // GETTERS
    std::string getFlightID() const { return flightID; }
    std::string getAircraftID() const { return aircraftID; }
    std::string getOrigin() const { return origin; }
    std::string getDestination() const { return destination; }
    std::string getDepartureTime() const { return departureTime; }
    std::string getArrivalTime() const { return arrivalTime; }
    std::string getDate() const { return date; }
    int getCapacity() const { return capacity; }
    int getBookedSeats() const { return bookedSeats; }
    std::string getStatus() const { return status; }

    // UTILITY
    bool isFull() const { return bookedSeats >= capacity; }
    int getAvailableSeats() const { return capacity - bookedSeats; }
};

#endif