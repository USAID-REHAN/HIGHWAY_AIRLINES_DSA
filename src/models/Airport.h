#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>

using namespace std;

class Airport {
private:
  string airportCode;
  string airportName;
  string city;

public:
  // default constructor for airport
  Airport() {
    airportCode = "";
    airportName = "";
    city = "";
  }

  // parameterized constructor for airport
  Airport(string code, string name, string c) {
    airportCode = code;
    airportName = name;
    city = c;
  }

  // sets the airport code
  void setAirportCode(string code) { airportCode = code; }
  // sets the airport name
  void setAirportName(string name) { airportName = name; }
  // sets the city
  void setCity(string c) { city = c; }

  // returns the airport code
  string getAirportCode() const { return airportCode; }
  // returns the airport name
  string getAirportName() const { return airportName; }
  // returns the city
  string getCity() const { return city; }
};

#endif