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
               OtusAlgo::GCD::IntType a, OtusAlgo::GCD::IntType b) {
    constexpr size_t CYCLES = 100;
    auto start = std::chrono::system_clock::now();
    for (size_t i = 0; i < CYCLES; ++i){
        runner.Calculate(a,b);
    }
    auto end = std::chrono::system_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    output << name << " : " << 1.*us/CYCLES << " us" <<std::endl;

}

    
int main() {
    // for tests
    std::filesystem::path this_file = __FILE__;
    // elapsed time to save
    std::ofstream output(this_file.parent_path().string() + "/benchmark.txt");

    {
    OtusAlgo::EuclidSub gcd_sub;
    OtusAlgo::Tester test(gcd_sub, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Euclid Sub", output, gcd_sub, 9876543210, 123456789);
    }

    {
    OtusAlgo::EuclidMod gcd_mod;
    OtusAlgo::Tester test(gcd_mod, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Euclid Mod", output, gcd_mod, 9876543210, 123456789);
    }

    
    {
    OtusAlgo::Stein gcd_stein;
    OtusAlgo::Tester test(gcd_stein, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Euclid Stein", output, gcd_stein, 9876543210, 123456789);
    }


    return 0;
}
