// Sanity check test — confirms Google Test + CMake are wired up correctly.
// Once real classes (Graph, Node, Router, etc.) exist, replace/expand this
// with tests in dedicated files: test_graph.cpp, test_routing.cpp, etc.

#include <gtest/gtest.h>

TEST(SanityCheck, BuildAndRunWorks) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(SanityCheck, StringsWork) {
    std::string hello = "hello";
    EXPECT_EQ(hello.length(), 5);
}
