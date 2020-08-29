#include <DenceGraph.h>

namespace OtusAlgo {

DenceGraph::DenceGraph(int n_vertex): IGraph(false) {
    m_graph.assign(n_vertex, ConnectType(n_vertex));
}

size_t DenceGraph::V() const {
    return m_graph.size();
}
size_t DenceGraph::E() const {
    return m_edge;
}

void DenceGraph::insert(Edge edge, WeightType w) {
    if (edge.from < V() && edge.to < V()) {
        if (m_graph[edge.from][edge.to] == 0) {
            ++m_edge;
        }
        m_graph[edge.from][edge.to] = w;
        if (!m_is_directed) {
            m_graph[edge.to][edge.from] = w;
        }
    }
}

void DenceGraph::remove(Edge edge) {
    if (edge.from < V() && edge.to < V()) {
        m_graph[edge.from][edge.to] = 0;
        if (!m_is_directed) {
            m_graph[edge.to][edge.from] = 0;
        }
    }

}

auto DenceGraph::edge(int from, int to) const -> WeightType {
    if (from < V() && to < V()) {
        return m_graph[from][to];
    }
    return -1;
}


DenceGraph::adjIterator::adjIterator(const IGraph & graph, size_t v):
          m_graph(graph)
        , m_v(v)
        , i(-1)
    {}

int DenceGraph::adjIterator::begin() {
    i = -1;
    return next();
}

int DenceGraph::adjIterator::next() {
    for (i++; i < m_graph.V(); ++i) {
        if (m_graph.edge(m_v, i) != 0) return i;
    }
    return -1;
}

bool DenceGraph::adjIterator::end() {
    return i >= m_graph.V();
}

} // namespace OtusAlgo

