#include "Power.h"
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
               const OtusAlgo::Power& runner,
               OtusAlgo::Power::FloatType a, OtusAlgo::Power::IntType b) {
    constexpr size_t CYCLES = 10;
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
    OtusAlgo::PowerMultiplication p;
    OtusAlgo::Tester test(p, this_file.parent_path().string() + "/tests");
    test.RunTests(7);
    // benchmark
    benchmark("Power Multiplication", output, p, 1.000000001, 1000000000);
    }

    {
    OtusAlgo::Power2 p;
    OtusAlgo::Tester test(p, this_file.parent_path().string() + "/tests");
    test.RunTests(7);
    // benchmark
    benchmark("Power2", output, p, 1.000000001, 1000000000);
    }
    
    {
    OtusAlgo::PowerBinary p;
    OtusAlgo::Tester test(p, this_file.parent_path().string() + "/tests");
    test.RunTests(7);
    // benchmark
    benchmark("Power Binary", output, p, 1.000000001, 1000000000);
    }


    return 0;
}
