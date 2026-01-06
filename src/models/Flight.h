#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

using namespace std;

class Flight {
private:
  string flightID;
  string aircraftID;
  string origin;
  string destination;
  string departureTime; // FORMAT: HH:MM
  string arrivalTime;   // FORMAT: HH:MM
  string date;          // FORMAT: DD-MM-YYYY
  int capacity;
  int bookedSeats;
  string status; // SCHEDULED, DELAYED, CANCELLED, COMPLETED

public:
  // default constructor for flight
  Flight() {
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

  // parameterized constructor for flight
  Flight(string id, string aircraft, string orig, string dest, string depTime,
         string arrTime, string d, int cap, int booked, string stat) {
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

  // sets the flight id
  void setFlightID(string id) { flightID = id; }
  // sets the aircraft id
  void setAircraftID(string aircraft) { aircraftID = aircraft; }
  // sets the origin airport
  void setOrigin(string orig) { origin = orig; }
  // sets the destination airport
  void setDestination(string dest) { destination = dest; }
  // sets the departure time
  void setDepartureTime(string depTime) { departureTime = depTime; }
  // sets the arrival time
  void setArrivalTime(string arrTime) { arrivalTime = arrTime; }
  // sets the flight date
  void setDate(string d) { date = d; }
  // sets the total capacity
  void setCapacity(int cap) { capacity = cap; }
  // sets the number of booked seats
  void setBookedSeats(int booked) { bookedSeats = booked; }
  // sets the flight status
  void setStatus(string stat) { status = stat; }

  // returns the flight id
  string getFlightID() const { return flightID; }
  // returns the aircraft id
  string getAircraftID() const { return aircraftID; }
  // returns the origin airport
  string getOrigin() const { return origin; }
  // returns the destination airport
  string getDestination() const { return destination; }
  // returns the departure time
  string getDepartureTime() const { return departureTime; }
  // returns the arrival time
  string getArrivalTime() const { return arrivalTime; }
  // returns the flight date
  string getDate() const { return date; }
  // returns the total capacity
  int getCapacity() const { return capacity; }
  // returns the number of booked seats
  int getBookedSeats() const { return bookedSeats; }
  // returns the flight status
  string getStatus() const { return status; }

  // checks if the flight is full
  bool isFull() const { return bookedSeats >= capacity; }
  // returns the number of available seats
  int getAvailableSeats() const { return capacity - bookedSeats; }
};

#endif