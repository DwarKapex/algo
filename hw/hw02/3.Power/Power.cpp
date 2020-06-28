#include "Power.h"
#include <iostream>
#include <sstream>
#include <iomanip>

namespace OtusAlgo {


std::string Power::Run(const ITask::DataType& data) {
    if (data.size() < 2) {
        return "0";
    }
    constexpr size_t precision = 20;
    FloatType a;
    IntType n;
    std::stringstream ss;
    ss << data[0] << " " << data[1];
    ss >> a >> n;
    FloatType result = Calculate(a, n);
    std::cout << std::setprecision(precision) << " a = " << a << ", n = " << n << std::setprecision(precision) << ", res = " << result << "; ";
    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << result;
    return out.str() + " ";
}


auto PowerMultiplication::Calculate(FloatType a, IntType b) const -> FloatType {
    FloatType result = 1.;
    while (b-- > 0){
        result *= a;
    }
    return result;
}

auto Power2::Calculate(FloatType a, IntType b) const -> FloatType {
    if (b == 0) return 1;
    if (b == 1) return a;
    size_t p = 2;
    FloatType result = a*a;
    while (2*p <= b) {
        p *= 2;
        result *= result;
    }
    for (size_t i = p; i < b; ++i)
        result *= a;
    
    return result;
}

auto PowerBinary::Calculate(FloatType a, IntType b) const -> FloatType {
    FloatType result = 1.;
    FloatType base = a;
    while (b > 0) {
        if ( b & 1)
            result *= base;
        base *= base;
        b >>=1;
    }
    return result;
}


} //namespace OtusAlgo
