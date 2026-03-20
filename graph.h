#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

class Graph {
private:
    int n;
    vector <vector <long long>> g;

public:
    Graph(int n);

    int size() const;
    long long getWeight(int u, int v) const;
    void addToEdge(int u, int v, long long w);

    static Graph readFromInput();
};

struct MinCutResult {
    long long value;
    vector <pair <int,int>> edges;
};

MinCutResult stoerWagnerWithEdges(const Graph& graph);

#endif
