# Project Charter — Ambulance Route Optimization

## Problem Statement
Emergency response time directly affects patient survival and outcomes. Ambulances often lose critical time due to inefficient route selection, traffic congestion, and lack of real-time coordination with hospital availability. This project builds a C++ system that models the road network as a graph and applies shortest-path algorithms to compute the fastest route from an ambulance's location to an emergency site, and from there to the nearest available hospital.

## Objectives
1. Model a road network using graph data structures (nodes = intersections/locations, edges = roads with weights).
2. Implement a shortest-path algorithm (Dijkstra's algorithm, with A* as a stretch goal) to compute the fastest route between two points.
3. Represent core entities as C++ classes using OOP principles (encapsulation, inheritance, polymorphism where applicable) — e.g., `Graph`, `Node`, `Edge`, `Ambulance`, `Hospital`, `Router`.
4. Select the nearest available hospital from an emergency site based on distance/travel time (and capacity, if implemented).
5. Deliver a working, tested, and documented C++ application demonstrating the above.

## Scope
**In scope:**
- Static or semi-static road network graph (from sample data, not live GPS/maps).
- Single-ambulance routing (not multi-ambulance dispatch optimization).
- Console-based interaction (CLI), unless the team adds a GUI as a stretch goal.

**Out of scope (for this course project):**
- Real-time traffic API integration.
- Multi-vehicle fleet optimization.
- Production-grade deployment/scaling concerns.

## Team & Roles
| Name | Role |
|---|---|
| [Teammate 1] | Core algorithm & graph implementation |
| [Teammate 2] | Class design (Ambulance/Hospital entities), CLI/UI |
| **[Your Name]** | **Documentation & Testing** |

## My Role: Documentation & Testing
- Own the `/docs` folder: requirements, design docs, developer guide, test plan, test reports.
- Own the `/tests` folder: unit tests for each class/module, integration tests for full workflows, edge-case coverage.
- Maintain a weekly progress log and ensure documentation stays in sync with code as it evolves.
- Use Google Test (or Catch2) as the C++ testing framework, integrated via CMake.

## Success Criteria
- The system correctly computes the shortest path on test graphs of varying size and complexity.
- Core classes and algorithms have documented unit tests with clear pass/fail results.
- Project documentation (requirements, design, developer guide, test report) is complete and up to date by Week 12.
- The full test suite runs cleanly via CMake/CTest with no failing tests at final submission.

## Milestones (High-Level)
| Week(s) | Milestone |
|---|---|
| 1–3 | Setup, requirements, design (UML class diagram) |
| 4–6 | Core unit tests (graph, routing algorithm), inline documentation |
| 7 | Mid-project checkpoint |
| 8–9 | Integration & edge-case testing |
| 10 | Performance testing |
| 11 | Regression testing & final test report |
| 12 | Final documentation polish & presentation |

## Tools
- Language: C++ (C++17 or later recommended)
- Build system: CMake
- Testing framework: Google Test
- Documentation: Doxygen (code-level) + Markdown (project-level)
- Version control: Git / GitHub
