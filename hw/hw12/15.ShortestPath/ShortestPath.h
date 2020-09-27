#pragma once

#include <DenceGraph.h>

namespace OtusAlgo {

auto DijkstraAlgorithm(const DenceGraph& graph, const int from, const int to) -> std::pair<Edge, DenceGraph::WeightType>;
std::vector<Edge> FloydWarshallAlgorithm(const DenceGraph& graph);
std::vector<Edge> JohnsonAlgorithm(const DenceGraph& graph);

} // namespace OtusAlgo


