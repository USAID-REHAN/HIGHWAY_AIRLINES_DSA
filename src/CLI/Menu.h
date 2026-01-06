#ifndef MENU_H
#define MENU_H

#include "../managers/AuthManager.h"
#include "../managers/BookingManager.h"
#include "../managers/FlightManager.h"
#include "../managers/RouteManager.h"
#include "Colors.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Menu {
private:
  AuthManager *authManager;
  FlightManager *flightManager;
  BookingManager *bookingManager;
  RouteManager *routeManager;

  // Helper functions for styled output
  void printHeader(const string &title) {
    cout << Colors::BOLD << Colors::BRIGHT_CYAN;
    cout << "\n";
    cout << "   ==========================================\n";
    cout << "   |";
    int spaces = (41 - title.length()) / 2;
    for (int i = 0; i < spaces; i++)
      cout << " ";
    cout << title;
    for (int i = 0; i < spaces; i++)
      cout << " ";
    if ((41 - title.length()) % 2 != 0)
      cout << " ";
    cout << "|\n";
    cout << "   ==========================================" << Colors::RESET
         << "\n";
  }

  void printSubHeader(const string &title) {
    cout << Colors::BOLD << Colors::BRIGHT_CYAN << "\n   >> " << Colors::BLUE
         << title << Colors::BRIGHT_CYAN << " <<\n"
         << Colors::RESET;
  }

  void printSuccess(const string &msg) {
    cout << Colors::BOLD << Colors::BRIGHT_GREEN << "[+] " << msg
         << Colors::RESET << "\n";
  }

  void printError(const string &msg) {
    cout << Colors::BOLD << Colors::BRIGHT_RED << "[-] " << msg << Colors::RESET
         << "\n";
  }

  void printWarning(const string &msg) {
    cout << Colors::BOLD << Colors::BRIGHT_YELLOW << "[!] " << msg
         << Colors::RESET << "\n";
  }

  void printInfo(const string &msg) {
    cout << Colors::BOLD << Colors::BRIGHT_CYAN << "[*] " << msg
         << Colors::RESET << "\n";
  }

  void printMenuItem(int num, const string &text) {
    cout << "   " << Colors::BOLD << Colors::BRIGHT_CYAN << "["
         << Colors::BRIGHT_GREEN << num << Colors::BRIGHT_CYAN << "] "
         << Colors::WHITE << text << Colors::RESET << "\n";
  }

  // clear terminal screen and reset colors (cross-platform)
  void clearScreen() {
    cout << Colors::RESET;
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
  }

  // pause and wait for user input with proper formatting
  void waitKey() {
    cout << Colors::RESET << Colors::BOLD << Colors::YELLOW
         << "\n   Press any key to continue..." << Colors::RESET << " ";
    cin.ignore();
    cin.get();
    clearScreen();
  }

