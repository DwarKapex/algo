#include "Primes.h"
#include <Tester.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>

namespace fs = std::filesystem;

void benchmark(const std::string& name,
               std::ofstream& output,
               const OtusAlgo::Primes& runner,
               const std::vector<OtusAlgo::Primes::IntType>& a) {
    constexpr size_t CYCLES = 2;
    output << name << " : ";
    for (const auto value: a) {
        auto start = std::chrono::system_clock::now();
        for (size_t i = 0; i < CYCLES; ++i){
            runner.Calculate(value);
        }
        auto end = std::chrono::system_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
        output << 1.*us/CYCLES << " us\t";
    }
    output << std::endl;
}

    
int main() {
    // for tests
    std::filesystem::path this_file = __FILE__;
    // elapsed time to save
    std::ofstream output(this_file.parent_path().string() + "/benchmark.txt");
    const std::vector<OtusAlgo::Primes::IntType> as{10, 2500, 100000};
    output << "Benchmark for input data: \n";
    for (size_t i = 1; i <= as.size(); ++i) {
        output << i << ". " << as[i-1] << '\n';
    }
    output << std::endl;
    
    {
    std::cout << "PrimesDividers\n";
    OtusAlgo::PrimesDividers prime;
    OtusAlgo::Tester test(prime, this_file.parent_path().string() + "/tests");
    test.RunTests(10);
    // benchmark
    benchmark("Primes Dividers", output, prime, as);
    }

    {
    std::cout << "PrimesDivider2\n";
    OtusAlgo::PrimesDividers2 prime;
    OtusAlgo::Tester test(prime, this_file.parent_path().string() + "/tests");
    test.RunTests(8);
    // benchmark
    benchmark("Primes Dividers2", output, prime, as);
    }

    {
    std::cout << "PrimesSieve\n";
    OtusAlgo::PrimesSieve prime;
    OtusAlgo::Tester test(prime, this_file.parent_path().string() + "/tests");
    test.RunTests(8);
    // benchmark
    benchmark("Primes Sieve", output, prime, as);
    }
    
    {
    std::cout << "PrimesSieveBitmap\n";
    OtusAlgo::PrimesSieveBitmap prime;
    OtusAlgo::Tester test(prime, this_file.parent_path().string() + "/tests");
    test.RunTests(8);
    // benchmark
    benchmark("Primes SieveBitMap", output, prime, as);
    }

    {
    std::cout << "PrimesSieveN\n";
    OtusAlgo::PrimesSieveN prime;
    OtusAlgo::Tester test(prime, this_file.parent_path().string() + "/tests");
    test.RunTests(8);
    // benchmark
    benchmark("Primes Sieve O(N)", output, prime, as);
    }

    
    return 0;
}
