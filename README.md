# Highways Airline Management System

A comprehensive C++ CLI application for managing airline operations, including passenger bookings, flight scheduling, and route management using various data structures.

## Features

- **Passenger Management**: Signup, login, and profile handling.
- **Flight Management**: Add, update, delete, and search flights with undo functionality.
- **Booking System**: Real-time flight booking with waitlist support and priority boarding based on passenger type.
- **Route Management**: Airport connection graphing with shortest path calculation (Dijkstra's algorithm).
- **Data Persistence**: Automatic loading and saving of system data to text files.
- **Activity Logging**: Detailed logs of system actions and updates.

## Data Structures & Usage

| Data Structure               | Feature             | Description                                                                                                                                                   |
| :--------------------------- | :------------------ | :------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Binary Search Tree (BST)** | Flight Search       | Stores flight objects indexed by `FlightID` to allow O(log N) searching and sorted display of the flight schedule.                                            |
| **Graph**                    | Route Management    | Models airports as vertices and flight paths as weighted edges (distance in KM). Uses Dijkstra's algorithm to find the shortest air route between two cities. |
| **Priority Queue**           | Boarding System     | Manages the passenger boarding sequence. Passengers are prioritized based on their type (Premium > Business > Economy Plus > Economy).                        |
| **Queue**                    | Waitlist Management | Handles overflow when a flight is full. Passengers are added to a First-In-First-Out (FIFO) queue and automatically promoted when a seat becomes available.   |
| **Stack**                    | Undo Functionality  | Stores history of administrative actions (adding/updating/deleting flights), allowing the operator to revert the most recent changes.                         |
| **Linked List**              | Activity Logging    | Records all major system events (logins, bookings, schedule changes) in a chronological, dynamic list for auditing purposes.                                  |
| **STL Vector**               | Data Persistence    | Used as the primary backing storage for all models (Passengers, Flights, Bookings) to facilitate easy file I/O and bulk data operations.                      |

## Project Structure

- `src/`: Source code directory.
  - `ds/`: Custom data structure implementations.
  - `managers/`: Core logic and management classes.
  - `models/`: Data models for system entities.
  - `ui/`: User interface components.
  - `Main.cpp`: Entry point of the application.
- `data/`: Text files for data persistence.

## How to Compile and Run

To run the Highways Airline Management System, follow these steps:

### 1. Prerequisites

Ensure you have a C++ compiler (like `g++`) installed on your system.

### 2. Close Existing Instances

If the program is already running, close it or run the following command in PowerShell to avoid "Permission Denied" errors during compilation:

```powershell
Stop-Process -Name Main -Force
```

### 3. Compile the Project

Open your terminal in the project root directory (`Highway_Airlines_DSA`) and run:

```powershell
g++ Main.cpp -o RunMe.exe -Isrc
```

### 4. Run the Application

After successful compilation, start the program:

```powershell
.\RunMe.exe
```
