#include "ShortestPath.h"
#include <numeric>
#include <queue>
#include <cassert>

namespace OtusAlgo {

// ----------------------------------------------------
#pragma mark Dijkstra Algorithm
// ----------------------------------------------------

auto DijkstraAlgorithm(const DenceGraph& graph, const int from, const int to) -> std::pair<Edge, DenceGraph::WeightType> {
    std::vector<Edge> result;
    if (from != to) {
        const size_t n = graph.V();
        assert(from < n && to < n);
        std::vector<DenceGraph::WeightType> distance(n, std::numeric_limits<DenceGraph::WeightType>::max());
        distance[from] = 0;
        std::vector<bool> visited(n, false);
        using StoreType = std::pair<DenceGraph::WeightType, int>;
        std::priority_queue<StoreType, std::vector<StoreType>, std::greater<StoreType>> q;
        q.emplace(0, from);
        while (!q.empty()) {
            auto [w, v] = q.top();
            if (v == to)
                break;
            q.pop();
            visited[v] = true;
            OtusAlgo::DenceGraph::adjIterator adjIt(graph, v);
            for (auto t = adjIt.begin(); !adjIt.end(); t = adjIt.next()) {
                if (w + graph.edge(v,t) < distance[t]) {
                    distance[t] = w + graph.edge(v,t);
                    if (!visited[t])
                        q.emplace(distance[t], t);
                }
            }
        }
        if (distance[to] < std::numeric_limits<DenceGraph::WeightType>::max())
            return {Edge{from,to}, distance[to]};
    }
    return {};
}

} // namespace OtusAlgo
