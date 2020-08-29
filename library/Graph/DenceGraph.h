#pragma once

#include <IGraph.h>
#include <vector>

namespace OtusAlgo {
class DenceGraph: public IGraph {
private:
    using ConnectType = std::vector<WeightType>;
    using GraphType = std::vector<ConnectType>;
public:
    DenceGraph(int n_vertex);
    ~DenceGraph() = default;
    
    size_t V() const override; // number of vertices
    size_t E() const override; // number of egdes
    
    void insert(Edge, WeightType w = 1) override; // add edge
    void remove(Edge) override; // remove edge
    WeightType edge(int, int) const override; // chech edge presents

    // iterator to traverse throu graph
    class adjIterator {
        private:
            const IGraph& m_graph;
            size_t m_v;
            int i;

        public:
            adjIterator(const IGraph & graph, size_t v);
            int begin();
            int next();
            bool end();
    };

    
private:
    GraphType m_graph;
    size_t m_edge = 0;
};

} // namespace OtusAlgo
