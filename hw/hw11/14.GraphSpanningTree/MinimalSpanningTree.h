#pragma once

#include <DenceGraph.h>

namespace OtusAlgo {

std::vector<Edge> KruscalMinimalSpanningTree(const DenceGraph& graph);
std::vector<Edge> PrimaMinimalSpanningTree(const DenceGraph& graph);
std::vector<Edge> BoruvkiMinimalSpanningTree(const DenceGraph& graph);

} // namespace OtusAlgo


