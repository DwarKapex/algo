#define BOOST_TEST_MODULE SIMPLE_DiGraph_TopologicalSort_TEST

#include <DiGraph.h>
#include <sstream>
#include "../TopologicalSort.h"

#include <boost/test/unit_test.hpp>

//using namespace OtusAlgo;

BOOST_AUTO_TEST_CASE (BuildDiGraph)
{
    [[maybe_unused]] OtusAlgo::DiGraph graph(5);
}

BOOST_AUTO_TEST_CASE (DiGraphAddRemoveEdges)
{
    OtusAlgo::DiGraph graph(5);
    graph.insert({1,2});
    BOOST_TEST(graph.edge(1,2));
    BOOST_TEST(!graph.edge(2,1));
    graph.remove({1,2});
    BOOST_TEST(!graph.edge(1,2));
    
    BOOST_TEST(!graph.edge(10,20));
}

BOOST_AUTO_TEST_CASE (DiGraphAdjIterator)
{
    using Graph = OtusAlgo::DiGraph;
    Graph graph(5);
    graph.insert({1,2});
    graph.insert({1,4});
    graph.insert({2,4});
    auto adjIt = Graph::adjIterator(graph, 1);
    std::stringstream ss;
    for (auto it = adjIt.begin(); !adjIt.end(); it = adjIt.next()) {
        ss << it << " ";
    }
    BOOST_TEST(ss.str() == "2 4 ");
}



