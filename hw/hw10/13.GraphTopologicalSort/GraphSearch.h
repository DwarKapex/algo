#pragma once

#include <DiGraph.h>

namespace OtusAlgo {

std::vector<Edge> BridgeSearch(const DiGraph& graph);
std::vector<size_t> ArticulationPointSearch(const DiGraph& graph);

} // namespace OtusAlgo


