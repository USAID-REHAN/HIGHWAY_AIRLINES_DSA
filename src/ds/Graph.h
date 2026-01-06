#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Edge {
  int destination;
  int weight; // DISTANCE IN KM

  // constructor for edge
  Edge(int dest, int w) {
    destination = dest;
    weight = w;
  }
};

class Graph {
private:
  int numVertices;
  vector<vector<Edge>> adjacencyList;
  vector<string> airportCodes;

  // finds the vertex with minimum distance value
  int findMinDistance(int dist[], bool visited[]) {
    int min = numeric_limits<int>::max();
    int minIndex = -1;

    for (int v = 0; v < numVertices; v++) {
      if (!visited[v] && dist[v] < min) {
        min = dist[v];
        minIndex = v;
      }
    }
    return minIndex;
  }

  // returns index of airport code
  int getAirportIndex(string code) {
    for (int i = 0; i < numVertices; i++) {
      if (airportCodes[i] == code) {
        return i;
      }
    }
    return -1;
  }

public:
  // constructor for graph
  Graph(int vertices) {
    numVertices = vertices;
    adjacencyList.resize(numVertices);
  }

  // adds an airport code to the list
  void addAirportCode(string code) { airportCodes.push_back(code); }

  // adds an undirected edge between airports
  void addEdge(int src, int dest, int weight) {
    adjacencyList[src].push_back(Edge(dest, weight));
    adjacencyList[dest].push_back(Edge(src, weight)); // UNDIRECTED GRAPH
  }

  // finds shortest path between two airports using dijkstra
  void dijkstra(string startCode, string endCode) {
    int start = getAirportIndex(startCode);
    int end = getAirportIndex(endCode);

    if (start == -1 || end == -1) {
      cout << "INVALID AIRPORT CODE!" << endl;
      return;
    }

    int *dist = new int[numVertices];
    bool *visited = new bool[numVertices];
    int *parent = new int[numVertices];

    for (int i = 0; i < numVertices; i++) {
      dist[i] = numeric_limits<int>::max();
      visited[i] = false;
      parent[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
      int u = findMinDistance(dist, visited);

      if (u == -1) {
        break;
      }

      visited[u] = true;

      for (int i = 0; i < adjacencyList[u].size(); i++) {
        Edge edge = adjacencyList[u][i];
        int v = edge.destination;
        int weight = edge.weight;

        if (!visited[v] && dist[u] != numeric_limits<int>::max() &&
            dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
          parent[v] = u;
        }
      }
    }

    // DISPLAY RESULT
    if (dist[end] == numeric_limits<int>::max()) {
      cout << "\n   [-] NO PATH EXISTS BETWEEN " << startCode << " AND "
           << endCode << "!" << endl;
    } else {
      cout << "\n========== SHORTEST ROUTE ==========\n";
      cout << "   From: " << startCode << " > To: " << endCode << endl;
      cout << "   Distance: " << dist[end] << " KM\n";
      cout << "\n   Route Path: ";

      // RECONSTRUCT PATH
      vector<int> path;
      int current = end;
      while (current != -1) {
        path.push_back(current);
        current = parent[current];
      }

      // PRINT PATH IN REVERSE
      for (int i = path.size() - 1; i >= 0; i--) {
        cout << airportCodes[path[i]];
        if (i > 0) {
          cout << " > ";
        }
      }
      cout << "\n====================================\n";
    }

    delete[] dist;
    delete[] visited;
    delete[] parent;
  }

  // displays all connections in the graph
  void displayGraph() {
    cout << "\n========== AIRPORT NETWORK ==========\n";
    for (int i = 0; i < numVertices; i++) {
      cout << "   " << airportCodes[i] << " > ";
      for (int j = 0; j < adjacencyList[i].size(); j++) {
        cout << airportCodes[adjacencyList[i][j].destination] << "("
             << adjacencyList[i][j].weight << "km) ";
      }
      cout << endl;
    }
    cout << "====================================\n";
  }
};

#endif