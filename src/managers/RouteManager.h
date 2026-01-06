#ifndef ROUTEMANAGER_H
#define ROUTEMANAGER_H

#include "../CLI/Colors.h"
#include "../ds/Graph.h"
#include "../models/Airport.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RouteManager {
private:
  Graph *airportGraph;
  vector<Airport> *airportsRef;

public:
  // constructor for route manager
  RouteManager(vector<Airport> *airports) {
    airportsRef = airports;
    airportGraph = new Graph(airports->size());
    buildGraph();
  }

  // builds the airport connection graph
  void buildGraph() {
    // ADD AIRPORT CODES TO GRAPH
    for (int i = 0; i < airportsRef->size(); i++) {
      airportGraph->addAirportCode((*airportsRef)[i].getAirportCode());
    }

    // ADD EDGES (CONNECTIONS) WITH DISTANCES
    // THESE ARE APPROXIMATE DISTANCES IN KM

    // KHI (0) CONNECTIONS
    airportGraph->addEdge(0, 1, 1000); // KHI -> LHE
    airportGraph->addEdge(0, 2, 1100); // KHI -> ISB

    // LHE (1) CONNECTIONS
    airportGraph->addEdge(1, 2, 300); // LHE -> ISB
    airportGraph->addEdge(1, 3, 400); // LHE -> PEW

    // ISB (2) CONNECTIONS
    airportGraph->addEdge(2, 3, 150); // ISB -> PEW
    airportGraph->addEdge(2, 4, 650); // ISB -> UET

    // PEW (3) CONNECTIONS
    airportGraph->addEdge(3, 5, 200); // PEW -> SKT

    // UET (4) CONNECTIONS
    airportGraph->addEdge(4, 5, 750); // UET -> SKT

    // SKT (5) already connected through above
  }

  // displays all available routes
  void showRoutes() { airportGraph->displayGraph(); }

  // finds the shortest route between two airports
  void findShortestRoute() {
    string startCode, endCode;
    cin.ignore();
    cout << Colors::BOLD << "\nENTER START AIRPORT CODE: " << Colors::RESET;
    getline(cin, startCode);
    cout << Colors::BOLD << "ENTER DESTINATION AIRPORT CODE: " << Colors::RESET;
    getline(cin, endCode);

    airportGraph->dijkstra(startCode, endCode);
  }

  // displays all registered airports
  void viewAirports() {
    cout << Colors::BOLD << Colors::BRIGHT_CYAN
         << "\n========== AVAILABLE AIRPORTS ==========\n"
         << Colors::RESET;
    for (int i = 0; i < airportsRef->size(); i++) {
      Airport &a = (*airportsRef)[i];
      cout << "   [" << (i + 1) << "] " << a.getAirportCode() << " - "
           << a.getAirportName() << " (" << a.getCity() << ")" << endl;
    }
    cout << Colors::BOLD << Colors::BRIGHT_CYAN
         << "========================================\n"
         << Colors::RESET;
  }

  // destructor to free resources
  ~RouteManager() { delete airportGraph; }
};

#endif