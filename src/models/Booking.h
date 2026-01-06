#ifndef BOOKING_H
#define BOOKING_H

#include <string>

using namespace std;

class Booking {
private:
  string bookingID;
  string passengerID;
  string flightID;
  string seatNumber;
  string bookingStatus; // CONFIRMED, WAITLIST, CANCELLED

public:
  // default constructor for booking
  Booking() {
    bookingID = "";
    passengerID = "";
    flightID = "";
    seatNumber = "";
    bookingStatus = "CONFIRMED";
  }

  // parameterized constructor for booking
  Booking(string bID, string pID, string fID, string seat, string status) {
    bookingID = bID;
    passengerID = pID;
    flightID = fID;
    seatNumber = seat;
    bookingStatus = status;
  }

  // sets the booking id
  void setBookingID(string bID) { bookingID = bID; }
  // sets the passenger id
  void setPassengerID(string pID) { passengerID = pID; }
  // sets the flight id
  void setFlightID(string fID) { flightID = fID; }
  // sets the seat number
  void setSeatNumber(string seat) { seatNumber = seat; }
  // sets the booking status
  void setBookingStatus(string status) { bookingStatus = status; }

  // returns the booking id
  string getBookingID() const { return bookingID; }
  // returns the passenger id
  string getPassengerID() const { return passengerID; }
  // returns the flight id
  string getFlightID() const { return flightID; }
  // returns the seat number
  string getSeatNumber() const { return seatNumber; }
  // returns the booking status
  string getBookingStatus() const { return bookingStatus; }
};

#endif