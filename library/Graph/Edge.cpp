#include <Edge.h>

namespace OtusAlgo {

bool operator==(const Edge& lhs, const Edge& rhs) {
    return lhs.from == rhs.from && lhs.to == rhs.to;
}
} //namespace OtusAlgo
