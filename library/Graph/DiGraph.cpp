#include <DiGraph.h>

namespace OtusAlgo {

DiGraph::DiGraph(int n_vertex): IGraph(true) {
    m_graph.assign(n_vertex, ConnectType(n_vertex));
}

size_t DiGraph::V() const {
    return m_graph.size();
}
size_t DiGraph::E() const {
    return m_edge;
}

void DiGraph::insert(Edge edge, WeightType w) {
    if (edge.from < V() && edge.to < V()) {
        m_graph[edge.from][edge.to] = w;
    }
}

void DiGraph::remove(Edge edge) {
    if (edge.from < V() && edge.to < V()) {
        m_graph[edge.from][edge.to] = 0;
    }

}

auto DiGraph::edge(int from, int to) const -> WeightType{
    if (from < V() && to < V()) {
        return m_graph[from][to] != 0;
    }
    return false;
}


DiGraph::adjIterator::adjIterator(const DiGraph & graph, size_t v):
          m_graph(graph)
        , m_v(v)
        , i(-1)
    {}

int DiGraph::adjIterator::begin() {
    i = -1;
    return next();
}

int DiGraph::adjIterator::next() {
    for (i++; i< m_graph.V(); ++i) {
        if (m_graph.edge(m_v, i) == 1) return i;
    }
    return -1;
}

bool DiGraph::adjIterator::end() {
    return i >= m_graph.V();
}

    
//public:
//
//    int DiGraph::beg() {}
//    int DiGraph::nxt() {}
//    bool DiGraph::end() {}
//};


} // namespace OtusAlgo

