#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>

using namespace std;

class Aircraft {
private:
  string aircraftID;
  string model;
  int capacity;

public:
  // default constructor for aircraft
  Aircraft() {
    aircraftID = "";
    model = "";
    capacity = 0;
  }

  // parameterized constructor for aircraft
  Aircraft(string id, string m, int cap) {
    aircraftID = id;
    model = m;
    capacity = cap;
  }

  // sets the aircraft id
  void setAircraftID(string id) { aircraftID = id; }
  // sets the aircraft model
  void setModel(string m) { model = m; }
  // sets the aircraft capacity
  void setCapacity(int cap) { capacity = cap; }

  // returns the aircraft id
  string getAircraftID() const { return aircraftID; }
  // returns the aircraft model
  string getModel() const { return model; }
  // returns the aircraft capacity
  int getCapacity() const { return capacity; }
};

#endif