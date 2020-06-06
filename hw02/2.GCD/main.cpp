#include "GCD.h"
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
               const OtusAlgo::GCD& runner,
               const std::vector<OtusAlgo::GCD::IntType>& as,
               const std::vector<OtusAlgo::GCD::IntType>& bs) {
    output << name << " : ";
    constexpr size_t CYCLES = 10;
    for (int i = 0; i < as.size(); ++i) {
        auto start = std::chrono::system_clock::now();
        for (size_t j = 0; j < CYCLES; ++j){
            runner.Calculate(as[i],bs[i]);
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
    const std::vector<OtusAlgo::GCD::IntType>& as{10, 1234567890, 1073676287};
    const std::vector<OtusAlgo::GCD::IntType>& bs{1, 12, 997};
    output << "Benchmark for input data: \n";
    for (size_t i = 1; i <= as.size(); ++i) {
        output << i << ". NOD(" << as[i-1] << "," << bs[i-1] << ")\n";
    }
    output << std::endl;
    
    {
    OtusAlgo::EuclidSub gcd_sub;
    OtusAlgo::Tester test(gcd_sub, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Euclid Sub", output, gcd_sub, as, bs);
    }

    {
    OtusAlgo::EuclidMod gcd_mod;
    OtusAlgo::Tester test(gcd_mod, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Euclid Mod", output, gcd_mod, as, bs);
    }

    
    {
    OtusAlgo::Stein gcd_stein;
    OtusAlgo::Tester test(gcd_stein, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Euclid Stein", output, gcd_stein, as, bs);
    }


    return 0;
}
