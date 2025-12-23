#ifndef ROUTEMANAGER_H
#define ROUTEMANAGER_H

#include <vector>
#include <iostream>
#include <string>
#include "../models/Airport.h"
#include "../ds/Graph.h"

class RouteManager{
    private:
    Graph* airportGraph;
    std::vector<Airport>* airportsRef;

    public:
    RouteManager(std::vector<Airport>* airports){
        airportsRef = airports;
        airportGraph = new Graph(airports->size());
        buildGraph();
    }

    void buildGraph(){
        // ADD AIRPORT CODES TO GRAPH
        for(int i = 0; i < airportsRef->size(); i++){
            airportGraph->addAirportCode((*airportsRef)[i].getAirportCode());
        }

        // ADD EDGES (CONNECTIONS) WITH DISTANCES
        // THESE ARE APPROXIMATE DISTANCES IN KM

        // KHI (0) CONNECTIONS
        airportGraph->addEdge(0, 1, 1000); // KHI -> LHE
        airportGraph->addEdge(0, 2, 1100); // KHI -> ISB

        // LHE (1) CONNECTIONS
        airportGraph->addEdge(1, 2, 300);  // LHE -> ISB
        airportGraph->addEdge(1, 3, 400);  // LHE -> PEW

        // ISB (2) CONNECTIONS
        airportGraph->addEdge(2, 3, 150);  // ISB -> PEW
        airportGraph->addEdge(2, 4, 650);  // ISB -> UET

        // PEW (3) CONNECTIONS
        airportGraph->addEdge(3, 5, 200);  // PEW -> SKT

        // UET (4) CONNECTIONS
        airportGraph->addEdge(4, 5, 750);  // UET -> SKT

        // SKT (5) already connected through above
    }

    void showRoutes(){
        airportGraph->displayGraph();
    }

    void findShortestRoute(){
        std::string startCode, endCode;
        std::cin.ignore();
        std::cout << "\nENTER START AIRPORT CODE: ";
        std::getline(std::cin, startCode);
        std::cout << "ENTER DESTINATION AIRPORT CODE: ";
        std::getline(std::cin, endCode);

        airportGraph->dijkstra(startCode, endCode);
    }

    void viewAirports(){
        std::cout << "\n===== AVAILABLE AIRPORTS =====\n";
        for(int i = 0; i < airportsRef->size(); i++){
            Airport& a = (*airportsRef)[i];
            std::cout << a.getAirportCode() << " - " 
                      << a.getAirportName() << " (" << a.getCity() << ")" << std::endl;
        }
        std::cout << "==============================\n";
    }

    ~RouteManager(){
        delete airportGraph;
    }
};

#endif