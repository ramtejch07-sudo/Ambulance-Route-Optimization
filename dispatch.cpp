/*
 * WEEK 04 — Nearest-Ambulance Dispatch Engine
 * -----------------------------------------------
 * Goal: Given an incident, automatically select the closest AVAILABLE
 * ambulance using Dijkstra distances, and mark it busy.
 *
 * Concepts introduced:
 *   - Dispatch decision algorithm (min-distance search)
 *   - State mutation (ambulance becomes unavailable once dispatched)
 *
 * Compile:  g++ -std=c++17 -O2 -Wall -o week04 week04_dispatch.cpp
 * Run:      ./week04
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
    void addRoad(int u, int v, double w) { adjList[u].push_back({v, w}); adjList[v].push_back({u, w}); }
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
        for (const auto& e : graph.neighbors(u)) {
            if (visited[e.to]) continue;
            double nd = dist[u] + e.weight;
            if (nd < dist[e.to]) { dist[e.to] = nd; prev[e.to] = u; pq.push({nd, e.to}); }
        }
    }
    PathResult result;
    result.totalDistance = dist[destination];
    if (dist[destination] == INF) return result;
    for (int at = destination; at != -1; at = prev[at]) result.path.push_back(at);
    reverse(result.path.begin(), result.path.end());
    return result;
}

struct Ambulance {
    int id;
    string callSign;
    int locationNode;
    bool available;
};

struct Incident {
    int id;
    string description;
    int locationNode;
};

// Searches all available ambulances and returns the index of the nearest
// one (by shortest-path distance) along with its route. Returns -1 if
// no ambulance is available.
struct DispatchDecision {
    int ambulanceIndex = -1;
    PathResult route;
};

DispatchDecision findNearestAvailableAmbulance(const CityGraph& graph,
                                                const vector<Ambulance>& ambulances,
                                                const Incident& incident) {
    DispatchDecision best;
    double bestDist = numeric_limits<double>::infinity();

    for (size_t i = 0; i < ambulances.size(); ++i) {
        if (!ambulances[i].available) continue;
        PathResult r = dijkstraShortestPath(graph, ambulances[i].locationNode, incident.locationNode);
        if (r.path.empty()) continue; // unreachable
        if (r.totalDistance < bestDist) {
            bestDist = r.totalDistance;
            best.ambulanceIndex = static_cast<int>(i);
            best.route = r;
        }
    }
    return best;
}

void printRoute(const CityGraph& graph, const PathResult& r) {
    cout << "    Distance: " << r.totalDistance << " km | Route: ";
    for (size_t i = 0; i < r.path.size(); ++i) {
        cout << graph.getNodeName(r.path[i]);
        if (i + 1 < r.path.size()) cout << " -> ";
    }
    cout << "\n";
}

int main() {
    cout << "Ambulance Route Optimizer - Week 04: Nearest-Ambulance Dispatch\n";

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

    vector<Ambulance> ambulances = {
        {1, "Ambulance-Alpha", 0, true},
        {2, "Ambulance-Bravo", 5, true},
        {3, "Ambulance-Charlie", 4, true}
    };

    vector<Incident> incidents = {
        {101, "Cardiac emergency", 3},
        {102, "Road accident", 1}
    };

    for (const auto& incident : incidents) {
        cout << "\nIncident #" << incident.id << " (" << incident.description
             << ") at " << city.getNodeName(incident.locationNode) << "\n";

        DispatchDecision decision = findNearestAvailableAmbulance(city, ambulances, incident);

        if (decision.ambulanceIndex == -1) {
            cout << "  No ambulance available!\n";
            continue;
        }

        Ambulance& chosen = ambulances[decision.ambulanceIndex];
        cout << "  Dispatching " << chosen.callSign << "\n";
        printRoute(city, decision.route);

        chosen.available = false; // ambulance is now busy
        chosen.locationNode = incident.locationNode; // simulate arrival
    }

    cout << "\nFleet status after dispatch round:\n";
    for (const auto& a : ambulances) {
        cout << "  " << a.callSign << ": " << (a.available ? "AVAILABLE" : "BUSY") << "\n";
    }

    cout << "\nWeek 04 complete: automatic nearest-ambulance dispatch working.\n";
    return 0;
}
