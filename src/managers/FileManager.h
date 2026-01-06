#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../models/Aircraft.h"
#include "../models/Airport.h"
#include "../models/Booking.h"
#include "../models/Flight.h"
#include "../models/Passenger.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class FileManager {
private:
  // helper for safe string to int conversion
  static int safeToInt(string str) {
    if (str.empty())
      return 0;
    try {
      return stoi(str);
    } catch (...) {
      return 0;
    }
  }

public:
  // loads passengers from a file
  static vector<Passenger> loadPassengers(string filename) {
    vector<Passenger> passengers;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
      cout << "ERROR: COULD NOT OPEN " << filename << endl;
      return passengers;
    }

    string line;
    while (getline(inFile, line)) {
      if (line.empty())
        continue; // SKIP EMPTY LINES
      stringstream ss(line);
      string id, name, email, password, phone, type;

      getline(ss, id, '|');
      getline(ss, name, '|');
      getline(ss, email, '|');
      getline(ss, password, '|');
      getline(ss, phone, '|');
      getline(ss, type, '|');

      if (!id.empty()) {
        passengers.push_back(Passenger(id, name, email, password, phone, type));
      }
    }

    inFile.close();
    return passengers;
  }

  // saves passengers to a file
  static void savePassengers(string filename, vector<Passenger> &passengers) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
      cout << "ERROR: COULD NOT OPEN " << filename << endl;
      return;
    }

    for (int i = 0; i < passengers.size(); i++) {
      outFile << passengers[i].getPassengerID() << "|"
              << passengers[i].getName() << "|" << passengers[i].getEmail()
              << "|" << passengers[i].getPassword() << "|"
              << passengers[i].getPhone() << "|"
              << passengers[i].getPassengerType();

      if (i < passengers.size() - 1) {
        outFile << endl;
      }
    }

    outFile.close();
  }

  // loads flights from a file
  static vector<Flight> loadFlights(string filename) {
    vector<Flight> flights;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
      cout << "ERROR: COULD NOT OPEN " << filename << endl;
      return flights;
    }

    string line;
    while (getline(inFile, line)) {
      if (line.empty())
        continue;
      stringstream ss(line);
      string id, aircraft, origin, dest, depTime, arrTime, date, cap, booked,
          status;

      getline(ss, id, '|');
      getline(ss, aircraft, '|');
      getline(ss, origin, '|');
      getline(ss, dest, '|');
      getline(ss, depTime, '|');
      getline(ss, arrTime, '|');
      getline(ss, date, '|');
      getline(ss, cap, '|');
      getline(ss, booked, '|');
      getline(ss, status, '|');

      if (!id.empty()) {
        flights.push_back(Flight(id, aircraft, origin, dest, depTime, arrTime,
                                 date, safeToInt(cap), safeToInt(booked),
                                 status));
      }
    }

    inFile.close();
    return flights;
  }

  // saves flights to a file
  static void saveFlights(string filename, vector<Flight> &flights) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
      cout << "ERROR: COULD NOT OPEN " << filename << endl;
      return;
    }

    for (int i = 0; i < flights.size(); i++) {
      outFile << flights[i].getFlightID() << "|" << flights[i].getAircraftID()
              << "|" << flights[i].getOrigin() << "|"
              << flights[i].getDestination() << "|"
              << flights[i].getDepartureTime() << "|"
              << flights[i].getArrivalTime() << "|" << flights[i].getDate()
              << "|" << flights[i].getCapacity() << "|"
              << flights[i].getBookedSeats() << "|" << flights[i].getStatus();

      if (i < flights.size() - 1) {
        outFile << endl;
      }
    }

    outFile.close();
  }

  // loads bookings from a file
  static vector<Booking> loadBookings(string filename) {
    vector<Booking> bookings;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
      cout << "ERROR: COULD NOT OPEN " << filename << endl;
      return bookings;
    }

    string line;
    while (getline(inFile, line)) {
      if (line.empty())
        continue;
      stringstream ss(line);
      string bookingID, passengerID, flightID, seat, status;

      getline(ss, bookingID, '|');
      getline(ss, passengerID, '|');
      getline(ss, flightID, '|');
      getline(ss, seat, '|');
      getline(ss, status, '|');

      if (!bookingID.empty()) {
        bookings.push_back(
            Booking(bookingID, passengerID, flightID, seat, status));
      }
    }

    inFile.close();
    return bookings;
  }

  // saves bookings to a file
  static void saveBookings(string filename, vector<Booking> &bookings) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
      cout << "ERROR: COULD NOT OPEN " << filename << endl;
      return;
    }

    for (int i = 0; i < bookings.size(); i++) {
      outFile << bookings[i].getBookingID() << "|"
              << bookings[i].getPassengerID() << "|"
              << bookings[i].getFlightID() << "|" << bookings[i].getSeatNumber()
              << "|" << bookings[i].getBookingStatus();

      if (i < bookings.size() - 1) {
        outFile << endl;
      }
    }

    outFile.close();
  }

  // loads airports from a file
  static vector<Airport> loadAirports(string filename) {
    vector<Airport> airports;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
      cout << "ERROR: COULD NOT OPEN " << filename << endl;
      return airports;
    }

    string line;
    while (getline(inFile, line)) {
      if (line.empty())
        continue;
      stringstream ss(line);
      string code, name, city;

      getline(ss, code, '|');
      getline(ss, name, '|');
      getline(ss, city, '|');

      if (!code.empty()) {
        airports.push_back(Airport(code, name, city));
      }
    }

    inFile.close();
    return airports;
  }

  // loads aircrafts from a file
  static vector<Aircraft> loadAircrafts(string filename) {
    vector<Aircraft> aircrafts;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
      cout << "ERROR: COULD NOT OPEN " << filename << endl;
      return aircrafts;
    }

    string line;
    while (getline(inFile, line)) {
      if (line.empty())
        continue;
      stringstream ss(line);
      string id, model, cap;

      getline(ss, id, '|');
      getline(ss, model, '|');
      getline(ss, cap, '|');

      if (!id.empty()) {
        aircrafts.push_back(Aircraft(id, model, safeToInt(cap)));
      }
    }

    inFile.close();
    return aircrafts;
  }

  // verifies admin credentials
  static bool verifyAdmin(string filename, string username, string password) {
    ifstream inFile(filename);

    if (!inFile.is_open()) {
      cout << "ERROR: COULD NOT OPEN " << filename << endl;
      return false;
    }

    string line;
    while (getline(inFile, line)) {
      stringstream ss(line);
      string user, pass;

      getline(ss, user, '|');
      getline(ss, pass, '|');

      if (user == username && pass == password) {
        inFile.close();
        return true;
      }
    }

    inFile.close();
    return false;
  }
};

#endif