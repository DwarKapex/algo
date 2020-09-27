#include "ShortestPath.h"
#include <cassert>
#include <memory>
#include <iostream>

int main() {
    
    using Graph = OtusAlgo::DenceGraph;
    Graph graph(6);
    graph.insert({0, 1}, 7);
    graph.insert({0, 2}, 9);
    graph.insert({0, 5}, 14);
    graph.insert({1, 2}, 10);
    graph.insert({1, 3}, 15);
    graph.insert({2, 5}, 2);
    graph.insert({2, 3}, 11);
    graph.insert({3, 4}, 6);
    graph.insert({4, 5}, 9);
    
    int from = 0, to = 5;
    std::pair<OtusAlgo::Edge, double> expected{{from, to}, 11};
    auto result = OtusAlgo::DijkstraAlgorithm(graph, from, to);
    assert(expected == result);
    std::cout << "Path found! Min distance is " << result.second << std::endl;
    return 0;
}
