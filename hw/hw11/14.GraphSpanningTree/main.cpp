#include "MinimalSpanningTree.h"
#include <cassert>

int main() {
    
    using Graph = OtusAlgo::DenceGraph;
    Graph graph(7);
    graph.insert({0, 1}, 7);
    graph.insert({0, 3}, 5);
    graph.insert({1, 2}, 8);
    graph.insert({1, 3}, 9);
    graph.insert({1, 4}, 7);
    graph.insert({2, 4}, 5);
    graph.insert({3, 4}, 15);
    graph.insert({3, 5}, 6);
    graph.insert({4, 5}, 8);
    graph.insert({4, 6}, 9);
    graph.insert({5, 6}, 11);
    
    std::vector<OtusAlgo::Edge> expected{{1,0}, {3, 0}, {4,1}, {4,2}, {5,3}, {6,4}};
    {
        auto received = OtusAlgo::KruscalMinimalSpanningTree(graph);
        std::sort(received.begin(), received.end(),
                  [](const auto& a, const auto& b){
                    return a.from < b.from || (a.from == b.from && a.to < b.to);
        });
        assert(expected == received);
    }

    {
        auto received = OtusAlgo::PrimaMinimalSpanningTree(graph);
        std::sort(received.begin(), received.end(),
                  [](const auto& a, const auto& b){
                    return a.from < b.from || (a.from == b.from && a.to < b.to);
        });
        assert(expected == received);
    }

    return 0;
}
