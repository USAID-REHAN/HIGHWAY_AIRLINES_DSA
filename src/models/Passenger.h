#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

class Passenger{
    private:
    std::string passengerID;
    std::string name;
    std::string email;
    std::string password;
    std::string phone;
    std::string passengerType; // PREMIUM, BUSINESS, ECONOMY_PLUS, ECONOMY

    public:
    Passenger(){
        passengerID = "";
        name = "";
        email = "";
        password = "";
        phone = "";
        passengerType = "ECONOMY";
    }

    Passenger(std::string id, std::string n, std::string e, std::string pass, std::string ph, std::string type){
        passengerID = id;
        name = n;
        email = e;
        password = pass;
        phone = ph;
        passengerType = type;
    }

    // SETTERS
    void setPassengerID(std::string id){ passengerID = id; }
    void setName(std::string n){ name = n; }
    void setEmail(std::string e){ email = e; }
    void setPassword(std::string pass){ password = pass; }
    void setPhone(std::string ph){ phone = ph; }
    void setPassengerType(std::string type){ passengerType = type; }

    // GETTERS
    std::string getPassengerID() const { return passengerID; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    std::string getPassword() const { return password; }
    std::string getPhone() const { return phone; }
    std::string getPassengerType() const { return passengerType; }

    // GET PRIORITY FOR BOARDING (LOWER NUMBER = HIGHER PRIORITY)
    int getPriority() const {
        if(passengerType == "PREMIUM"){ return 1; }
        else if(passengerType == "BUSINESS"){ return 2; }
        else if(passengerType == "ECONOMY_PLUS"){ return 3; }
        else{ return 4; } // ECONOMY
    }
};

#endif