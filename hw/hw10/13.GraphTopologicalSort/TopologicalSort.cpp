#include "TopologicalSort.h"
#include <stack>
#include <algorithm>

namespace OtusAlgo {

std::vector<size_t> DemucronTopologicalSort(const DiGraph& graph) {
    size_t n = graph.V();
    std::vector<size_t> result;
    result.reserve(n);
    
    // fill in out edges
    std::vector<size_t> M(n, 0);
    for (size_t i = 0; i < n; ++i) {
        OtusAlgo::DiGraph::adjIterator adjIt(graph, i);
        for (auto it = adjIt.begin(); !adjIt.end(); it = adjIt.next()) {
            ++M[it];
        }
    }
    
    // do algo
    std::vector<bool> used(n, false);
    size_t added = 0;
    while (result.size() < n) {
        // find source
        for (size_t i = 0; i < n; ++i) {
            if (M[i] == 0 && !used[i]) {
                ++added;
                result.push_back(i);
                used[i] = true;
            }
        }
        if (added == 0)
            throw std::runtime_error("Loop detected. Topological sort is impossible!");
        // substruct from M
        auto it = result.rbegin();
        while (added > 0) {
            OtusAlgo::DiGraph::adjIterator adjIt(graph, *it);
            for (auto it = adjIt.begin(); !adjIt.end(); it = adjIt.next()) {
                --M[it];
            }
            ++it;
            added--;
        }
    }
    
    return result;
}


void TarjanTopologicalSortUtil(const DiGraph& graph,
                               size_t idx,
                               std::vector<bool>& visited,
                               std::vector<size_t>& result)
{
    visited[idx] = true;
    DiGraph::adjIterator adjIt(graph, idx);
    for (auto it = adjIt.begin(); !adjIt.end(); it = adjIt.next()) {
        if (!visited[it])
            TarjanTopologicalSortUtil(graph, it, visited, result);
    }
    result.push_back(idx);
}

std::vector<size_t> TarjanTopologicalSort(const DiGraph& graph) {
    size_t n = graph.V();
    std::vector<bool> visited(n, false);
    std::vector<size_t> result;
    for (size_t i = 0; i < n; ++i) {
        if (!visited[i]) {
            TarjanTopologicalSortUtil(graph, i, visited, result);
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}
} // namespace OtusAlgo
