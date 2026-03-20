#include "graph.h"

int main() {
    Graph g = Graph::readFromInput();

    auto res = stoerWagnerWithEdges(g);

    std::cout << "Min cut value: " << res.value << "\n";
    std::cout << "Edges:\n";

    for (auto [u, v] : res.edges) {
        std::cout << u << " " << v << "\n";
    }
}