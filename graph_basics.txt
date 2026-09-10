/*
 * WEEK 01 — City Graph Foundations
 * ---------------------------------
 * Goal: Model the city road network as a weighted, undirected graph.
 * This is the foundation every later week builds on.
 *
 * Concepts introduced:
 *   - Adjacency list representation
 *   - Node = intersection / landmark, Edge weight = distance in km
 *   - Basic graph printing utility
 *
 * Compile:  g++ -std=c++17 -O2 -Wall -o week01 week01_graph_basics.cpp
 * Run:      ./week01
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// A single road connection to a neighboring intersection.
struct Edge {
    int to;         // destination node id
    double weight;  // distance in km (used as edge cost)
};

// CityGraph stores the road network as an adjacency list.
class CityGraph {
private:
    int numNodes;
    vector<vector<Edge>> adjList;
    unordered_map<int, string> nodeNames;

public:
    explicit CityGraph(int n) : numNodes(n), adjList(n) {}

    void setNodeName(int id, const string& name) {
        nodeNames[id] = name;
    }

    string getNodeName(int id) const {
        auto it = nodeNames.find(id);
        return (it != nodeNames.end()) ? it->second : ("Node" + to_string(id));
    }

    // Roads are two-way, so we add the edge in both directions.
    void addRoad(int u, int v, double distanceKm) {
        adjList[u].push_back({v, distanceKm});
        adjList[v].push_back({u, distanceKm});
    }

    const vector<Edge>& neighbors(int u) const {
        return adjList[u];
    }

    int size() const { return numNodes; }

    void printGraph() const {
        cout << "\n===== CITY ROAD NETWORK =====\n";
        for (int i = 0; i < numNodes; ++i) {
            cout << "[" << i << "] " << getNodeName(i) << " -> ";
            for (const auto& e : adjList[i]) {
                cout << getNodeName(e.to) << "(" << e.weight << "km) ";
            }
            cout << "\n";
        }
        cout << "==============================\n";
    }
};

int main() {
    cout << "Ambulance Route Optimizer - Week 01: Graph Basics\n";

    // Build a small sample city with 6 intersections/landmarks.
    CityGraph city(6);
    city.setNodeName(0, "Central Station");
    city.setNodeName(1, "City Hospital");
    city.setNodeName(2, "Market Square");
    city.setNodeName(3, "Riverside Ave");
    city.setNodeName(4, "Tech Park");
    city.setNodeName(5, "Old Town");

    // Roads (undirected, weighted by distance in km).
    city.addRoad(0, 1, 3.2);
    city.addRoad(0, 2, 1.5);
    city.addRoad(2, 3, 2.7);
    city.addRoad(3, 1, 4.0);
    city.addRoad(2, 4, 5.1);
    city.addRoad(4, 5, 2.2);
    city.addRoad(5, 1, 6.4);
    city.addRoad(0, 5, 7.8);

    city.printGraph();

    cout << "\nTotal intersections: " << city.size() << "\n";
    cout << "Week 01 complete: graph structure ready for pathfinding.\n";
    return 0;
}
