#pragma once

// edge representation
struct Edge {
    int from, to;
    Edge(int _from=-1, int _to=-1):
          from(_from)
        , to(_to) {}
};
