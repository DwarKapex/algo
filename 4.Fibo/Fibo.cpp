#include "Fibo.h"
#include <iostream>
#include <sstream>
#include <cmath>
namespace OtusAlgo {


std::string Fibo::Run(const ITask::DataType& data) {
    IntType N;
    std::stringstream ss;
    ss << data.front();
    ss >> N;
    return std::to_string(Calculate(N));
}

auto FiboRecursive::Calculate(IntType N) const -> IntType {
    if (N == 0)
        return 0;
    if (N == 1)
        return 1;
    
    return Calculate(N-1) + Calculate(N-2);
}

auto FiboIter::Calculate(IntType N) const -> IntType   {
    if (N == 0)
        return 0;
    if (N == 1)
        return 1;
        
    IntType a = 0, b = 1;
    while (N != 1 ) {
        a += b;
        std::swap(a,b);
        --N;
    }
    
    return b;

}

auto FiboGolden::Calculate(IntType N) const -> IntType {
    double phi = (1+std::sqrt(5))/2;
    
    return std::floor(std::pow(phi, N)/std::sqrt(5) + 1./2);
}

auto FiboMatrix::Calculate(IntType N) const -> IntType {
    if (N == 0) return 0;
    auto res = PowerMatrix(N);
    return res[1];
}

auto FiboMatrix::PowerMatrix(IntType n) const -> MatrixType {
    MatrixType result = MatrixType{1,0,0,1};
    MatrixType power_matrix = m_matrix;
    while (n != 0) {
        if ( n & 1 ) {
            result = MultiplyMatrix(result, power_matrix);
        }
        power_matrix = MultiplyMatrix(power_matrix, power_matrix);
        n >>= 1;
    }
    return result;
}

auto FiboMatrix::MultiplyMatrix(MatrixType a, MatrixType b) const -> MatrixType {
    MatrixType result(a.size(), 0);
    result[0] = a[0]*b[0] + a[1]*b[2];
    result[1] = a[0]*b[1] + a[1]*b[3];
    result[2] = a[2]*b[0] + a[3]*b[2];
    result[3] = a[2]*b[1] + a[3]*b[3];
    
    return result;
}


} //namespace OtusAlgo
