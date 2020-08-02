#pragma once
#include <stddef.h>
#include <Edge.h>

namespace OtusAlgo {

class IGraph {
private:
public:
    explicit IGraph(bool is_directed): m_is_directed(is_directed) {}
    ~IGraph() = default;
    
    virtual size_t V() const = 0; // number of vertices
    virtual size_t E() const = 0; // number of egdes
    bool is_directed() const { return m_is_directed; }
    
    virtual void insert(Edge) = 0; // add edge
    virtual void remove(Edge) = 0; // remove edge
    virtual bool edge(int, int) const = 0; // chech edge presents

//    void insert(); // add a new vertex
//    void remove(int); // remove vertex


protected:
    bool m_is_directed;
};

} // namespace OtusAlgo
