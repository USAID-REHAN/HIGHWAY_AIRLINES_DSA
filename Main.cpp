#include "src/CLI/Colors.h"
#include "src/CLI/Menu.h"
#include "src/managers/AuthManager.h"
#include "src/managers/BookingManager.h"
#include "src/managers/FileManager.h"
#include "src/managers/FlightManager.h"
#include "src/managers/RouteManager.h"
#include "src/models/Aircraft.h"
#include "src/models/Airport.h"
#include "src/models/Booking.h"
#include "src/models/Flight.h"
#include "src/models/Passenger.h"
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

  cout << "\n"
       << Colors::BOLD << Colors::BRIGHT_CYAN
       << "   =========================================\n"
       << "   |  SYSTEM INITIALIZED SUCCESSFULLY!    |\n"
       << "   =========================================\n"
       << Colors::RESET;
  cout << Colors::BRIGHT_GREEN << "   [+] LOADED " << passengers.size()
       << " PASSENGERS" << Colors::RESET << endl;
  cout << Colors::BRIGHT_GREEN << "   [+] LOADED " << flights.size()
       << " FLIGHTS" << Colors::RESET << endl;
  cout << Colors::BRIGHT_GREEN << "   [+] LOADED " << bookings.size()
       << " BOOKINGS" << Colors::RESET << endl;
  cout << Colors::BRIGHT_GREEN << "   [+] LOADED " << airports.size()
       << " AIRPORTS" << Colors::RESET << endl;
  cout << Colors::BRIGHT_GREEN << "   [+] LOADED " << aircrafts.size()
       << " AIRCRAFTS" << Colors::RESET << endl;
  cout << Colors::BOLD << Colors::BRIGHT_CYAN
       << "   =========================================\n"
       << Colors::RESET;

  // INITIALIZE MANAGERS
  AuthManager authManager(&passengers);
  FlightManager flightManager(&flights, &aircrafts);
  BookingManager bookingManager(&bookings, &flights, &passengers);
  RouteManager routeManager(&airports);

  // INITIALIZE MENU
  Menu menu(&authManager, &flightManager, &bookingManager, &routeManager);

  cout << Colors::BOLD << Colors::YELLOW << "\n   Press any key to start..."
       << Colors::RESET;
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
      cout << Colors::BOLD << Colors::BRIGHT_YELLOW
           << "\n   =========================================\n"
           << "   |   SAVING DATA AND EXITING SYSTEM   |\n"
           << "   =========================================\n"
           << Colors::RESET;
      break;
    default:
      cout << Colors::BOLD << Colors::BRIGHT_RED
           << "\n   [-] INVALID CHOICE! PLEASE TRY AGAIN." << Colors::RESET
           << endl;
      cout << Colors::BOLD << Colors::YELLOW
           << "   Press any key to continue..." << Colors::RESET;
      cin.ignore();
      cin.get();
      break;
    }
  } while (choice != 4);

  // SAVE ALL DATA TO FILES
  FileManager::savePassengers("data/passengers.txt", passengers);
  FileManager::saveFlights("data/flights.txt", flights);
  FileManager::saveBookings("data/bookings.txt", bookings);

  cout << Colors::BOLD << Colors::BRIGHT_GREEN
       << "\n[+] DATA SAVED SUCCESSFULLY!" << Colors::RESET << endl;
  cout << Colors::BRIGHT_CYAN
       << "   THANK YOU FOR USING HIGHWAYS AIRLINE SYSTEM!" << Colors::RESET
       << endl;
  cout << Colors::BRIGHT_YELLOW << "   GOODBYE!" << Colors::RESET << endl
       << Colors::RESET;

  return 0;
}