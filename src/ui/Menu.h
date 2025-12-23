#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "../managers/AuthManager.h"
#include "../managers/FlightManager.h"
#include "../managers/BookingManager.h"
#include "../managers/RouteManager.h"

class Menu{
    private:
    AuthManager* authManager;
    FlightManager* flightManager;
    BookingManager* bookingManager;
    RouteManager* routeManager;

    public:
    Menu(AuthManager* auth, FlightManager* flight, BookingManager* booking, RouteManager* route){
        authManager = auth;
        flightManager = flight;
        bookingManager = booking;
        routeManager = route;
    }

    void displayMainMenu(){
        std::cout << "\n";
        std::cout << "=========================================\n";
        std::cout << "    HIGHWAYS AIRLINE MANAGEMENT SYSTEM   \n";
        std::cout << "=========================================\n";
        std::cout << "1. PASSENGER LOGIN\n";
        std::cout << "2. PASSENGER SIGNUP\n";
        std::cout << "3. ADMIN LOGIN\n";
        std::cout << "4. EXIT\n";
        std::cout << "=========================================\n";
        std::cout << "ENTER YOUR CHOICE: ";
    }

    void displayPassengerMenu(){
        std::cout << "\n";
        std::cout << "=========================================\n";
        std::cout << "          PASSENGER MENU                 \n";
        std::cout << "=========================================\n";
        std::cout << "1. SEARCH FLIGHTS\n";
        std::cout << "2. BOOK A FLIGHT\n";
        std::cout << "3. VIEW MY BOOKINGS\n";
        std::cout << "4. CANCEL BOOKING\n";
        std::cout << "5. VIEW AIRPORTS\n";
        std::cout << "6. LOGOUT\n";
        std::cout << "=========================================\n";
        std::cout << "ENTER YOUR CHOICE: ";
    }

    void displayAdminMenu(){
        std::cout << "\n";
        std::cout << "=========================================\n";
        std::cout << "            ADMIN MENU                   \n";
        std::cout << "=========================================\n";
        std::cout << "1. ADD FLIGHT\n";
        std::cout << "2. UPDATE FLIGHT\n";
        std::cout << "3. DELETE FLIGHT\n";
        std::cout << "4. VIEW ALL FLIGHTS\n";
        std::cout << "5. SEARCH FLIGHT BY ID\n";
        std::cout << "6. CHANGE FLIGHT STATUS\n";
        std::cout << "7. VIEW AIRPORT ROUTES\n";
        std::cout << "8. FIND SHORTEST ROUTE\n";
        std::cout << "9. VIEW BOARDING PRIORITY\n";
        std::cout << "10. VIEW WAITLIST\n";
        std::cout << "11. UNDO LAST ACTION\n";
        std::cout << "12. VIEW ACTIVITY LOG\n";
        std::cout << "13. LOGOUT\n";
        std::cout << "=========================================\n";
        std::cout << "ENTER YOUR CHOICE: ";
    }

    int handleMainMenu(){
        int choice;
        std::cin >> choice;
        return choice;
    }

    void handlePassengerLogin(){
        std::string email, password;
        std::cin.ignore();
        std::cout << "\nENTER EMAIL: ";
        std::getline(std::cin, email);
        std::cout << "ENTER PASSWORD: ";
        std::getline(std::cin, password);

        Passenger* loggedInPassenger = authManager->loginPassenger(email, password);
        
        if(loggedInPassenger != nullptr){
            runPassengerMenu(loggedInPassenger);
        }
    }

    void handlePassengerSignup(){
        std::string name, email, password, phone, type;
        int typeChoice;

        std::cin.ignore();
        std::cout << "\nENTER YOUR NAME: ";
        std::getline(std::cin, name);
        std::cout << "ENTER YOUR EMAIL: ";
        std::getline(std::cin, email);
        std::cout << "ENTER PASSWORD: ";
        std::getline(std::cin, password);
        std::cout << "ENTER PHONE NUMBER: ";
        std::getline(std::cin, phone);

        std::cout << "\nSELECT PASSENGER TYPE:\n";
        std::cout << "1. PREMIUM\n";
        std::cout << "2. BUSINESS\n";
        std::cout << "3. ECONOMY PLUS\n";
        std::cout << "4. ECONOMY\n";
        std::cout << "ENTER CHOICE: ";
        std::cin >> typeChoice;

        switch(typeChoice){
            case 1: type = "PREMIUM"; break;
            case 2: type = "BUSINESS"; break;
            case 3: type = "ECONOMY_PLUS"; break;
            case 4: type = "ECONOMY"; break;
            default: type = "ECONOMY"; break;
        }

        authManager->signupPassenger(name, email, password, phone, type);
    }

    void handleAdminLogin(){
        std::string username, password;
        std::cin.ignore();
        std::cout << "\nENTER ADMIN USERNAME: ";
        std::getline(std::cin, username);
        std::cout << "ENTER ADMIN PASSWORD: ";
        std::getline(std::cin, password);

        if(authManager->loginAdmin("../data/admins.txt", username, password)){
            runAdminMenu();
        }
    }

    void runPassengerMenu(Passenger* passenger){
        int choice;
        do{
            displayPassengerMenu();
            std::cin >> choice;

            switch(choice){
                case 1:
                    flightManager->displayAllFlights();
                    break;
                case 2:
                    bookingManager->bookFlight(passenger->getPassengerID());
                    break;
                case 3:
                    bookingManager->viewPassengerBookings(passenger->getPassengerID());
                    break;
                case 4:
                    bookingManager->cancelBooking(passenger->getPassengerID());
                    break;
                case 5:
                    routeManager->viewAirports();
                    break;
                case 6:
                    std::cout << "\nLOGGING OUT..." << std::endl;
                    break;
                default:
                    std::cout << "\nINVALID CHOICE! PLEASE TRY AGAIN." << std::endl;
                    break;
            }
        }while(choice != 6);
    }

    void runAdminMenu(){
        int choice;
        do{
            displayAdminMenu();
            std::cin >> choice;

            switch(choice){
                case 1:
                    flightManager->addFlight();
                    break;
                case 2:
                    flightManager->updateFlight();
                    break;
                case 3:
                    flightManager->deleteFlight();
                    break;
                case 4:
                    flightManager->displayAllFlights();
                    break;
                case 5:
                    flightManager->searchFlightByID();
                    break;
                case 6:
                    flightManager->changeFlightStatus();
                    break;
                case 7:
                    routeManager->showRoutes();
                    break;
                case 8:
                    routeManager->findShortestRoute();
                    break;
                case 9:
                    bookingManager->viewBoardingPriority();
                    break;
                case 10:
                    bookingManager->viewWaitlist();
                    break;
                case 11:
                    flightManager->undoLastAction();
                    break;
                case 12:
                    flightManager->viewActivityLog();
                    break;
                case 13:
                    std::cout << "\nLOGGING OUT..." << std::endl;
                    break;
                default:
                    std::cout << "\nINVALID CHOICE! PLEASE TRY AGAIN." << std::endl;
                    break;
            }
        }while(choice != 13);
    }
};

#endif