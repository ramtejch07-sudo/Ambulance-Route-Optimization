# 🚑 Ambulance Route Optimizer

A C++-based **Ambulance Route Optimizer** that finds the shortest and fastest route for an ambulance from its current location to a hospital. The project uses **graph algorithms** to model roads and intersections and optimize emergency response routes.

## 📌 Overview

In emergency situations, reaching the hospital as quickly as possible is critical. This project represents a road network as a weighted graph, where:

* **Vertices (nodes)** represent locations or intersections.
* **Edges** represent roads connecting locations.
* **Edge weights** represent travel distance or estimated travel time.

The application calculates an optimized route from the ambulance's starting location to the selected hospital.

## ✨ Features

* 🚑 Find the shortest route for an ambulance.
* 🏥 Route the ambulance to a specified hospital.
* 🗺️ Represent roads using a weighted graph.
* ⚡ Efficient route calculation using **Dijkstra's Algorithm**.
* 📍 Display the optimized path.
* 📏 Calculate the total distance/cost of the route.
* 💻 Simple command-line interface.
* 🔧 Easily extendable to support traffic and multiple ambulances.

## 🛠️ Technologies Used

* **Language:** C++
* **Data Structures:** Graph, Adjacency List, Priority Queue
* **Algorithm:** Dijkstra's Shortest Path Algorithm
* **Compiler:** GCC / G++ supporting C++17 or later

## 📂 Project Structure

```text
Ambulance-Route-Optimizer/
│
├── main.cpp              # Main program
├── Graph.h               # Graph declaration
├── Graph.cpp             # Graph implementation
├── Dijkstra.h            # Route optimization logic
├── Dijkstra.cpp          # Dijkstra implementation
├── README.md             # Project documentation
└── input.txt             # Optional road network input
```

## 🧠 How It Works

The road network is modeled as a weighted graph.

For example:

```text
        4
   A -------- B
   |          |
  2|          |3
   |          |
   C -------- D
        1
```

If the ambulance starts at `A` and the hospital is at `D`, the algorithm evaluates the available routes and selects the route with the minimum total cost.

### Algorithm

**Dijkstra's Algorithm** is used to find the shortest path:

1. Store all locations as graph nodes.
2. Store roads and their weights as graph edges.
3. Set the ambulance's starting location as the source.
4. Assign an initial distance of infinity to all other nodes.
5. Use a priority queue to process the closest unvisited node.
6. Update the shortest distances to neighboring nodes.
7. Continue until the hospital is reached.
8. Reconstruct and display the optimized route.

## 🚀 Installation

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/ambulance-route-optimizer.git
cd ambulance-route-optimizer
```

### 2. Compile the Project

Using `g++`:

```bash
g++ -std=c++17 main.cpp Graph.cpp Dijkstra.cpp -o ambulance_optimizer
```

### 3. Run

```bash
./ambulance_optimizer
```

On Windows:

```bash
ambulance_optimizer.exe
```

## ▶️ Example

### Input

```text
Enter number of locations: 5

Enter roads:
A B 4
A C 2
C D 1
B D 3
D E 2

Enter ambulance location: A
Enter hospital location: E
```

### Output

```text
Optimized Ambulance Route:
A -> C -> D -> E

Total Distance/Cost: 5
```

## 📊 Complexity

For a graph represented using an adjacency list and a priority queue, Dijkstra's algorithm has a time complexity of approximately:

```text
O((V + E) log V)
```

Where:

* `V` = number of locations/intersections
* `E` = number of roads

The space complexity is:

```text
O(V + E)
```

## 🔮 Future Improvements

The project can be extended with:

* 🚦 Real-time traffic information.
* 🛣️ Road closures and blocked routes.
* ⏱️ Estimated travel time instead of only distance.
* 🚑 Multiple ambulance management.
* 🏥 Selection of the nearest available hospital.
* 📍 GPS/map integration.
* 🔄 Dynamic route recalculation.
* 🚨 Emergency vehicle priority at intersections.
* 📊 Graphical user interface.
* 🌐 Real-time map and traffic API integration.

## 🎯 Applications

This project can be used as a foundation for:

* Emergency response systems
* Ambulance dispatch systems
* Smart-city transportation systems
* Hospital emergency management
* Route optimization research
* Data Structures and Algorithms projects

## 👨‍💻 Learning Outcomes

By completing this project, you can gain practical experience with:

* Graph data structures
* Shortest-path algorithms
* Dijkstra's algorithm
* Priority queues
* C++ STL
* File handling
* Algorithmic problem solving
* Path reconstruction

## 🤝 Contributing

Contributions are welcome!

1. Fork the repository.
2. Create a new branch.
3. Make your changes.
4. Commit your changes.
5. Push the branch.
6. Create a Pull Request.

## 📄 License

This project is intended for educational and research purposes. You may modify and distribute it according to the terms of the license included with the project.

## ⭐ Acknowledgements

This project is based on fundamental concepts from **Data Structures, Graph Theory, and Shortest Path Algorithms**.

---

**🚑 Ambulance Route Optimizer — Finding the fastest path when every second matters.**
