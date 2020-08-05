#pragma once

namespace OtusAlgo {
// edge representation
struct Edge {
    int from, to;
    Edge(int _from=-1, int _to=-1):
          from(_from)
        , to(_to) {}
};

bool operator==(const Edge& lhs, const Edge& rhs);

} //namespace OtusAlgo
