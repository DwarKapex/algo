#include "GraphSearch.h"

namespace OtusAlgo {

void BridgeSearchUtil(const DiGraph& graph,
                      int v, int p,
                      std::vector<size_t>& tin, std::vector<size_t>& fup,
                      std::vector<bool>& visited, size_t timer,
                      std::vector<Edge>& bridges) {
    visited[v] = true;
    tin[v] = fup[v] = timer++;
    OtusAlgo::DiGraph::adjIterator adjIt(graph, v);
    for (auto to = adjIt.begin(); !adjIt.end(); to = adjIt.next()) {
        if (v != p) {
            if (to == p) continue;
            if (visited[to]) {
                fup[v] = std::min(fup[v], tin[to]);
            }
            else {
                BridgeSearchUtil(graph, to, v, tin, fup, visited, timer, bridges);
                fup[v] = std::min(fup[v], fup[to]);
                if (fup[to] > tin[v])
                    bridges.emplace_back(v,to);
            }
        }
    }
    
}
std::vector<Edge> BridgeSearch(const DiGraph& graph) {
    size_t n = graph.V();
    size_t timer = 0;
    std::vector<Edge> bridges;
    std::vector<bool> visited(n, false);
    std::vector<size_t> tin(n, 0), fup(n, 0);
    for (size_t idx = 0; idx < n; ++idx) {
        if (!visited[idx]) {
            BridgeSearchUtil(graph, idx, -1,
                             tin, fup,
                             visited, timer, bridges);
        }
    }
    
    return bridges;
}
std::vector<size_t> ArticulationPointSearch([[maybe_unused]] const DiGraph& graph) {
    return {};
}

} // namespace OtusAlgo