public:
  // constructor to initialize menu with managers
  Menu(AuthManager *auth, FlightManager *flight, BookingManager *booking,
       RouteManager *route) {
    authManager = auth;
    flightManager = flight;
    bookingManager = booking;
    routeManager = route;
  }

  // displays the main startup menu
  void displayMainMenu() {
    clearScreen();
    printHeader("HIGHWAYS AIRLINE MANAGEMENT SYSTEM");
    cout << Colors::DIM << Colors::WHITE
         << "   Welcome to the flight booking system\n"
         << Colors::RESET;
    cout << "\n";
    printMenuItem(1, "Passenger Login");
    printMenuItem(2, "Passenger Signup");
    printMenuItem(3, "Admin Login");
    printMenuItem(4, "Exit");
    cout << "\n   " << Colors::BOLD << Colors::YELLOW
         << "=> Enter your choice: " << Colors::RESET;
  }

  // displays the menu for registered passengers
  void displayPassengerMenu() {
    printHeader("PASSENGER MENU");
    cout << "\n";
    printMenuItem(1, "Search Flights");
    printMenuItem(2, "Book a Flight");
    printMenuItem(3, "View My Bookings");
    printMenuItem(4, "Cancel Booking");
    printMenuItem(5, "View Airports");
    printMenuItem(6, "Logout");
    cout << "\n   " << Colors::BOLD << Colors::YELLOW
         << "=> Enter your choice: " << Colors::RESET;
  }

  // displays the menu for administrators
  void displayAdminMenu() {
    printHeader("ADMIN MENU");
    cout << "\n";
    printMenuItem(1, "Add Flight");
    printMenuItem(2, "Update Flight");
    printMenuItem(3, "Delete Flight");
    printMenuItem(4, "View All Flights");
    printMenuItem(5, "Search Flight by ID");
    printMenuItem(6, "Change Flight Status");
    printMenuItem(7, "View Airport Routes");
    printMenuItem(8, "Find Shortest Route");
    printMenuItem(9, "View Boarding Priority");
    printMenuItem(10, "View Waitlist");
    printMenuItem(11, "Undo Last Action");
    printMenuItem(12, "View Activity Log");
    printMenuItem(13, "Logout");
    cout << "\n   " << Colors::BOLD << Colors::YELLOW
         << "=> Enter your choice: " << Colors::RESET;
  }

  // handles the main menu choice input
  int handleMainMenu() {
    int choice;
    cin >> choice;
    return choice;
  }

  // processes passenger login credentials
  void handlePassengerLogin() {
    clearScreen();
    string email, password;
    cin.ignore();
    printSubHeader("Passenger Login");
    cout << Colors::BOLD << "   Email: " << Colors::RESET;
    getline(cin, email);
    cout << Colors::BOLD << "   Password: " << Colors::RESET;
    getline(cin, password);

    Passenger *loggedInPassenger = authManager->loginPassenger(email, password);

    if (loggedInPassenger != nullptr) {
      printSuccess("Login successful! Welcome aboard.");
      waitKey();
      runPassengerMenu(loggedInPassenger);
    } else {
      printError("Login failed! Invalid credentials.");
      waitKey();
    }
  }

  // processes passenger signup information
  void handlePassengerSignup() {
    clearScreen();
    string name, email, password, phone, type;
    int typeChoice;

    cin.ignore();
    printSubHeader("Passenger Signup");
    cout << Colors::BOLD << "   Full Name: " << Colors::RESET;
    getline(cin, name);
    cout << Colors::BOLD << "   Email: " << Colors::RESET;
    getline(cin, email);
    cout << Colors::BOLD << "   Password: " << Colors::RESET;
    getline(cin, password);
    cout << Colors::BOLD << "   Phone Number: " << Colors::RESET;
    getline(cin, phone);

    printInfo("Select your passenger type:");
    cout << "\n";
    printMenuItem(1, "Premium");
    printMenuItem(2, "Business");
    printMenuItem(3, "Economy Plus");
    printMenuItem(4, "Economy");
    cout << "\n   " << Colors::BOLD << Colors::YELLOW
         << "=> Enter choice: " << Colors::RESET;
    cin >> typeChoice;

    switch (typeChoice) {
    case 1:
      type = "PREMIUM";
      break;
    case 2:
      type = "BUSINESS";
      break;
    case 3:
      type = "ECONOMY_PLUS";
      break;
    case 4:
      type = "ECONOMY";
      break;
    default:
      type = "ECONOMY";
      break;
    }

    authManager->signupPassenger(name, email, password, phone, type);
    printSuccess("Signup successful! You can now login.");
    waitKey();
  }

  // processes admin login credentials
  void handleAdminLogin() {
    clearScreen();
    string username, password;
    cin.ignore();
    printSubHeader("Admin Login");
    cout << Colors::BOLD << "   Username: " << Colors::RESET;
    getline(cin, username);
    cout << Colors::BOLD << "   Password: " << Colors::RESET;
    getline(cin, password);

    if (authManager->loginAdmin("data/admins.txt", username, password)) {
      printSuccess("Admin login successful! Welcome back.");
      waitKey();
      runAdminMenu();
    } else {
      printError("Admin login failed! Invalid credentials.");
      waitKey();
    }
  }

  // runs the interaction loop for the passenger menu
  void runPassengerMenu(Passenger *passenger) {
    int choice;
    do {
      clearScreen();
      displayPassengerMenu();
      cin >> choice;

      switch (choice) {
      case 1: {
        clearScreen();
        printSubHeader("Search Flights");
        cout << "\n";
        printMenuItem(1, "View all flights");
        printMenuItem(2, "Search by route (departure > destination)");
        cout << "\n   " << Colors::BOLD << Colors::YELLOW
             << "> Enter your choice: " << Colors::RESET;
        int searchChoice;
        cin >> searchChoice;

        if (searchChoice == 1) {
          flightManager->displayAllFlights();
        } else if (searchChoice == 2) {
          flightManager->searchFlightsByRoute();
        } else {
          printError("Invalid choice!");
        }
        waitKey();
        break;
      }
      case 2:
        bookingManager->bookFlight(passenger->getPassengerID());
        waitKey();
        break;
      case 3:
        bookingManager->viewPassengerBookings(passenger->getPassengerID());
        waitKey();
        break;
      case 4:
        bookingManager->cancelBooking(passenger->getPassengerID());
        waitKey();
        break;
      case 5:
        routeManager->viewAirports();
        waitKey();
        break;
      case 6:
        printInfo("Logging out...");
        break;
      default:
        printError("Invalid choice! Please try again.");
        waitKey();
        break;
      }
    } while (choice != 6);
  }

  // runs the interaction loop for the admin menu
  void runAdminMenu() {
    int choice;
    do {
      clearScreen();
      displayAdminMenu();
      cin >> choice;

      switch (choice) {
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
        waitKey();
        break;
      case 5:
        flightManager->searchFlightByID();
        waitKey();
        break;
      case 6:
        flightManager->changeFlightStatus();
        waitKey();
        break;
      case 7:
        routeManager->showRoutes();
        waitKey();
        break;
      case 8:
        routeManager->findShortestRoute();
        waitKey();
        break;
      case 9:
        bookingManager->viewBoardingPriority();
        waitKey();
        break;
      case 10:
        bookingManager->viewWaitlist();
        waitKey();
        break;
      case 11:
        flightManager->undoLastAction();
        waitKey();
        break;
      case 12:
        flightManager->viewActivityLog();
        waitKey();
        break;
      case 13:
        printInfo("Logging out...");
        break;
      default:
        printError("Invalid choice! Please try again.");
        waitKey();
        break;
      }
    } while (choice != 13);
  }
};

#endif