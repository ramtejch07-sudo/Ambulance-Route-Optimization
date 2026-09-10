/*
 * WEEK 02 — Shortest Path with Dijkstra's Algorithm
 * ---------------------------------------------------
 * Goal: Given the city graph from Week 01, compute the shortest
 * route (in km) from an ambulance's location to an incident location.
 *
 * Concepts introduced:
 *   - Dijkstra's algorithm using a min-priority-queue
 *   - Path reconstruction via a "previous node" array
 *
 * Compile:  g++ -std=c++17 -O2 -Wall -o week02 week02_dijkstra.cpp
 * Run:      ./week02
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    double weight;
};

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

// Result bundle for a shortest-path query.
struct PathResult {
    double totalDistance;
    vector<int> path; // sequence of node ids from source to destination
};

// Classic Dijkstra using a min-heap (priority_queue with negated compare).
PathResult dijkstraShortestPath(const CityGraph& graph, int source, int destination) {
    const double INF = numeric_limits<double>::infinity();
    int n = graph.size();
    vector<double> dist(n, INF);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    using PDI = pair<double, int>; // (distance, node)
    priority_queue<PDI, vector<PDI>, greater<PDI>> pq;

    dist[source] = 0.0;
    pq.push({0.0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;

        if (u == destination) break; // early exit once destination is finalized

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

    if (dist[destination] == INF) {
        return result; // no path exists, path stays empty
    }

    // Reconstruct path by walking backwards through prev[].
    for (int at = destination; at != -1; at = prev[at]) {
        result.path.push_back(at);
    }
    reverse(result.path.begin(), result.path.end());
    return result;
}

void printPath(const CityGraph& graph, const PathResult& result) {
    if (result.path.empty()) {
        cout << "No route found.\n";
        return;
    }
    cout << "Shortest distance: " << result.totalDistance << " km\n";
    cout << "Route: ";
    for (size_t i = 0; i < result.path.size(); ++i) {
        cout << graph.getNodeName(result.path[i]);
        if (i + 1 < result.path.size()) cout << " -> ";
    }
    cout << "\n";
}

int main() {
    cout << "Ambulance Route Optimizer - Week 02: Dijkstra Shortest Path\n";

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

    cout << "\nScenario: Ambulance at Central Station (0), incident at City Hospital (1)\n";
    PathResult r1 = dijkstraShortestPath(city, 0, 1);
    printPath(city, r1);

    cout << "\nScenario: Ambulance at Old Town (5), incident at Riverside Ave (3)\n";
    PathResult r2 = dijkstraShortestPath(city, 5, 3);
    printPath(city, r2);

    cout << "\nWeek 02 complete: shortest-path routing is operational.\n";
    return 0;
}
