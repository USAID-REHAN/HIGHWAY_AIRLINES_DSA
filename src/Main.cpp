#include <iostream>
#include <vector>
#include "models/Passenger.h"
#include "models/Flight.h"
#include "models/Airport.h"
#include "models/Aircraft.h"
#include "models/Booking.h"
#include "managers/FileManager.h"
#include "managers/AuthManager.h"
#include "managers/FlightManager.h"
#include "managers/BookingManager.h"
#include "managers/RouteManager.h"
#include "ui/Menu.h"

int main(){
    // LOAD ALL DATA FROM FILES
    std::vector<Passenger> passengers = FileManager::loadPassengers("../data/passengers.txt");
    std::vector<Flight> flights = FileManager::loadFlights("../data/flights.txt");
    std::vector<Booking> bookings = FileManager::loadBookings("../data/bookings.txt");
    std::vector<Airport> airports = FileManager::loadAirports("../data/airports.txt");
    std::vector<Aircraft> aircrafts = FileManager::loadAircrafts("../data/aircrafts.txt");

    std::cout << "\n=========================================" << std::endl;
    std::cout << "   SYSTEM INITIALIZED SUCCESSFULLY!     " << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "LOADED " << passengers.size() << " PASSENGERS" << std::endl;
    std::cout << "LOADED " << flights.size() << " FLIGHTS" << std::endl;
    std::cout << "LOADED " << bookings.size() << " BOOKINGS" << std::endl;
    std::cout << "LOADED " << airports.size() << " AIRPORTS" << std::endl;
    std::cout << "LOADED " << aircrafts.size() << " AIRCRAFTS" << std::endl;
    std::cout << "=========================================" << std::endl;

    // INITIALIZE MANAGERS
    AuthManager authManager(&passengers);
    FlightManager flightManager(&flights, &aircrafts);
    BookingManager bookingManager(&bookings, &flights, &passengers);
    RouteManager routeManager(&airports);

    // INITIALIZE MENU
    Menu menu(&authManager, &flightManager, &bookingManager, &routeManager);

    // MAIN PROGRAM LOOP
    int choice;
    do{
        menu.displayMainMenu();
        choice = menu.handleMainMenu();

        switch(choice){
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
                std::cout << "\n=========================================" << std::endl;
                std::cout << "   SAVING DATA AND EXITING SYSTEM...    " << std::endl;
                std::cout << "=========================================" << std::endl;
                break;
            default:
                std::cout << "\nINVALID CHOICE! PLEASE TRY AGAIN." << std::endl;
                break;
        }
    }while(choice != 4);

    // SAVE ALL DATA TO FILES
    FileManager::savePassengers("../data/passengers.txt", passengers);
    FileManager::saveFlights("../data/flights.txt", flights);
    FileManager::saveBookings("../data/bookings.txt", bookings);

    std::cout << "\nDATA SAVED SUCCESSFULLY!" << std::endl;
    std::cout << "THANK YOU FOR USING HIGHWAYS AIRLINE SYSTEM!" << std::endl;
    std::cout << "GOODBYE!" << std::endl;

    return 0;
}