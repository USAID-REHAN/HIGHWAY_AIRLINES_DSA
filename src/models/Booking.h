#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking{
    private:
    std::string bookingID;
    std::string passengerID;
    std::string flightID;
    std::string seatNumber;
    std::string bookingStatus; // CONFIRMED, WAITLIST, CANCELLED

    public:
    Booking(){
        bookingID = "";
        passengerID = "";
        flightID = "";
        seatNumber = "";
        bookingStatus = "CONFIRMED";
    }

    Booking(std::string bID, std::string pID, std::string fID, std::string seat, std::string status){
        bookingID = bID;
        passengerID = pID;
        flightID = fID;
        seatNumber = seat;
        bookingStatus = status;
    }

    // SETTERS
    void setBookingID(std::string bID){ bookingID = bID; }
    void setPassengerID(std::string pID){ passengerID = pID; }
    void setFlightID(std::string fID){ flightID = fID; }
    void setSeatNumber(std::string seat){ seatNumber = seat; }
    void setBookingStatus(std::string status){ bookingStatus = status; }

    // GETTERS
    std::string getBookingID() const { return bookingID; }
    std::string getPassengerID() const { return passengerID; }
    std::string getFlightID() const { return flightID; }
    std::string getSeatNumber() const { return seatNumber; }
    std::string getBookingStatus() const { return bookingStatus; }
};

#endif