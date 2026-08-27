cmake_minimum_required(VERSION 3.14)
project(AmbulanceRouteOptimization CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# Main library / application source
# ---------------------------------------------------------------------------
# Add your .cpp files here as the team implements classes
# (Graph, Node, Edge, Ambulance, Hospital, Router, etc.)
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_library(ambulance_core ${SRC_FILES})
target_include_directories(ambulance_core PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Main executable (the actual program entry point, e.g. src/main.cpp)
# Uncomment once main.cpp exists:
# add_executable(ambulance_app src/main.cpp)
# target_link_libraries(ambulance_app PRIVATE ambulance_core)

# ---------------------------------------------------------------------------
# Testing (Google Test, fetched automatically — no manual install needed)
# ---------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)
