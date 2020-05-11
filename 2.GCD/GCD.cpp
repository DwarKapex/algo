#include "GCD.h"
#include <iostream>
#include <sstream>
namespace OtusAlgo {


std::string GCD::Run(const ITask::DataType& data) {
    if (data.size() < 2) {
        return "0";
    }
    uint64_t a, b;
    std::stringstream ss;
    ss << data[0] << " " << data[1];
    ss >> a >> b;
    return std::to_string(Calculate(a, b));
}


GCD::IntType EuclidSub::Calculate(IntType a, IntType b) const {
    while (a != b) {
        if (a > b) {
            a -= b;
        }
        else {
            b -=a;
        }
    }
    return a;
}

GCD::IntType EuclidMod::Calculate(IntType a, IntType b) const {
    while (a > 0 && b > 0) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a+b;
}

GCD::IntType Stein::Calculate(IntType u, IntType v) const {
    // simple cases (termination)
    if (u == v) { return u; }
    if (u == 0) { return v; }
    if (v == 0) { return u; }

    if (~u & 1) {
        if (v & 1) {
            return Calculate(u >> 1, v);
        }
        else {
            return Calculate(u >> 1, v >> 1) << 1;
        }
    }

    if (~v & 1) return Calculate(u, v >> 1);
    if (u > v) return Calculate((u - v) >> 1, v);

    return Calculate((v - u) >> 1, u);
}

} //namespace OtusAlgo
