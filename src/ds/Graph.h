#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>

struct Edge{
    int destination;
    int weight; // DISTANCE IN KM

    Edge(int dest, int w){
        destination = dest;
        weight = w;
    }
};

class Graph{
    private:
    int numVertices;
    std::vector<std::vector<Edge>> adjacencyList;
    std::vector<std::string> airportCodes;

    int findMinDistance(int dist[], bool visited[]){
        int min = std::numeric_limits<int>::max();
        int minIndex = -1;

        for(int v = 0; v < numVertices; v++){
            if(!visited[v] && dist[v] < min){
                min = dist[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    int getAirportIndex(std::string code){
        for(int i = 0; i < numVertices; i++){
            if(airportCodes[i] == code){
                return i;
            }
        }
        return -1;
    }

    public:
    Graph(int vertices){
        numVertices = vertices;
        adjacencyList.resize(numVertices);
    }

    void addAirportCode(std::string code){
        airportCodes.push_back(code);
    }

    void addEdge(int src, int dest, int weight){
        adjacencyList[src].push_back(Edge(dest, weight));
        adjacencyList[dest].push_back(Edge(src, weight)); // UNDIRECTED GRAPH
    }

    void dijkstra(std::string startCode, std::string endCode){
        int start = getAirportIndex(startCode);
        int end = getAirportIndex(endCode);

        if(start == -1 || end == -1){
            std::cout << "INVALID AIRPORT CODE!" << std::endl;
            return;
        }

        int* dist = new int[numVertices];
        bool* visited = new bool[numVertices];
        int* parent = new int[numVertices];

        for(int i = 0; i < numVertices; i++){
            dist[i] = std::numeric_limits<int>::max();
            visited[i] = false;
            parent[i] = -1;
        }

        dist[start] = 0;

        for(int count = 0; count < numVertices - 1; count++){
            int u = findMinDistance(dist, visited);
            
            if(u == -1){
                break;
            }

            visited[u] = true;

            for(int i = 0; i < adjacencyList[u].size(); i++){
                Edge edge = adjacencyList[u][i];
                int v = edge.destination;
                int weight = edge.weight;

                if(!visited[v] && dist[u] != std::numeric_limits<int>::max() 
                   && dist[u] + weight < dist[v]){
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }

        // DISPLAY RESULT
        if(dist[end] == std::numeric_limits<int>::max()){
            std::cout << "\nNO PATH EXISTS BETWEEN " << startCode 
                      << " AND " << endCode << "!" << std::endl;
        }
        else{
            std::cout << "\n========== SHORTEST ROUTE ==========\n";
            std::cout << "FROM: " << startCode << " TO: " << endCode << std::endl;
            std::cout << "DISTANCE: " << dist[end] << " KM\n";
            std::cout << "\nROUTE PATH: ";

            // RECONSTRUCT PATH
            std::vector<int> path;
            int current = end;
            while(current != -1){
                path.push_back(current);
                current = parent[current];
            }

            // PRINT PATH IN REVERSE
            for(int i = path.size() - 1; i >= 0; i--){
                std::cout << airportCodes[path[i]];
                if(i > 0){
                    std::cout << " -> ";
                }
            }
            std::cout << "\n====================================\n";
        }

        delete[] dist;
        delete[] visited;
        delete[] parent;
    }

    void displayGraph(){
        std::cout << "\n========== AIRPORT NETWORK ==========\n";
        for(int i = 0; i < numVertices; i++){
            std::cout << airportCodes[i] << " -> ";
            for(int j = 0; j < adjacencyList[i].size(); j++){
                std::cout << airportCodes[adjacencyList[i][j].destination] 
                          << "(" << adjacencyList[i][j].weight << "km) ";
            }
            std::cout << std::endl;
        }
        std::cout << "=====================================\n";
    }
};

#endif