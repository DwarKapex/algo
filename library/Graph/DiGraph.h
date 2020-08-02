#pragma once

#include <IGraph.h>
#include <vector>

namespace OtusAlgo {
class DiGraph: public IGraph {
private:
    using ConnectType = std::vector<int>;
    using GraphType = std::vector<ConnectType>;
public:
    DiGraph(int n_vertex);
    ~DiGraph() = default;
    
    size_t V() const override; // number of vertices
    size_t E() const override; // number of egdes
    
    void insert(Edge) override; // add edge
    void remove(Edge) override; // remove edge
    bool edge(int, int) const override; // chech edge presents

    // iterator to traverse throu graph
    class adjIterator {
        private:
            const DiGraph& m_graph;
            size_t m_v;
            int i;

        public:
            adjIterator(const DiGraph & graph, size_t v);
            int begin();
            int next();
            bool end();
    };

    
private:
    GraphType m_graph;
    size_t m_edge = 0;
};

} // namespace OtusAlgo
