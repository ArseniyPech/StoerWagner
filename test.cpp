#include <gtest/gtest.h>
#include "graph.h"

TEST(MinCutTest, Simple) {
    Graph g(2);
    g.addToEdge(0,1,5);

    EXPECT_EQ(stoerWagnerWithEdges(g).value, 5);
}

TEST(MinCutTest, Triangle) {
    Graph g(3);
    g.addToEdge(0,1,1);
    g.addToEdge(1,2,1);
    g.addToEdge(0,2,1);

    EXPECT_EQ(stoerWagnerWithEdges(g).value, 2);
}

TEST(MinCutTest, Chain) {
    Graph g(4);
    g.addToEdge(0,1,3);
    g.addToEdge(1,2,2);
    g.addToEdge(2,3,4);

    EXPECT_EQ(stoerWagnerWithEdges(g).value, 2);
}