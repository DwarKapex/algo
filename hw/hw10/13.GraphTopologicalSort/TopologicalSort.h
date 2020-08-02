#pragma once

#include <DiGraph.h>

namespace OtusAlgo {

std::vector<size_t> DemucronTopologicalSort(const DiGraph& graph);

std::vector<size_t> TarjanTopologicalSort(const DiGraph& graph);

} // namespace OtusAlgo


