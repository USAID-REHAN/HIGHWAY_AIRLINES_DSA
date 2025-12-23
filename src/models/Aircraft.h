#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>

class Aircraft{
    private:
    std::string aircraftID;
    std::string model;
    int capacity;

    public:
    Aircraft(){
        aircraftID = "";
        model = "";
        capacity = 0;
    }

    Aircraft(std::string id, std::string m, int cap){
        aircraftID = id;
        model = m;
        capacity = cap;
    }

    // SETTERS
    void setAircraftID(std::string id){ aircraftID = id; }
    void setModel(std::string m){ model = m; }
    void setCapacity(int cap){ capacity = cap; }

    // GETTERS
    std::string getAircraftID() const { return aircraftID; }
    std::string getModel() const { return model; }
    int getCapacity() const { return capacity; }
};

#endif