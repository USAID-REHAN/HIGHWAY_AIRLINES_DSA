#include "managers/AuthManager.h"
#include "managers/BookingManager.h"
#include "managers/FileManager.h"
#include "managers/FlightManager.h"
#include "managers/RouteManager.h"
#include "models/Aircraft.h"
#include "models/Airport.h"
#include "models/Booking.h"
#include "models/Flight.h"
#include "models/Passenger.h"
#include "CLI/Menu.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// main entry point for the airline management system
int main() {
  // LOAD ALL DATA FROM FILES
  vector<Passenger> passengers =
      FileManager::loadPassengers("data/passengers.txt");
  vector<Flight> flights = FileManager::loadFlights("data/flights.txt");
  vector<Booking> bookings = FileManager::loadBookings("data/bookings.txt");
  vector<Airport> airports = FileManager::loadAirports("data/airports.txt");
  vector<Aircraft> aircrafts = FileManager::loadAircrafts("data/aircrafts.txt");

  cout << "\n=========================================" << endl;
  cout << "   SYSTEM INITIALIZED SUCCESSFULLY!     " << endl;
  cout << "=========================================" << endl;
  cout << "LOADED " << passengers.size() << " PASSENGERS" << endl;
  cout << "LOADED " << flights.size() << " FLIGHTS" << endl;
  cout << "LOADED " << bookings.size() << " BOOKINGS" << endl;
  cout << "LOADED " << airports.size() << " AIRPORTS" << endl;
  cout << "LOADED " << aircrafts.size() << " AIRCRAFTS" << endl;
  cout << "=========================================" << endl;

  // INITIALIZE MANAGERS
  AuthManager authManager(&passengers);
  FlightManager flightManager(&flights, &aircrafts);
  BookingManager bookingManager(&bookings, &flights, &passengers);
  RouteManager routeManager(&airports);

  // INITIALIZE MENU
  Menu menu(&authManager, &flightManager, &bookingManager, &routeManager);

  cout << "\nPRESS ANY KEY TO START...";
  cin.get();

  // MAIN PROGRAM LOOP
  int choice;
  do {
    menu.displayMainMenu();
    choice = menu.handleMainMenu();

    switch (choice) {
    case 1:
      menu.handlePassengerLogin();
      break;
    case 2:
      menu.handlePassengerSignup();
      break;
    case 3:
      menu.handleAdminLogin();
      break;
    case 4:
      cout << "\n=========================================" << endl;
      cout << "   SAVING DATA AND EXITING SYSTEM...    " << endl;
      cout << "=========================================" << endl;
      break;
    default:
      cout << "\nINVALID CHOICE! PLEASE TRY AGAIN." << endl;
      cout << "\nPRESS ANY KEY TO CONTINUE...";
      cin.ignore();
      cin.get();
      break;
    }
  } while (choice != 4);

  // SAVE ALL DATA TO FILES
  FileManager::savePassengers("data/passengers.txt", passengers);
  FileManager::saveFlights("data/flights.txt", flights);
  FileManager::saveBookings("data/bookings.txt", bookings);

  cout << "\nDATA SAVED SUCCESSFULLY!" << endl;
  cout << "THANK YOU FOR USING HIGHWAYS AIRLINE SYSTEM!" << endl;
  cout << "GOODBYE!" << endl;

  return 0;
}