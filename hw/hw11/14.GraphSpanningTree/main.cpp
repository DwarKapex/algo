#include "TopologicalSort.h"
#include "GraphSearch.h"
#include <cassert>

int main() {
    
    using Graph = OtusAlgo::DiGraph;
    {
        Graph graph(14);
        graph.insert({0, 2});
        graph.insert({0, 12});
        
        graph.insert({1, 12});
        
        graph.insert({3, 2});
        
        graph.insert({4, 2});
        graph.insert({4, 8});
        graph.insert({4, 9});
        
        graph.insert({5, 3});
        graph.insert({5, 10});
        graph.insert({5, 11});
        graph.insert({5, 12});
        
        graph.insert({6, 10});
        
        graph.insert({7, 1});
        graph.insert({7, 3});
        graph.insert({7, 5});
        graph.insert({7, 6});
        
        graph.insert({8, 0});
        graph.insert({8, 13});
        
        graph.insert({9, 0});
        graph.insert({9, 6});
        graph.insert({9, 11});
        
        graph.insert({10, 2});
        graph.insert({12, 2});
        
        graph.insert({13, 5});
        
        auto received = OtusAlgo::DemucronTopologicalSort(graph);
        std::vector<std::vector<size_t>> expected{{4,7},{1,8,9},{0,6,13},{5},{3,10,11,12},{2}};
        assert(received == expected);
    }
    {
        Graph graph(6);
        graph.insert({5, 2});
        graph.insert({5, 0});
        graph.insert({4, 0});
        graph.insert({4, 1});
        graph.insert({2, 3});
        graph.insert({3, 1});
        auto received = OtusAlgo::TarjanTopologicalSort(graph);
        std::vector<size_t> expected{5,4,2,3,1,0};
        assert(received == expected);
    }
    
    // find bridge
//    {
//        Graph graph(5);
//        graph.insert({0, 1});
//        graph.insert({1, 2});
//        graph.insert({0, 2});
//        graph.insert({2, 0});
//        graph.insert({2, 3});
//        graph.insert({4, 3});
//
//        auto received = OtusAlgo::BridgeSearch(graph);
//        std::vector<OtusAlgo::Edge> expected{{2,3}, {4,3}};
//        assert(received == expected);
//    }
    
    {
        Graph graph(2);
        graph.insert({0, 1});
        
        auto received = OtusAlgo::BridgeSearch(graph);
        std::vector<OtusAlgo::Edge> expected{{0, 1}};
        assert(received == expected);
    }

    return 0;
}
