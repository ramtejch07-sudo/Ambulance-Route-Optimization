/*
 * WEEK 03 — Ambulance & Hospital Entities
 * ------------------------------------------
 * Goal: Introduce domain entities (Ambulance, Hospital, Incident) on top
 * of the graph + Dijkstra engine from Weeks 01-02.
 *
 * Concepts introduced:
 *   - Structs modeling real-world entities
 *   - Placing entities at graph nodes
 *   - Simple lookup/reporting utilities
 *
 * Compile:  g++ -std=c++17 -O2 -Wall -o week03 week03_entities.cpp
 * Run:      ./week03
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge { int to; double weight; };

class CityGraph {
private:
    int numNodes;
    vector<vector<Edge>> adjList;
    unordered_map<int, string> nodeNames;
public:
    explicit CityGraph(int n) : numNodes(n), adjList(n) {}
    void setNodeName(int id, const string& name) { nodeNames[id] = name; }
    string getNodeName(int id) const {
        auto it = nodeNames.find(id);
        return (it != nodeNames.end()) ? it->second : ("Node" + to_string(id));
    }
    void addRoad(int u, int v, double distanceKm) {
        adjList[u].push_back({v, distanceKm});
        adjList[v].push_back({u, distanceKm});
    }
    const vector<Edge>& neighbors(int u) const { return adjList[u]; }
    int size() const { return numNodes; }
};

struct PathResult { double totalDistance; vector<int> path; };

PathResult dijkstraShortestPath(const CityGraph& graph, int source, int destination) {
    const double INF = numeric_limits<double>::infinity();
    int n = graph.size();
    vector<double> dist(n, INF);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);
    using PDI = pair<double, int>;
    priority_queue<PDI, vector<PDI>, greater<PDI>> pq;
    dist[source] = 0.0;
    pq.push({0.0, source});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        if (u == destination) break;
        for (const auto& edge : graph.neighbors(u)) {
            if (visited[edge.to]) continue;
            double newDist = dist[u] + edge.weight;
            if (newDist < dist[edge.to]) {
                dist[edge.to] = newDist;
                prev[edge.to] = u;
                pq.push({newDist, edge.to});
            }
        }
    }
    PathResult result;
    result.totalDistance = dist[destination];
    if (dist[destination] == INF) return result;
    for (int at = destination; at != -1; at = prev[at]) result.path.push_back(at);
    reverse(result.path.begin(), result.path.end());
    return result;
}

// ---------------- Domain entities ----------------

struct Ambulance {
    int id;
    string callSign;
    int locationNode;   // current node in the graph
    bool available;
};

struct Hospital {
    int id;
    string name;
    int locationNode;
    int emergencyBedsFree;
};

struct Incident {
    int id;
    string description;
    int locationNode;
};

class FleetManager {
private:
    vector<Ambulance> ambulances;
    vector<Hospital> hospitals;

public:
    void addAmbulance(const Ambulance& a) { ambulances.push_back(a); }
    void addHospital(const Hospital& h) { hospitals.push_back(h); }

    vector<Ambulance>& getAmbulances() { return ambulances; }
    vector<Hospital>& getHospitals() { return hospitals; }

    void printFleetStatus(const CityGraph& graph) const {
        cout << "\n----- Ambulance Fleet -----\n";
        for (const auto& a : ambulances) {
            cout << "  [" << a.id << "] " << a.callSign
                 << " | at " << graph.getNodeName(a.locationNode)
                 << " | " << (a.available ? "AVAILABLE" : "BUSY") << "\n";
        }
        cout << "----- Hospitals -----\n";
        for (const auto& h : hospitals) {
            cout << "  [" << h.id << "] " << h.name
                 << " | at " << graph.getNodeName(h.locationNode)
                 << " | free beds: " << h.emergencyBedsFree << "\n";
        }
    }
};

int main() {
    cout << "Ambulance Route Optimizer - Week 03: Entities (Ambulance/Hospital/Incident)\n";

    CityGraph city(6);
    city.setNodeName(0, "Central Station");
    city.setNodeName(1, "City Hospital");
    city.setNodeName(2, "Market Square");
    city.setNodeName(3, "Riverside Ave");
    city.setNodeName(4, "Tech Park");
    city.setNodeName(5, "Old Town");
    city.addRoad(0, 1, 3.2);
    city.addRoad(0, 2, 1.5);
    city.addRoad(2, 3, 2.7);
    city.addRoad(3, 1, 4.0);
    city.addRoad(2, 4, 5.1);
    city.addRoad(4, 5, 2.2);
    city.addRoad(5, 1, 6.4);
    city.addRoad(0, 5, 7.8);

    FleetManager fleet;
    fleet.addAmbulance({1, "Ambulance-Alpha", 0, true});
    fleet.addAmbulance({2, "Ambulance-Bravo", 5, true});
    fleet.addAmbulance({3, "Ambulance-Charlie", 4, false});

    fleet.addHospital({1, "City Hospital", 1, 6});
    fleet.addHospital({2, "Riverside Clinic", 3, 2});

    fleet.printFleetStatus(city);

    Incident incident{101, "Traffic collision", 2}; // at Market Square
    cout << "\nNew Incident #" << incident.id << ": " << incident.description
         << " at " << city.getNodeName(incident.locationNode) << "\n";

    cout << "\nDistance from each available ambulance to the incident:\n";
    for (auto& a : fleet.getAmbulances()) {
        if (!a.available) {
            cout << "  " << a.callSign << " is busy, skipping.\n";
            continue;
        }
        PathResult r = dijkstraShortestPath(city, a.locationNode, incident.locationNode);
        cout << "  " << a.callSign << " -> " << r.totalDistance << " km\n";
    }

    cout << "\nWeek 03 complete: domain model established for dispatch logic.\n";
    return 0;
}
