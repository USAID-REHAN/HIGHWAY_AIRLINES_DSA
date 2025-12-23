#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>

class Airport{
    private:
    std::string airportCode;
    std::string airportName;
    std::string city;

    public:
    Airport(){
        airportCode = "";
        airportName = "";
        city = "";
    }

    Airport(std::string code, std::string name, std::string c){
        airportCode = code;
        airportName = name;
        city = c;
    }

    // SETTERS
    void setAirportCode(std::string code){ airportCode = code; }
    void setAirportName(std::string name){ airportName = name; }
    void setCity(std::string c){ city = c; }

    // GETTERS
    std::string getAirportCode() const { return airportCode; }
    std::string getAirportName() const { return airportName; }
    std::string getCity() const { return city; }
};

#endif