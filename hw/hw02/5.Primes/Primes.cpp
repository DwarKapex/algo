#include "Primes.h"
#include <iostream>
#include <sstream>
#include <numeric>

namespace OtusAlgo {


std::string Primes::Run(const ITask::DataType& data) {
    if (data.empty()) {
        return "0";
    }
    IntType a;
    std::stringstream ss;
    ss << data[0];
    ss >> a;
    return std::to_string(Calculate(a)) + " ";
}


auto PrimesDividers::Calculate(IntType a) const -> IntType {
    IntType result = 0;
    for (IntType i = 2; i <= a; ++i) {
        if (IsPrime(i)) ++result;
    }
    return result;
}

auto PrimesDividers::IsPrime(IntType a) const -> bool {
    for (IntType i = 2; i*i <= a; ++i)
        if ( a % i == 0 ) return false;
    return true;
}


auto PrimesDividers2::Calculate(IntType a) const  -> IntType {
    if (a == 1) return 0;
    std::vector<IntType> primes;
    primes.reserve(1000);
    primes.push_back(2);
    for (IntType i = 2; i <=a; ++i) {
        bool is_prime = true;
        for (auto const prime: primes) {
            if (i % prime == 0) {
                is_prime = false;
            }
        }
        if (is_prime) primes.push_back(i);
    }
    return primes.size();
}

auto PrimesSieve::Calculate(IntType a) const -> IntType {
    std::vector<int> sieve(a+1, 1);
    size_t idx = 2;
    while (idx*idx <= a) {
        for (IntType i = idx*idx; i <= a; i+=idx) {
            sieve[i] = 0;
        }
        while (sieve[++idx] == 0)
            ;
    }
    
    return std::accumulate(sieve.begin(), sieve.end(), -2);
}

auto PrimesSieveBitmap::Calculate(IntType a) const -> IntType {
    using Type = int;
    size_t bits = sizeof(Type)*8;
    std::vector<Type> sieve((a+1)/bits + 1, 0);
    size_t idx = 2;
    while (idx*idx <= a) {
        for (IntType i = idx*idx; i <= a; i+=idx) {
            sieve[i/bits] |= (1 << (i % bits - 1));
        }
        ++idx;
        while ((sieve[idx/bits] & (1 << (idx % bits - 1))))
            ++idx;
    }
    size_t result = a-1;
    for (auto item: sieve)
        result -= GetBitOneCount(item);
    return result;
}
auto PrimesSieveBitmap::GetBitOneCount(int a) const -> size_t {
    size_t result = 0;
    while (a) {
        ++result;
        a &= (a-1);
    }
    return result;
}


auto PrimesSieveN::Calculate(IntType a) const -> IntType{
    std::vector<IntType> lp(a+1, 0);
    std::vector<IntType> primes;
    for (IntType i = 2; i <= a; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (auto p: primes) {
            if ((p <= lp[i]) && (p*i <=a ))
                lp[p*i] = p;
            else
                break;
        }
         
    }
    return primes.size();
}


} //namespace OtusAlgo
