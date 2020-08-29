#include "MinimalSpanningTree.h"
#include <cassert>
#include <numeric>
#include <set>

namespace OtusAlgo {

// ----------------------------------------------------
#pragma mark Kruscal Minimal Spanning Tree Algorithm
// ----------------------------------------------------

auto GetAllEdges(const DenceGraph& graph) -> std::vector<std::pair<Edge, DenceGraph::WeightType>>{
    std::vector<std::pair<Edge, DenceGraph::WeightType>> all_edges;
    all_edges.reserve(graph.E());
    for (int from = 0; from < graph.V(); ++from) {
        OtusAlgo::DenceGraph::adjIterator adjIt(graph, from);
        for (auto to = adjIt.begin(); to <= from && !adjIt.end(); to = adjIt.next()) {
            all_edges.push_back({{from, to}, graph.edge(from, to)});
        }
    }
    assert(all_edges.size() == graph.E());
    return all_edges;
}

int FindParent(const std::vector<int>& parent, int child) {
    if (parent[child] == child)
        return child;
    else
        return FindParent(parent, parent[child]);
}

void Union(std::vector<int>& parent, int x, int y) {
    if (x < y)
        std::swap(x,y);
    parent[x] = parent[y];
}
std::vector<Edge> KruscalMinimalSpanningTree(const DenceGraph& graph) {
    // compile edge array sorted by length
    auto sorted_edges = GetAllEdges(graph);
    std::sort(sorted_edges.begin(), sorted_edges.end(),
              [](const auto& a, const auto& b){
                return a.second < b.second;
    });
    std::vector<Edge> spanning_tree;
    size_t n = graph.V();
    spanning_tree.reserve(n);
    std::vector<int> parent(n);
    std::iota(parent.begin(), parent.end(), 0);
    
    for (const auto& edge: sorted_edges) {
        int x = FindParent(parent, edge.first.from);
        int y = FindParent(parent, edge.first.to);
        if (x != y) {
            spanning_tree.emplace_back(edge.first.from, edge.first.to);
            Union(parent, x, y);
        }
    }
    
    return spanning_tree;
}

// ----------------------------------------------------
#pragma mark Prima Minimal Spanning Tree Algorithm
// ----------------------------------------------------


std::vector<Edge> PrimaMinimalSpanningTree(const DenceGraph& graph) {
    using WeightType = DenceGraph::WeightType;
    using DenseEdge = std::pair<Edge, WeightType>;
    WeightType INF = std::numeric_limits<WeightType>::max();
    
    size_t n = graph.V();
    std::vector<Edge> spanning_tree;
    spanning_tree.reserve(n-1);

    // used vertices
    std::vector<DenseEdge> remain_vertices(n);
    std::vector<bool> used (n, false);
    std::vector<int> min_edge_weight (n, INF), selected_edge (n, -1);
    min_edge_weight[0] = 0;
    
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || min_edge_weight[j] < min_edge_weight[v]))
                v = j;
        }
        if (min_edge_weight[v] == INF) {
            throw std::runtime_error("There is no MST in this graph!");
        }
     
        used[v] = true;
        if (selected_edge[v] != -1) {
            
            spanning_tree.push_back({std::max(v,selected_edge[v]), std::min(v,selected_edge[v])});
        }
        OtusAlgo::DenceGraph::adjIterator adjIt(graph, v);
        for (auto to = adjIt.begin(); !adjIt.end(); to = adjIt.next()) {
            if (graph.edge(v,to) < min_edge_weight[to]) {
                min_edge_weight[to] = graph.edge(v,to);
                selected_edge[to] = v;
            }
        }
    }
    
    return spanning_tree;
}

// ----------------------------------------------------
#pragma mark Boruvki Minimal Spanning Tree Algorithm
// ----------------------------------------------------


std::vector<Edge> BoruvkiMinimalSpanningTree(const DenceGraph& graph) {
    return {};
}


} // namespace OtusAlgo


