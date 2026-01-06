#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

using namespace std;

class Passenger {
private:
  string passengerID;
  string name;
  string email;
  string password;
  string phone;
  string passengerType; // PREMIUM, BUSINESS, ECONOMY_PLUS, ECONOMY

public:
  // default constructor for passenger
  Passenger() {
    passengerID = "";
    name = "";
    email = "";
    password = "";
    phone = "";
    passengerType = "ECONOMY";
  }

  // parameterized constructor for passenger
  Passenger(string id, string n, string e, string pass, string ph,
            string type) {
    passengerID = id;
    name = n;
    email = e;
    password = pass;
    phone = ph;
    passengerType = type;
  }

  // sets the passenger id
  void setPassengerID(string id) { passengerID = id; }
  // sets the passenger name
  void setName(string n) { name = n; }
  // sets the passenger email
  void setEmail(string e) { email = e; }
  // sets the passenger password
  void setPassword(string pass) { password = pass; }
  // sets the passenger phone number
  void setPhone(string ph) { phone = ph; }
  // sets the passenger type
  void setPassengerType(string type) { passengerType = type; }

  // returns the passenger id
  string getPassengerID() const { return passengerID; }
  // returns the passenger name
  string getName() const { return name; }
  // returns the passenger email
  string getEmail() const { return email; }
  // returns the passenger password
  string getPassword() const { return password; }
  // returns the passenger phone number
  string getPhone() const { return phone; }
  // returns the passenger type
  string getPassengerType() const { return passengerType; }

  // returns the boarding priority (lower number = higher priority)
  int getPriority() const {
    if (passengerType == "PREMIUM") {
      return 1;
    } else if (passengerType == "BUSINESS") {
      return 2;
    } else if (passengerType == "ECONOMY_PLUS") {
      return 3;
    } else {
      return 4;
    } // ECONOMY
  }
};

#endif